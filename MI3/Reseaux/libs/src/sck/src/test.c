/*
 * test.c
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

void child_process(){
	char name[101];
	lsocket*chld,*serv=make_lsocket("tmp/serv");
	lpacket*pck;
	
	sprintf(name,"tmp/chld_%d",getpid());
	chld=make_lsocket(name);
	
	open_lsocket(chld,AF_UNIX,SOCK_DGRAM);
	open_lsocket(serv,AF_UNIX,SOCK_DGRAM);
	bind_lsocket(chld);
	
	/* Hardcore setup actions */
	srand(getpid());
/*	sleep(rand()%4);*/
	
	/* Handshake */
	message_send(serv,msg_sync,"",chld);
	pck=message_receive(chld,NULL);
	printf("[%d] %i %s\n",getpid(),pck->type,pck->message);
	
	/* Hardcore actions again */
/*	sleep(rand()%4);*/
	
	/* Send results */
	message_send(chld,msg_text,"Here I am",chld);
	
/*	pck=message_receive(chld,NULL);*/
/*	printf("[%d] %i %s\n",getpid(),pck->type,pck->message);*/
	close_lsocket(serv,0);
	close_lsocket(chld,1);
	
	exit(EXIT_SUCCESS);
}

void father_process(){
	lsocket*serv=make_lsocket("tmp/serv");		/* Listener */
	lsocket*sndr=malloc(sizeof(lsocket));	/* Replyto */
	
	int*actives,i=0;
	lpacket*pck;
	lpodrum*podr=make_lpodrum(20,0);
	
	open_lsocket(serv,AF_UNIX,SOCK_DGRAM);
	bind_lsocket(serv);
	
	add_lsocket(podr,serv);
	while (1){
		actives=listen_lpodrum(podr,-1);
		for(i=0;actives[i]>=0;i++) {
			printf("Waiting for %s:%d\n",get_lsocket(podr,actives[i])->addr,actives[i]);
			pck=message_receive(get_lsocket(podr,actives[i]),sndr);
			
			/* 0 is the server address: new connections comes from here*/
			if (i==0 && pck->type==msg_sync) {
				add_lsocket(podr,sndr);
				message_send(sndr,msg_recv,"",NULL);
			}
			
			printf("[%s:%d] %i %s\n", sndr->addr ,(int)sndr->file,pck->type,pck->message);
		}
		free(actives);
	}
	close_lsocket(serv,1);
	close_lsocket(sndr,0);
}

int main (){
	int p;
	p=fork();
	if (p) father_process();
	else {
		fork();
		fork();
		child_process();
	}
	return 0;
}


