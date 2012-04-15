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
#define SIZE 6
int main(void)
{
	int i;
	char nom[]="./data/out/0.pgm";
	Image* image_p[SIZE]={
		pgm_read("./data/config1.pgm"),
		pgm_read("./data/config2.pgm"),
		pgm_read("./data/config3.pgm"),
		pgm_read("./data/config4.pgm"),
		pgm_read("./data/config5.pgm"),
		pgm_read("./data/config6.pgm")
	};
	
	Stat_Temperature *stat[SIZE];
	
	for (i=0;i<SIZE;i+=1){
		estime_temperature(image_p[i],30);
		nom[11]='0'+i;
		pgm_write(nom,image_p[i],255);
		stat[i]=stat_temperature(image_p[i]);
		printf("Image %d:\n    Moyenne: %f\n    Ecart Type: %f\n",i,stat[i]->moyenne,stat[i]->ecart_type);
	}
	/* Le meilleur placement predefini est le 3, bien que l'ecart type le plus optimal soit celui du 1 */
	
	/* */
    return 0;
}
