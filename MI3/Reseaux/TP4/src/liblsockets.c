/*
 * liblsockets.c
 * This file is part of liblsockets
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * liblsockets is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * liblsockets is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liblsockets. If not, see <http://www.gnu.org/licenses/>.
 */

#include "liblsockets.h"


/* ========= Defines ==========*/
int verbose; /*< Verbosity of the program */

/* ========= Functions ========*/

/** \defgroup Wrappers Communication Managers
 * Two functions for managing communications, take care of everithing for you
 */
/** @{ */

/** Big sending function 
 * Note that it will just call socket_message_send() because it's actually the best function for that.
 */
int message_send(lsocket*sck,msg_type type_message,char*msg){
	return socket_message_send(sck,type_message,msg);
}

/** Kinda deprecated but well, you can't have everything */
char*message_receive(lsocket*sck){
	lpacket*pck=packet_receive(sck);
	char*msg=malloc(sizeof(char)*strlen(pck->message));
	strcpy(pck->message,msg);
	packet_drop(pck);
	return msg;
}

/** Initiate an exchange
 * Send a message, wait for a correct answer 
 * @param sck_send Socket used for sending
 * @param type_message_send Type of the sended message
 * @param msg The sended message
 * @param sck_recv Socket used for reception
 * @param type_message_recv Type expected for reception
 */
char*message_exchange(lsocket*sck_send,msg_type type_message_send,char*msg,lsocket*sck_recv,msg_type type_message_recv){
	int count=KEEP_ALIVE; /** <Time to keep-alive connection */
	lpacket*pck; char*answer;
	
	/* Force good formated answer */
	if (verbose>1) {printf("Awaiting answer...");fflush(stdout);}
	do{
		socket_message_send(sck_send,type_message_send,msg);
		if (KEEP_ALIVE-count) sleep(LATENCY); /* [ILL IMPLEMENTED] Find a damn smaller function */
		pck=packet_receive(sck_recv);
		if (verbose>1) {printf("%c",pck->type==msg_recv?'*':'.');fflush(stdout);}
		if (!count--) {printf("\n");OUT("Server didn't sent expected message")};
	} while (pck->type!=type_message_recv);
	if (verbose>1) printf("\nServer replied !\n");
	/* Copy answer */
	answer=malloc(sizeof(char)*strlen(pck->message));
	strcpy(answer,pck->message);
	
	/* Free it and return */
	packet_drop(pck);
	return answer;
}

/** @} */

/** \defgroup liblsockets
 * A very small lib, made mainly to avoid direct socket handling
 * 
 */
/** @{ */
 
/** Create a socket from the given informations */
lsocket* make_socket(char*p_socket){
	lsocket*sck=malloc(sizeof(lsocket));
	char*addr=malloc(sizeof(char)*SIZE_BUFFER);
	if (sck==NULL) ERROR("Socket malloc impossible");
	
	/* Socket creation */
	if (access(p_socket,F_OK)==-1) mkfifo(p_socket,MODE_SOCKET);
	if (verbose>1) printf("Socket created: %s\n",p_socket);
	strcpy(addr,p_socket); sck->addr=addr;
	
	return sck;
}

/** Open the connection of the given socket */
void open_socket(lsocket*sck,int mode){
	if ((sck->file=open(sck->addr,O_RDWR,mode))<0) ERROR("Socket opening was impossible");
}

/** Close a socket connection
 * @param shutdown Is the connection to be shutdown or just delete the pointer
 */
void close_socket(lsocket*sck,int shutdown){
	close(sck->file);
	if (shutdown) unlink(sck->addr);
	free(sck);
}

/** Send string to the server */
int socket_send(lsocket*sck,char*message,int bytes){
	return write(sck->file,message,bytes);
}

/** Receive string from the server */
int socket_receive(lsocket*sck, char*message,int bytes){
	return read(sck->file,message,bytes);
}
/**@}*/

/** \defgroup Packetlib 
 * Packetlib is a small lib build ontop of liblsockets.
 * 
 * It is used extensively to avoid any interference with the implementation of the sockets.
 * The main function you should use for communication is packet_receive() and socket_message_send().
 *
 * However, the following will allow you to handle basic communication:
 * \li packet_forge()
 * \li packet_send()
 * \li packet_drop()
 *
 * Moreover, the following function should be avoided:
 * \li packet_message()
 * @{
 */

/** Sending a message, with less information to provide */
int socket_message_send(lsocket*sck,msg_type type_message,char *message){
	lpacket*pck=packet_forge(type_message,message);
	packet_send(sck,pck);
	packet_drop(pck);
	return packet_snd_bytes;
}

/** [Deprecated] Receive a message with less information to provide,
 * note that it is advised to use a packet instead.
 */
char *socket_message_receive(lsocket*sck){
	char*message=malloc(sizeof(char)*SIZE_BUFFER);
	socket_receive(sck,message,SIZE_BUFFER);
	return message;
}

/** Forge a packet with the given information.
 *
 * For memory usage reason, the message is copied not linked, free it if needed.
 */
lpacket*packet_forge(msg_type type,char *message){
	lpacket*pck=malloc(sizeof(lpacket));
	char*pck_message=malloc(sizeof(char)*(strlen(message)+1));
	if (pck==NULL) ERROR("Malloc lpacket");
	if (pck==NULL) ERROR("Malloc message");
	if (!strcmp(message,"")) pck_message[0]=42;
	else strcpy(pck_message,message);
	pck->type=type;
	pck->message=pck_message;
	return pck;
}

/** Drop a packet and free the allocated memory. */
void packet_drop(lpacket*pck){
	free(pck->message);free(pck);
}

/** Create a packet from the given message. */
lpacket*packet_request(char*message){
	int type;
	char*pck_message;
	type=atoi(strtok(message," "));
	pck_message=strtok(NULL,"\n");
	return packet_forge(type,pck_message);
}

/** Create a message from given packet. */
char *packet_message(lpacket*pck){
	int size=strlen(pck->message)+5;
	char*message=malloc(sizeof(char)*size);
	if (message==NULL) ERROR("lPacket malloc");
	sprintf(message,"%d %s\n",pck->type,pck->message);
	return message;
}

/** Send a packet through the given socket.
 *
 * Note that you will NOT receive the number of readed packets.
 * You can access that information through ::packet_snd_bytes.
 */
void packet_send(lsocket*sck,lpacket*pck){
	packet_snd_bytes=socket_send(sck,packet_message(pck),strlen(pck->message)+5);
}

/** Receive a packet through the given socket
 *
 * Note that you will receive a socket not the number of readed packets. 
 * You can access that information through packet_rcv_bytes.
 */
lpacket*packet_receive(lsocket*sck){
	char*message=malloc(sizeof(char)*SIZE_BUFFER);
	if (message==NULL) ERROR("lPacket malloc");
	packet_rcv_bytes=socket_receive(sck,message,SIZE_BUFFER);
	return packet_request(message);
}
/** }@ */
