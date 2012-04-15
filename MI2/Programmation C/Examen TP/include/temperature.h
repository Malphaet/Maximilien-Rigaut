/*
//  temperature.h
//  
//
//  Created by Valentin Emiya on 15/04/12.
//  Modified by Maximilien Rigaut 16/04/12.
//  Copyright (c) 2012 LIF. All rights reserved.
*/

#ifndef _temperature_h
#define _temperature_h
#include "image_types.h"

typedef void Stat_Temperature; /* A MODIFIER */

double moyenne_temperature(Image *p_image);
double ecart_type_temperature(Image *p_image);
Stat_Temperature *stat_temperature(Image *p_image);
double lancer(Image *p_image, int i, int j);
void estime_temperature(Image *p_image, int nb_lancers);

#endif
