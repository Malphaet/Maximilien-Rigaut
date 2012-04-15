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
	Image* image_p=pgm_read("./data/test_stats.pgm");
	affiche_image(image_p);
	printf("Moyenne: %f\n",moyenne_temperature(image_p));
	printf("Ecart Type: %f\n",ecart_type_temperature(image_p));
	
    return 0;
}
