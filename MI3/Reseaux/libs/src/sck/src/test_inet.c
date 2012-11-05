/*
 * test_inet.c
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

void inet_chld_process(){
	lsocket*serv=make_lsocket("127.0.0.1:8888");
	open_lsocket(serv,AF_INET,SOCK_STREAM);
	sleep(1);
	connect_lsocket(serv,NULL);
	message_send(serv,msg_text,"MOOOOO");
	close_lsocket(serv,2);
	return;
}

void inet_fath_process(){
	int optval=1;
	lpacket*pck;
	lsocket*clnt,*serv=make_lsocket(" :8888");
	open_lsocket(serv,AF_INET,SOCK_STREAM);
	setsockopt(serv->file,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(int));
	bind_lsocket(serv);
	clnt=listen_lsocket(serv);
	pck=message_receive(clnt,NULL);
	printf("[%s] %d %s\n",clnt->addr,pck->type,pck->message);
	close_lsocket(serv,2);
	return;
}

void test_network_sockets(){
	int p;
	if ((p=fork())<0) ERROR("Fork !");
	if (p) inet_fath_process();
	else{
		inet_chld_process();
	}
}
