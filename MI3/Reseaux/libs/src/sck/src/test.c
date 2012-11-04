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

/** @file test.c Tests
 *
 * A little test program, uncomment the part you wanna test on the main functions, and compile it with make test
 */

void child_process(){
	char name[101];
	lsocket*chld,*nserv=malloc(sizeof(lsocket)),*serv=make_lsocket("tmp/serv");
	lpacket*pck;
	
	sprintf(name,"tmp/chld_%d",getpid());
	chld=make_lsocket(name);
	
	open_lsocket(chld,AF_UNIX,SOCK_DGRAM);
	open_lsocket(serv,AF_UNIX,SOCK_DGRAM);
	bind_lsocket(chld);
	
	/* Hardcore setup actions */
	srand(getpid());
	sleep(rand()%4);
	
	/* Handshake */
	printf("[%d] Awake, sending message\n",getpid());
	message_send(serv,msg_sync,"syn",chld);
	pck=message_receive(chld,nserv);
	printf("[%d] Server answered <%i> %s\n",getpid(),pck->type,pck->message);
	close_lsocket(serv,0);
	
	/* Hardcore actions again */
	sleep(2);
	
	/* Send results */
	message_send(nserv,msg_text,"Here I am",chld);
	
	/* Quit */
	message_send(nserv,msg_kill,"Ciao",NULL);
	printf("[%d] Exiting\n",getpid());
	
	close_lsocket(nserv,0);
	close_lsocket(chld,1);
	exit(EXIT_SUCCESS);
}

void father_process(){
	lsocket*serv=make_lsocket("tmp/serv");		/* Listener */
	lsocket*sndr,*clnt;							/* Replyto */
	
	int*actives,i=0;
	unsigned int nb_clients=0;
	char name[42];
	lpacket*pck;
	lpodrum*podr=make_lpodrum(20);
	
	open_lsocket(serv,AF_UNIX,SOCK_DGRAM);
	bind_lsocket(serv);
	
	add_lsocket(podr,serv,POLLIN);
	while (1){
		actives=listen_lpodrum(podr,-1);
		for(i=0;actives[i]>=0;i++) {
			/* Create a new socket to hold the caller's socket */
			sndr=malloc(sizeof(lsocket));
			if (sndr==NULL) ERROR("Receiving malloc");
			
			/* Wait for the communication */
			printf("[Server] Waiting %s:%d\n",get_lsocket(podr,actives[i])->addr,get_lsocket(podr,actives[i])->file);
			pck=message_receive(get_lsocket(podr,actives[i]),sndr);
			printf("[Server] (%s:%d) sended <%i> %s\n", sndr->addr ,(int)sndr->file,pck->type,pck->message);
			
			/* 0 is the server address: new connections comes from here*/
			if (i==0 && pck->type==msg_sync) {
				/* Create particular socket for him (note that it is generally not usefull)*/
				sprintf(name,"tmp/nw_clnt_%d",nb_clients++);
				clnt=make_lsocket(name);
				open_lsocket(clnt,AF_UNIX,SOCK_DGRAM);
				bind_lsocket(clnt);
				add_lsocket(podr,clnt,POLLIN);
				
				/* Send an answer with the new connection */
				message_send(sndr,msg_recv,"ack",clnt);
			} else if (pck->type==msg_kill){
				/* If he wants to die, well kill it */
				del_lsocket(podr,actives[i]);
			}
			close_lsocket(sndr,0);
		}
		free(actives);
	}
	close_lsocket(serv,1);
	close_lsocket(sndr,0);
}

void test_lists(){
	lclist*liste=make_lclist();
	lclist*curr;
	add_lclist(liste,12);
	add_lclist(liste,42);
	add_lclist(liste,'$');
	
	printf("Liste contains %d elts\n",len_lclist(liste));
	curr=liste; while((curr=curr->next)!=NULL) printf("%d\n",curr->data);
	
	printf("Poped %d\n",pop_lclist(liste));
	printf("Liste contains %d elts\n",len_lclist(liste));
	
	curr=liste; while((curr=curr->next)!=NULL) printf("%d\n",curr->data);
	drop_lclist(liste);
}

void test_sockets(){
	int p;
	p=fork();
	if (p) father_process();
	else {
		fork();
		fork();
		child_process();
	}
}

int main (){
/*	test_lists();*/
	test_sockets();
	return 0;
}


