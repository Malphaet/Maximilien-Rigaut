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
	lsocket*chld=make_lsocket("child");
	lsocket*serv=make_lsocket("serv");
	open_lsocket(chld,AF_UNIX,SOCK_DGRAM);
	open_lsocket(serv,AF_UNIX,SOCK_DGRAM);
	bind_lsocket(chld);
/*	printf("%s\n",((struct sockaddr_un*)chld->socket)->sun_path);*/
	message_send(chld,1,"Moo",serv);

	close_lsocket(serv,0);
	close_lsocket(chld,1);
}

void father_process(){
	lsocket*serv=make_lsocket("serv");
	lsocket*chld=malloc(sizeof(lsocket));
	lpacket*pck;
	open_lsocket(serv,AF_UNIX,SOCK_DGRAM);
	bind_lsocket(serv);

	printf("%p:%s (%d)\n",(void*)chld,chld->addr,(int)chld->file);
	pck=message_receive(serv,chld);

	printf("%p:%s (%d) %i %s \n",(void*)chld,chld->addr,(int)chld->file,pck->type,pck->message);
	
	close_lsocket(serv,1);
	close_lsocket(chld,0);
}

int main (){
	int p;
	p=fork();
	if (p) father_process();
	else child_process();
	return 0;
}


