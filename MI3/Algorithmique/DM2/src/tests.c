/*
 * tests.c
 * This file is part of Algorithms
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * Algorithms is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Algorithms is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Algorithms. If not, see <http://www.gnu.org/licenses/>.
 */

/* Test functions */
#define nb_test 10000000
#define val_test "*"
#define T_PATH "./tmp/tests.txt"
#define T_OPEN FILE*test=fopen(T_PATH,"w+"); if (test==NULL) ERROR("Cannot open test file");
#define T_CLOSE fclose(test);
void test_jhash(){
	TIMER_INIT;
	int i;unsigned long int res;
	char*cluster[]={
					"Dark Angels",
					"Emperor's Children",
					"Iron Warriors",
					"White Scars",
					"Space Wolves",
					"Imperial Fists",
					"Night Lords",
					"Blood Angels",
					"Iron Hands",
					"World Eaters",
					"Ultramarines",
					"Death Guard",
					"Thousand Sons",
					"Sons of Horus",
					"Word Bearers",
					"Salamanders",
					"Raven Guard",
					"Alpha Legion"};
	int size=18;
	TIMER_STRT;
	T_OPEN;
	
	for (i=0;i<nb_test;i+=1) jhash(val_test);
	TIMER_STOP;
	res=TIMER_USEC;
	while (size--)	fprintf(test,"%05x %s %s\n",jhash(cluster[size]),itobin(jhash(cluster[size]),HASH_SIZE),cluster[size]);
	printf("Time elapsed: %li ms. Hash speed: %li h/ms\n",res/1000,nb_test/(res/1000));
}

void test_hashtable(){
	lclist**dict,*node;
	int i;
	TIMER_INIT;
	T_OPEN;
	TIMER_STRT;
	dict=build_hashdict("./ressources/dico.txt");
	TIMER_STOP;
	
	for (i=0;i<HASH_DSIZ;i+=1) if(dict[i]){
		fprintf(test,"%05x %s",i,itobin(i,HASH_SIZE));
		node=dict[i];
		while((node=node->next)!=NULL) fprintf(test," %s",node->data);
		fprintf(test,"\n");
	}
	T_CLOSE;
	
	
	printf("Time elapsed: %li ms\n",TIMER_USEC/1000);
}
#undef nb_test
#undef val_test
