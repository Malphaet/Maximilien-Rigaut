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

#define SEND(msg) {nanosleep(&delay,NULL); message_send(serv,msg_text,msg);}
#define GET(msg)  {if (fgets(msg,SIZE_BUFFER-1,stdin)==NULL) ERROR("What did you do dude ?");}


int main(){
	lsocket*serv=make_lsocket(ADRESS);
	lpacket*pck;
	char message[SIZE_BUFFER],user[SIZE_BUFFER];
	int p;
	struct timespec delay; delay.tv_sec = 0; delay.tv_nsec = 2000000L;
  
    
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
	GET(user); user[strlen(user)-1]=0;
	message_send(serv,msg_name,user);
		
	/* Minimal client */
	if ((p=fork())<0) ERROR("Forking error dude");
	if (!p){
		/* Listening process */
		while (1){
			pck=message_receive(serv,NULL);
			
			switch (pck->type){
				case msg_text:
					printf("\r%s\n",pck->message);
					break;
				case msg_pass: /* Identification */
					printf("\r%s\n",pck->message);
					printf("> Password: ");
					GET(message);
					message_send(serv,msg_pass,lcrypt(message));
					pck=message_receive(serv,NULL);
					lpacket_drop(pck);
					break;
				default:
					printf("Unhandled mode !");
					kill(getppid(),SIGKILL);
					goto quit;
			}
		}
		
		quit:
			close_lsocket(serv,0);
			lpacket_drop(pck);
			return 0;
	}
	
	/* Sending process */
	while (1) {
		GET(message);
		if (!strcmp(message,"!quit\n")) {
			WHERE;
			break;
		}
		SEND(message);
	}
	
	/* Quit */
	message_send(serv,msg_kill,"Ciao");
	//sleep(1); kill(p,SIGKILL);
	waitpid(p,NULL,0);
	close_lsocket(serv,0);
	return 0;
}
