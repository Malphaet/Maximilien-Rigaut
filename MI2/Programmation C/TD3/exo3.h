/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* Model                       */
/*-----------------------------*/
#ifndef EXO3_H
#define EXO3_H

/* ========= Defines ==========*/
#define HOURTOINT(H) ((H).heures*60*60+(H).minutes*60+(H).secondes)
#define DATETOINT(D) (((D).mois+1)*30+(D).jour+(D).annee*365)
#define DIFF(diff) ((!(diff))?0:((diff)>0?1:-1))

/* ========= Typedef ==========*/

struct s_hour{
	int heures;
	int minutes;
	int secondes;
};

enum month {jan,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec};

struct date{
	int jour;
	enum month mois;
	int annee;
};


typedef struct s_hour Heure;
typedef struct date Date;

struct timestamp{
	Heure heure;
	Date date;
};

typedef struct timestamp Timestamp;

/* ======== Prototype =========*/
void afficheHeure(Heure heure);
Heure ajouteHeure(Heure heure, int secondes);
int compareHeures(Heure H1, Heure H2);
int compareDates(Date D1, Date D2);
int compareTimestamps(Timestamp T1,Timestamp T2);

#endif
