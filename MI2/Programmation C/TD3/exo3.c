/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* Model                       */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include "exo3.h"

/* ========= Defines ==========*/

/* =========== Main ===========*/

int main(void){
	Heure heure={4,45,42};
	Heure heure2=ajouteHeure(heure,12+14*60+60*60);
	Timestamp T1,T2;
	Date date={10,jan,1337},date2={24,dec,1789};
	
	T1.date=date;T1.heure=heure;
	T2.date=date2;T2.heure=heure2;
	
	afficheHeure(heure);
	afficheHeure(heure2);
	
	printf("%d\n",compareHeures(heure,heure2));
	
	printf("%d\n",compareDates(date2,date2));
	
	printf("%d\n",compareTimestamps(T1,T2));
	
	return 0;
}

/* ========= Functions ========*/

void afficheHeure(Heure heure){
	printf("It's now: %d:%d:%d\n",heure.heures,heure.minutes,heure.secondes);
}

int compareHeures(Heure H1, Heure H2){
	int diff=HOURTOINT(H1)-HOURTOINT(H2);
	return DIFF(diff);
}

Heure ajouteHeure(Heure heure, int secondes){
	int s,m,h;
	Heure heure2=heure;
	secondes+=HOURTOINT(heure);
	h=secondes/(60*60);
	m=(secondes-h*60*60)/60;	
	s=(secondes-h*60*60-m*60);

	heure2.heures=h;
	heure2.minutes=m;
	heure2.secondes=s;
	
	return heure2;
}

int compareDates(Date D1, Date D2){
	int diff=DATETOINT(D1)-DATETOINT(D2);
	return DIFF(diff);
}

int compareTimestamps(Timestamp T1,Timestamp T2){
	int diff=DATETOINT(T1.date)*60*60*24+HOURTOINT(T1.heure)-DATETOINT(T2.date)*60*60*24-HOURTOINT(T2.heure);
	return DIFF(diff);
}
