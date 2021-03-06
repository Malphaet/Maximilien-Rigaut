/*
 * client.h
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

#ifndef CLIENT_H
#define CLIENT_H

/* ========= Includes =========*/
#include "utils.h"
#include "liblsockets.h"

/* ======== Prototype =========*/

void 		client_socket		(char*);
lsocket** 	open_communication	();
int 		handshake			(lsocket*,lsocket**);
int			user_request		();
void 		gotcha				(int);
void 		self_terminate		();
#endif
