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
	return;
}

void inet_fath_process(){
	lsocket*serv=make_lsocket(" :8888");
	open_lsocket(serv,AF_INET,SOCK_STREAM);
	bind_lsocket(serv);
	listen_lsocket(serv);
				
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
