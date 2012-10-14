/*
 * server.c
 * This file is part of TP4
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * TP4 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * TP4 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with TP4. If not, see <http://www.gnu.org/licenses/>.
 */

/* ========= Includes =========*/
#include "bor-util.h"
#include "server.h"


/* ========= Defines ==========*/

/* =========== Main ===========*/

dictionnary **addr_book;
int verbose=0;

int main(int nbargs,char **argv){
	int p; /* Name of the current process */
	lsocket*main_sck;
	lpacket*pck;
	
	/** Checking variables */
	if (nbargs<3) OUT("Syntax incorrect\nUsage:\n  server <path_fifo> <path_dict>");
	if (nbargs>3) verbose=atoi(argv[3]);

	/** Initialisation of main variables */
	if (verbose) printf("[Server] Initialising...\n");
	main_sck=make_socket(argv[1]);
	open_socket(main_sck,S_IRUSR|S_IWUSR);
	load_dict(argv[2]);
	bor_signal(SIGCHLD,gotcha,0);
	if (verbose) printf("[Server] Initialisation done.\n");
	
	/* Server core */
	while(1){
		/* Receving request */
		if (verbose) printf("[Server] Waiting for new incoming transmissions...\n");
		pck=packet_receive(main_sck);
		
		if (pck->type!=msg_text) continue;
		if (verbose) printf("[Server] Transmission: %s\n",pck->message);
		
		/* Forking the program */
		if ((p=fork())<0) ERROR("Forking child");
		if (p) {child_socket(pck);break;}
	}
	return 0;
}

/* ========== Functions ==========*/

void gotcha(int signal){
	switch (signal){
		case SIGCHLD:
			wait(NULL);
			break;
	}
}

void child_socket(lpacket*rcv_pck){
	lsocket**sockets=create_from_feed(rcv_pck->message);
	lpacket*pck;
	char*message;
	packet_drop(rcv_pck);
	
	/* Everything went fine, proceed */
	socket_message_send(sockets[1],msg_recv,"");
	
	while(1){
		/* Wait for user request */
		pck=packet_receive(sockets[0]);
		if (verbose) printf("[%d] Received: %s\n",getpid(),pck->message);
		
		/* Analyse request */
		if (pck->type==msg_kill) break;
		if (pck->type!=msg_text) continue;
		
		/* Process it */
		message=seek_dict(pck->message);
		
		/* Send answer */
		if (verbose) printf("[%d] Answering: %s\n",getpid(),message);
		socket_message_send(sockets[1],msg_text,message);
		
		packet_drop(pck);
	}
	printf("[%d] Communication closed.\n",getpid());
	packet_drop(pck);
}

/** Create the two sockets from given request */
lsocket**create_from_feed(char*feed){
	char*sock_names[2];
	lsocket**new_sockets;
	new_sockets=malloc(sizeof(lsocket*)*2);
	if (new_sockets==NULL) ERROR("Sockets creation");
	
	/* Split sockets */
	sock_names[0]=strtok(feed,":");
	sock_names[1]=strtok(NULL,"\n");
	if (verbose) printf("[%d] Listening to sockets: %s,%s\n",getpid(),sock_names[0],sock_names[1]);
	if (!strlen(sock_names[0])|!strlen(sock_names[1])) OUT("Ill formated feed")
	
	/* Create new sockets */
	new_sockets[0]=make_socket(sock_names[1]); /**< The first socket is for reading */
	new_sockets[1]=make_socket(sock_names[0]); /**< The second socket is for writing */
	
	/* Open them */
	open_socket(new_sockets[0],S_IRUSR);
	open_socket(new_sockets[1],S_IWUSR);
	
	return new_sockets;
}

/** \defgroup Dictionnary 
 * Several lame methods for lame dictionary
 * 
 * @{
 */

/** Load a dictionnary from a file */
void load_dict(char*path){
	FILE*fd=fopen(path,"r");
	char *name,*number,buffer[SIZE_BUFFER]="";
	dictionnary**dic=malloc(sizeof(dictionnary*)*1);
	int i,lines;
	
	if (dic==NULL) ERROR("Dictionnary creation");
	if (fd==NULL) ERROR("Dictionnary file doesn't exists");
	
	lines=Salem(fd); rewind(fd);
/*	printf("%d lines in %s\n",lines,path);*/
	
	for (i=0;i<lines;i++){
		fgets(buffer,SIZE_BUFFER,fd);
		name=strtok(buffer,":"); number=strtok(NULL,"\n");
		if ((name==NULL)|(number==NULL)) ERROR("Ill formated address book");
		
		dic[i]=malloc(sizeof(dictionnary));
		dic[i]->name=malloc(sizeof(char)*strlen(name));
		dic[i]->numero=malloc(sizeof(char)*strlen(number));
		
		strcpy(dic[i]->name,name);
		strcpy(dic[i]->numero,number);
	}
	if (verbose) printf("[Server] Sucessfully read %d lines from file %s.\n",lines,path);
	addr_book=dic;
}

/** Search into the dictionnary */
char*seek_dict(char*key){
	/* Heavy search process :) */
	key++;
	return "Mooo";
}

/** Line counter by Salem */
int Salem (FILE*fd){
	int nlines=0, partial=0;
	char buff[SIZE_BUFFER] = "";
	
	while (fgets(buff,SIZE_BUFFER,fd)!=NULL){
		if (strchr(buff,'\n')){
			nlines++;
			partial = 0;
		} else partial = 1;
	}
	return nlines += partial;
}
/** @} */
