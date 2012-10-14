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
	socket* sck;
	char message[1024];
	char*socks[2];
	socket *sockets[2];
	if (argc<2) OUT("Not enought parameters");
	sck=make_socket(argv[1]);
	
	open_socket(sck,S_IRUSR);
	socket_receive(sck,message,1024);
	printf("Message: %s \n",message);
	socks[0]=strtok(message,":");
	socks[1]=strtok(NULL,"\n");
	printf("Sockets: %s,%s\n",socks[0],socks[1]);
	sockets[0]=make_socket(socks[0]);
	sockets[1]=make_socket(socks[1]);
	open_socket(sockets[0],S_IWUSR);
	open_socket(sockets[1],S_IRUSR);
	
	socket_send(sockets[0],SOCKET_RECEIVED,1024);
	
	close_socket(sck,0);
	return 0;
}
