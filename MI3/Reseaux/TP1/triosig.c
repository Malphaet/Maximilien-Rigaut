/*
 * triosig.c
 * This file is part of triosig
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * triosig is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * triosig is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with triosig. If not, see <http://www.gnu.org/licenses/>.
 */

/* ========= Includes =========*/

#include <bor-util.h>

/* ========= Defines ==========*/
int child(int);
void handler(int);

/* =========== Main ===========*/
int REFER_PID=0; /* PID du referant */
int OWN_PID=0;

int main(void){
	int p1,p2,stat;
	OWN_PID=getpid();
	printf("Master %d : Waiting...\n",getpid());
	
	p1=fork();
	if (p1==0) child(OWN_PID);
	p2=fork();
	if (p2==0) child(p1);
	
	REFER_PID=p2;
	bor_signal(SIGUSR1,handler,0);
	bor_signal(SIGALRM,handler,0);
	
	sleep(1);
	kill(REFER_PID,SIGUSR1);
	
	wait(&stat);
	return 0;
}

/* ========= Functions ========*/
/* fils */
int child(int p){
	bor_signal(SIGUSR1,handler,0);
	bor_signal(SIGALRM,handler,0);
	REFER_PID=p;
	OWN_PID=getpid();
	printf("Child %d: Waiting... (Referer: %d)\n",getpid(),REFER_PID);
	while (1){
		sleep(1);
	}
	exit(0);
}

void handler(int sig){
	if (sig==SIGUSR1){
		printf("%d : Keep-alive received.\nSending keep-alive to %d...\n",OWN_PID,REFER_PID);
		sleep(1);
		alarm(4);
		kill(REFER_PID,SIGUSR1);
		return;
	}
	if (sig==SIGALRM){
		printf("%d : Exiting (Ping timeout).\n",OWN_PID);
		exit(-1);
	}
}
