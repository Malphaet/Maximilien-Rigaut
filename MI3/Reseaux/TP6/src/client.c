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
#define _POSIX_C_SOURCE	199309L
#include <time.h>
#include "client.h"
#include "crypto.c"

#define ADRESS "127.0.0.1:4242"
#define QUIT "!quit\n"

#define MAX(a,b) (a)>(b)?(a):(b)
#define SEND(msg) {nanosleep(&delay,NULL); message_send(serv,msg_text,msg);}
#define GET(msg)  do{if (fgets(msg,SIZE_BUFFER-1,stdin)==NULL) ERROR("Error waiting for user message");\
					msg[MAX(strlen(msg)-1,0)]='\0';}while(0);


int main(){
	lsocket*serv=make_lsocket(ADRESS);
	lpacket*pck;
	char message[SIZE_BUFFER],user[SIZE_BUFFER];
	int p=0;
	struct timespec delay; delay.tv_sec = 0; delay.tv_nsec = 2000000L;

	/* Print informations */
	if (BUILD_NUMBER) printf("Client version %s (build:%s)\n",BUILD_VERSION,BUILD_NUMBER);
	printf("%s\n",BUILD_VERSION);
	/* Open sockets */
	open_lsocket(serv,AF_INET,SOCK_STREAM);
	connect_lsocket(serv,NULL);
	
	/* Wait for reply */
	FPRINT("[HAL] Establishing connection...");
	pck=message_receive(serv,NULL);
	printf("done !\n%s\n",pck->message);
	lpacket_drop(pck);
	
	
	/* Connecting */
	printf("[HAL] Good evening user.\n > Please identify yourself: ");
	GET(user);
	message_send(serv,msg_name,user);
		
	/* Minimal client */
	
	while (1){
		pck=message_receive(serv,NULL);
		
		switch (pck->type){
			case msg_text:
				printf("\r%s\n",pck->message);
				break;
			case msg_pass: /* Identification */
				printf("%s\n > Password: ",pck->message);
				lpacket_drop(pck);
				GET(message);
				message_send(serv,msg_pass,lcrypt(message));
				pck=message_receive(serv,NULL);
				
				if (pck->type==msg_kill) goto quit;
				if (!p) if ((p=fork())<0) ERROR("Forking error dude");
				if (p) goto sending_process; // Sending Process
				break; // Stay receiving
			case msg_kill: /* Quit */
				printf("\r%s\n",pck->message);
				if (p) kill(p,SIGKILL);
				goto quit;
			case msg_zero: // Server disconeted
				printf("[HAL] I know that you were planning to disconnect me\n");
				if (p) kill(p,SIGKILL);
				goto quit;
			default:
				printf("Unhandled mode !\n");
				if (p) kill(p,SIGKILL);
				goto quit;
		}
		lpacket_drop(pck);
	}

	sending_process:
		//lpacket_drop(pck);
		while (1) {
			printf("%s> ",user);
			GET(message);
			if (!strcmp(message,"!quit")) {
				WHERE;
				break;
			}
			SEND(message);
		}
	
	quit:
		lpacket_drop(pck);
		close_lsocket(serv,0);
		return 0;

	
	/* Sending process */
	
	
	
	/* Quit */
	message_send(serv,msg_kill,"Ciao");
	//sleep(1); kill(p,SIGKILL);
	waitpid(p,NULL,0);
	close_lsocket(serv,0);
	return 0;
}
