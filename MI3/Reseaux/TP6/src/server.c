/*
 * server.c
 * 
 * Copyright 2012 Maximilien Rigaut <max[dot]rigaut[at]orange.fr>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 */
#if defined __STRICT_ANSI__ && !defined _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "server.h"
#include "liblsockets.h"
#include <signal.h>
#include "crypto.h"

#define PORT 4242
#define MAXBUFFER 16384
#define MAX_USERS 20
#define MAX_MESSAGES 1000
#define MAX_PENDING 20

struct user allusers[MAX_USERS];
struct message allmessages[MAX_MESSAGES];
struct toidentify alltoidentify[MAX_PENDING];
int nbusers,nbmessages,nbtoidentify;
volatile int should_quit;

#include "functions.c"
#include "crypto.c"

#define CATCH_SIGNALS 	new_action.sa_handler = termination_handler;\
						sigemptyset(&new_action.sa_mask);\
						new_action.sa_flags = 0;\
						sigaction(SIGTERM,&new_action,NULL);\
						sigaction(SIGINT,&new_action,NULL);\
						sigaction(SIGPIPE,NULL,NULL);

void termination_handler (int signum){
	if (signum==SIGINT||signum==SIGTERM){
		printf("\r[Server] Shutting Down...\n");
		// Send a msg_kill to everyone
		should_quit=1;
	}
}
 
int main(void){
	char buffer[SIZE_BUFFER+1];
	//char buffer2[MAXBUFFER+1] = "Welcome\n";
	int optval=1,*actives_sockets,i,id,id2;
	struct sigaction new_action;
	
	lsocket*server,*sender;
	lpodrum*sockets;
	lpacket*pck;
	/* Print informations */
	if (BUILD_NUMBER) printf("Server version %s (build:%s)\n",BUILD_VERSION,BUILD_NUMBER);
	
	/* Init usefull variables */
	nbusers=0;nbmessages=0;nbtoidentify=0;
	should_quit=0;
	
	/* Sigaction */
	CATCH_SIGNALS;

	/* Init server */
	server=make_lsocket(" :4242");
	open_lsocket(server,AF_INET,SOCK_STREAM);
	setsockopt(server->file,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(int));
	bind_lsocket(server);
	listen_lsocket(server,SIZE_PENDING);
	
	/* Start the listening poll */
	sockets=make_lpodrum(SIZE_PENDING);
	add_lsocket(sockets,server,POLLIN);
	
	/* Create some test users */
	create_user("Dave","odyssey");
	create_user("Shell","portal");
		
	/* Start server */
	printf("Starting server on port 4242\n");
	while (!should_quit){
		actives_sockets=listen_lpodrum(sockets,-1);
		
		for(i=0;actives_sockets[i]!=LPOP_ERROR;i++){
			/* 0 is the server address: new connections comes from here */
			if (actives_sockets[i]==0){
				/* Send an answer with the new connection */
				sender=accept_lsocket(server);
				add_lsocket(sockets,sender,POLLIN);
				if (create_user_toidentify(sender)<0) del_lsocket(sockets,actives_sockets[i]);
				
				SND_ACK;
				printf("Client connected %s\n",sender->addr);
				continue;
			}
			
			if (get_event(sockets,actives_sockets[i])==POLLIN){
				/* Wait for the communication */				
				pck=message_receive(get_lsocket(sockets,actives_sockets[i]),&sender);
				switch(pck->type){
					case msg_name: // Done // User wants to register to the server
						if ((id=find_socket_toidentify(sender))<0) ERROR("Zombie connection");
						if (find_user(pck->message)<0){
							MSG_CONNATMP;
							SND_CONNDENY;
							DELETE_SOCKET;
						} else {
							MSG_CONNPROG;
							SND_CONNPROC;
							strcpy(alltoidentify[id].login,pck->message);
						}
						break;
					case msg_pass: // User wants to give his passphrase
						if (((id=find_socket_toidentify(sender))<0)||((id2=find_user(alltoidentify[id].login))<0)){
							MSG_CONNPASS;
							SND_CONNDENY;
							DELETE_SOCKET;
							break;
						}
						if (strcmp(allusers[id2].passwd,lcrypt(pck->message))){
							SND_CONNDENY;
							DELETE_SOCKET;
							//add_lclist(pending_deletion,id); // Make as a function
							MSG_WRNGPASS;
						} else {
							allusers[id2].status=1; // You are connected
							MSG_USERCONN;
							SND_MSGGREET;
							//add_lclist(pending_deletion,id); // Make as a function
						}
						break;
					case msg_text:
						MSG_RECEIVED;
						// Resend the message
						break;
					case msg_kill: // User wants to DIE
						// Be verbose
						MSG_CLNTQUIT;
						SND_CLNTQUIT;
						DELETE_SOCKET;
						break;
					case msg_zero: // Client disconected (Zero bytes read)
						DELETE_SOCKET;
						MSG_CLNTQUIT;
						break;
					case msg_wtf: // Avoid that
						DELETE_SOCKET;
						WARNING("WTF Happened ?");
						break;
					default: // Even worse
						DELETE_SOCKET;
						printf("Unhandled action\n%s\n",pck->message);
						if (pck->type>msg_errors) WARNING("Unhandled error happened");
						break;
				}
				lpacket_drop(pck);
				//while ((id=pop_lclist(pending_deletion))!=LPOP_ERROR) { //Make it as a function
					//Delete the id
				//}
			}
		}
		free(actives_sockets);
	}
	drop_lpodrum(sockets,1);
	return 0;
}
