/*
 * server.h
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

#include "liblsockets.h"

int sk_find(lsocket**,char*,int);
int sk_delete(lsocket**,char*,int);
void broadcast(lsocket**,struct player,int);
