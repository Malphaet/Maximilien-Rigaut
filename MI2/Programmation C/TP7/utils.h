/*
 * utils.h
 * This file is part of TP7
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * TP7 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * TP7 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __UTILS__
#define __UTILS__
/* ========= Defines ==========*/

#define P_TEST(p) if ((p)==NULL) {printf("Error in file %s.\n    > function:%s - line:%d\n    > NULL pointer error\n",__FILE__, __func__,__LINE__); exit(EXIT_FAILURE);}

#endif
