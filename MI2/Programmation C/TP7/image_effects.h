/*
 * image_effects.h
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

#ifndef __IMAGE_EFFECTS_H__
#define __IMAGE_EFFECTS_H__

/* ========= Includes =========*/

/* ========= Defines ==========*/
#include "types_image.h"

/* ========= Typedef ==========*/
/* ======== Prototype =========*/
void effect_binarization(Image *,float);	/*  */
void effect_negative(Image *);		/* Tested */
void effect_noise(Image *, float);	/* Tested */

#endif /* __IMAGE_EFFECTS_H__ */
