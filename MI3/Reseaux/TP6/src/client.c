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

#include <time.h>
#include <stdio.h>
#include "client.h"
#include <sys/wait.h>
#define _POSIX_C_SOURCE	199309L
#define ADRESS "127.0.0.1:4242"


int main(){
	lsocket*serv=make_lsocket(ADRESS);
	lpacket*pck;
	int p;
	
	/* Open sockets */
	open_lsocket(serv,AF_INET,SOCK_STREAM);
	connect_lsocket(serv,NULL);
	
	/* Handshake */
	FPRINT("Establishing connection...");
	message_send(serv,msg_sync,"bitopode:rugissant");
	pck=message_receive(serv,NULL);
	printf("done !\n%s\n",pck->message);
	lpacket_drop(pck);
	
	/* Minimal client */
	if ((p=fork())<0) ERROR("Forking error dude");
	if (!p){
		/* Listening process */
		while (1){
			pck=message_receive(serv,NULL);
			printf("\r%s\n",pck->message);
			if (pck->type!=msg_text) break;
			lpacket_drop(pck);
		}
		close_lsocket(serv,0);
		lpacket_drop(pck);
		return 0;
	}
	
	/* Sending process */
	#define SEND(msg) usleep(42); message_send(serv,msg_text,msg);
	SEND("Hello");
	SEND("Hello again");
	
	/* Quit */
	WHERE;
	sleep(1);
	message_send(serv,msg_kill,"Ciao");
	waitpid(p,NULL,0);
	//close_lsocket(serv,0);
	return 0;
}
