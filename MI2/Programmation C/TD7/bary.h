/*
 * bary.h
 * This file is part of TD7
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * TD7 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * TD7 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __BARY_H__
#define __BARY_H__

/* ========= Includes =========*/

/* ========= Defines ==========*/

/* ========= Typedef ==========*/
typedef struct dot_struct
{
	double x;
	double y;
	double z;
} dot;

/* ======== Prototype =========*/
dot bary(char *stream);

#endif
