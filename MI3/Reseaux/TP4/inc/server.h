/*
 * server.h
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

#ifndef SERVER_H
#define SERVER_H
/* ========= Includes =========*/
#include "utils.h"
#include "liblsockets.h"

/* ========= Defines ==========*/

/* ========= Typedef ==========*/

/* Structs */
struct dict{
	char *name;
	char *numero;
};

typedef struct dict dictionnary;


/* ======== Prototype =========*/
void		child_socket		(lpacket*);
lsocket**	create_from_feed	(char*);
void		load_dict			(char*);
char*		seek_dict			(char*);
void 		self_terminate		();
void		gotcha				(int);
int			Salem 				(FILE*); /* Line count */
#endif
