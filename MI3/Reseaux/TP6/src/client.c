/*
 * client.c
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
#include <stdio.h>
#include <signal.h>
#include "client.h"

#define ADRESS "127.0.0.1:4242"

volatile int should_quit;

void termination_handler (int signum){
	if (signum==SIGINT||signum==SIGTERM){
		printf("\rGoodbye\n");
		should_quit=1;
	}
}

int main(){
	lsocket*serv=make_lsocket(ADRESS);
	lpacket*pck;
	int p;
	struct sigaction new_action;
	
	/* Sigaction */
	new_action.sa_handler = termination_handler;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	
	sigaction(SIGTERM,&new_action,NULL);
	sigaction(SIGINT,&new_action,NULL);
	
	/* Open sockets */
	open_lsocket(serv,AF_INET,SOCK_STREAM);
	connect_lsocket(serv,NULL);
	
	/* Handshake */
	FPRINT("Establishing connection...");
	message_send(serv,msg_sync,"bitopode:rugissant");
	pck=message_receive(serv,NULL);
	printf("done !\n%s\n",pck->message);
	lpacket_drop(pck);
	
	///* Send results */
	if ((p=fork())<0) ERROR("Forking error dude");
	if (!p){
		/* Listening process */
		while (!should_quit){
			pck=message_receive(serv,NULL);
			printf("\r%s\n",pck->message);
			lpacket_drop(pck);
		}
		exit(EXIT_SUCCESS);
	}
	
	
	message_send(serv,msg_text,"Here I am");
	message_send(serv,msg_text,"Hello again");
	//message_receive(serv,NULL);
	///* Quit */
	kill(p,SIGTERM);
	message_send(serv,msg_kill,"Ciao");
	//printf("Exiting\n",getpid());
	
	sleep(1);
	close_lsocket(serv,0);
	return 0;
}

