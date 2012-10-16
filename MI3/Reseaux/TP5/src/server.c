/*
 * server.c
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

#include "server.h"
#define MAX_CLIENTS 10
int verbose=1;

int main (int argc, char *argv[]){
	lsocket*server;
	
	lpacket*pck;
	struct player playa;
	
	int connected=0;
	lsocket*clients[MAX_CLIENTS];
/*	struct player players[MAX_CLIENTS];*/
	
	if (argc<2) OUT("Incorrect usage, usage: server <listening address>");
	
	server=make_lsocket(argv[1]);
	open_lsocket(server,AF_UNIX,SOCK_DGRAM,1);
	
	while (1){
		pck=lpacket_receive(server);
		
		/* Nouvelle connection */
		if (pck->type==msg_sync){
			if (!sk_find(clients,pck->message,connected)){
				clients[connected++]=make_lsocket(pck->message);
				open_lsocket(clients[connected-1],AF_UNIX,SOCK_DGRAM,0);
				if (verbose) printf("[Server] New client connected %s\n",pck->message);
			}
			else printf("[Server] Error %s already exists\n",pck->message);
		} 
		else {
			if (pck->type==msg_text){
				playa.name=strtok(pck->message," ");
				playa.x=atoi(strtok(NULL," "));
				playa.y=atoi(strtok(NULL," "));
				playa.pv=atoi(strtok(NULL," "));
				broadcast(clients,playa,connected);

			} else {
				if (pck->type==msg_kill){
					printf("[%s] Disconnected\n",pck->message);
					sk_delete(clients,pck->message,connected);
					connected--;
				} else printf("Unsuspected behavior %i %s",pck->type,pck->message);
			}
		}
		lpacket_drop(pck);
	}
	

	close_lsocket(server,1);
	return 0;
}

void broadcast(lsocket**clients,struct player playa,int connected){
	int i; char message[SIZE_BUFFER];
	sprintf(message,"[%s] (x,y):(%d,%d) PV:%d\n",playa.name,playa.x,playa.y,playa.pv);
	printf("%s",message);
	for (i=0;i<connected;i+=1) if (strcmp(playa.name,clients[i]->addr)!=0)lsocket_message_send(clients[i],msg_text,message);
}


int sk_find(lsocket**clients,char*client,int size){
	int i;
	for (i=0;i<size;i+=1) if (strcmp(clients[i]->addr,client)==0) return 1;
	return 0;
	
}

int sk_delete(lsocket**clients,char*client,int size){
	int i,j;
	for (i=0;i<size;i+=1) if (strcmp(clients[i]->addr,client)==0) {
		for (j=0;j<size;j+=1) clients[i+1]=clients[i];
		return j;
	}
	return 0;
}
