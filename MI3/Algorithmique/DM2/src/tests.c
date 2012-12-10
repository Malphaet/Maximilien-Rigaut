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
#define exec_tests printf("> Writing test results at %s\n",T_PATH);\
					printf("> Testing hash function\n");\
					test_jhash();\
					printf("> Testing hash dict building function\n");\
					test_hashtable();\
					printf("> Testing 3-tuple reduction function\n");\
					test_3tuples();

void test_jhash(){
	TIMER_INIT;
	unsigned long int res;
	unsigned int hash,i,size=18;
	char*bin,*cluster[]={
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
	T_OPEN;
	TIMER_STRT;
	
	for (i=0;i<nb_test;i+=1) jhash(val_test);
	TIMER_STOP;
	res=TIMER_USEC;
	while (size--)	{
		hash=jhash(cluster[size]);
		bin=itobin(hash,HASH_M_SIZE);
		fprintf(test,"%05x %s %s\n",hash,bin,cluster[size]);
		free(bin);
	}
	printf("Time elapsed: %li ms. Hash speed: %li hashs per ms\n",res/1000,nb_test/(res/1000));
	T_CLOSE;
}

void test_hashtable(){
	lclist**dict,*node;
	unsigned int i,j,nb=0,col,max_col=0;
	TIMER_INIT;
	unsigned int*hashs_col=calloc(10,sizeof(int));
	double fisher[]={	0.6670355074,
						0.270090681373,
						0.054681478988,
						0.00738039567332,
						0.000747102693219,
						6.05021691434e-05,
						4.08300905203e-06,
						2.36179908754e-07,
						1.19540099017e-08,
						5.37813561922e-10
					};
	T_OPEN;
	
	printf("Digesting dictionnary: ./ressources/dico.txt\n");
	TIMER_STRT;
	dict=build_hashdict("./ressources/dico.txt");	
	TIMER_STOP;
	
	for (i=0;i<HASH_DSIZ;i+=1) if(dict[i]){
		fprintf(test,"%05x %s",i,itobin(i,HASH_SIZE));
		node=dict[i];
		col=0;
		while((node=node->next)!=NULL) {
			fprintf(test," %s",(char*)node->data);
			col++;
			nb++;
		}
		for (j=0;j<col;j+=1) hashs_col[j]++;
			

		max_col=col>max_col?col:max_col;
		fprintf(test,"\n");
	}
	T_CLOSE;
	
	printf("Time elapsed: %li ms, alpha: %f, word digested: %d, worst collision: %d\n",TIMER_USEC/1000,(float)nb/HASH_DSIZ,nb,max_col-1);
	printf("Hash repartition :\nk Number    Fisher\n");
	for (i=0;i<10;i+=1){
		if (hashs_col[i]) printf("%d %6d %9.2f\n",i,hashs_col[i],fisher[i]*nb);
	}

}

void test_3tuples(){
	lclist**dict,*node;
	unsigned int i,j,nb=0,col,max_col=0;
	TIMER_INIT;
	unsigned int*hashs_col=calloc(80000,sizeof(int));
	T_OPEN;
	
	printf("Digesting dictionnary: ./ressources/dico.txt\n");
	TIMER_STRT;
	dict=build_3tupledict("./ressources/dico.txt");	
	TIMER_STOP;
	
	for (i=0;i<HASH_DSIZ;i+=1) if(dict[i]){
		fprintf(test,"%05x %s",i,itobin(i,HASH_SIZE));
		node=dict[i];
		col=0;
		while((node=node->next)!=NULL) {
			fprintf(test," %s",(char*)node->data);
			col++;
			nb++;
		}
		for (j=0;j<col;j+=1) hashs_col[j]++;

		max_col=col>max_col?col:max_col;
		fprintf(test,"\n");
	}
	T_CLOSE;
	
	printf("Time elapsed: %li ms, alpha: %f, word digested: %d, worst collision: %d\n",TIMER_USEC/1000,(float)nb/HASH_DSIZ,nb,max_col-1);
	printf("Hash repartition :\nk Number\n");
	for (i=0;i<20;i+=1){
		if (hashs_col[i]) printf("%d %6d\n",i,hashs_col[i]);
	}
}

#undef nb_test
#undef val_test
