/*
 * lserver.c
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

#include "utils.h"
#include "libsockets.h"


int main (int argc, char *argv[]){
	socket* sck,*sockets[2];
	packet* pck;
	char*socks[2];
	
	if (argc<2) OUT("Not enought parameters");
	sck=make_socket(argv[1]);
	
	open_socket(sck,S_IRUSR);
	pck=packet_receive(sck);
	printf("Message: %s \n",pck->message);
	
	socks[0]=strtok(pck->message,":");
	socks[1]=strtok(NULL,"\n");
	printf("Sockets: %s,%s\n",socks[0],socks[1]);
	sockets[0]=make_socket(socks[0]);
	sockets[1]=make_socket(socks[1]);
	open_socket(sockets[0],S_IWUSR);
	open_socket(sockets[1],S_IRUSR);
	
	socket_message_send(sockets[0],msg_recv,"");
	while(1){
		pck=packet_receive(sockets[1]);
		printf("Received %s\n",packet_message(pck));
		socket_message_send(sockets[0],msg_text,"Moo\n");
	}
	close_socket(sck,0);
	return 0;
}
