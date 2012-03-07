/*
 * tintable_lib.h
 * This file is part of Tintable
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * Tintable is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Tintable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#ifndef __tintable_H__
#define __tintable_H__

/* ========= Includes =========*/

/* ========= Defines ==========*/

/* ========= Typedef ==========*/
#define tintype char *

/* ======== Prototype =========*/
tintype tintable(int *,int);
void print_tintable(tintype,int);
char *bytemap(int);
#endif /* __tintable_H__ */
