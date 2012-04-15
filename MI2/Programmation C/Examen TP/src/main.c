/**
 \file main.c
 \brief Programme principal
 
 Created by Valentin Emiya on 03/04/12.
 Modified by Maximilien Rigaut 16/04/12.
 Copyright (c) 2012 LIF. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include "temperature.h"
#include "imageio.h"
#include "image_utils.h"

/** Programme principal */
int main(void)
{
	Image* image_p=pgm_read("./data/piece_vide.pgm");
	Stat_Temperature *stat=stat_temperature(image_p);
	printf("Moyenne: %f\n",stat->moyenne);
	printf("Ecart Type: %f\n",stat->ecart_type);
	
	estime_temperature(image_p,5);
	free(stat); stat=stat_temperature(image_p);
	printf("Moyenne: %f\n",stat->moyenne);
	printf("Ecart Type: %f\n",stat->ecart_type);
	pgm_write("./data/test.pgm",image_p,255);
    return 0;
}
