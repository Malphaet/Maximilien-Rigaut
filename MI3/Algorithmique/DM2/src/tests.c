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
#define val_test "T"
void test_jhash(){
	TIMER_INIT;
	int i;unsigned long int res;
	char*cluster[]={
/*					"A","AA","AAA","AAAA","AAAAA","AAAAAA","AAAAAAA","AAAAAAAA",*/
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
	for (i=0;i<nb_test;i+=1) jhash(val_test);
	TIMER_STOP;
	res=TIMER_USEC;
	while (size--)	printf("%05x %s %s\n",jhash(cluster[size]),itobin(jhash(cluster[size]),sizeof(unsigned int)-2),cluster[size]);
	printf("Time elapsed: %li ms. Hash speed: %li h/ms\n",res/1000,nb_test/(res/1000));
}

void test_hashtable(){
	TIMER_INIT;
	
	TIMER_STRT;
	build_hashdict("./ressources/dico.txt");
	TIMER_STOP;
	
	printf("Time elapsed: %li ms\n",TIMER_USEC/1000);
}
#undef nb_test
#undef val_test
