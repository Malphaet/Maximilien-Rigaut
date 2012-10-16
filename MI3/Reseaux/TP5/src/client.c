/*
 * client.c
 * This file is part of TP5
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * TP5 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * TP5 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with TP5. If not, see <http://www.gnu.org/licenses/>.
 */
 
#define _POSIX_SOURCE
#include <signal.h>
#include <sys/signal.h>
#include <sys/types.h>
#include "client.h"
#define SIZE_NAME 108
int verbose=1;

int main (int argc, char *argv[]){
	lsocket*c_sck,*s_sck; lpacket*pck;
	int p;
	char name[SIZE_NAME];
	char touche;
	char message[SIZE_BUFFER];
	struct player playa;
	int quit=0,error;
	
	if (argc<2) OUT("Usage client <addresse server>");
	
	/* Init */
	sprintf(name,"tmp/%d.sock",getpid());
	c_sck=make_lsocket(name);
	s_sck=make_lsocket(argv[1]);
	
	playa.name=name;
	playa.x=0; playa.y=0;
	playa.pv=10;
	
	open_lsocket(s_sck,AF_UNIX,SOCK_DGRAM,0);
	open_lsocket(c_sck,AF_UNIX,SOCK_DGRAM,1);
	
	/* Connection au server */
	lsocket_message_send(s_sck,msg_sync,name);
	if ((p=fork())<0) ERROR("fork...");
	/* FATHER */
	if (p){
	while (1){
		touche=(char) getc(stdin);
		error=0;
		switch (touche){
			case 'z':
				playa.y-=1;
				break;
			case 's':
				playa.y+=1;
				break;
			case 'q':
				playa.x-=1;
				break;
			case 'd':
				playa.x+=1;
				break;
			case 'p':
				quit=1;
				break;
			default:
				error=1;
				break;
		}
		if (error) continue;
		if (quit){
			lsocket_message_send(s_sck,msg_kill,name);
			break;
		}
		sprintf(message,"%s %d %d %d",playa.name,playa.x,playa.y,playa.pv);
		lsocket_message_send(s_sck,msg_text,message);
	}
	kill(p,SIGKILL);
	close_lsocket(c_sck,1);
	close_lsocket(s_sck,0);
	} /* END FATHER */
	/* CHILD */
	else{
	while (1){
		pck=lpacket_receive(c_sck);
		if (pck->type==msg_text) printf("%s\n",pck->message);
		lpacket_drop(pck);
	}
	}/* END CHILD */
	return 0;
}
