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
	sk_addr* sck=make_socket(argv[1]);
	char message[1024];
	
	open_socket(sck,S_IRUSR);
	socket_receive(sck,message,1024);
	printf("Message: %s \n",message);
	close_socket(sck,0);
	return 0;
}
