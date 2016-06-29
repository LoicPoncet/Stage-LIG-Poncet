#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

typedef enum{START,STOP} EtatTimer;

typedef struct{
	struct timeval *start;
	struct timeval *stop;
	double valeur;
	EtatTimer etat;
}Timer;

Timer *initialiserTimer();
void freeTimer(Timer *t);
void startTimer(Timer *t);
void stopTimer(Timer *t);
double getTimerValue(Timer *t);

#endif //TIMER_H_INCLUDED
