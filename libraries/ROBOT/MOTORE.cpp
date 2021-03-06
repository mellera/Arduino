#include "MOTORE.h"

/*
dichiara i pin di arduino che sono collegati all'integrato come output e manda
un segnale basso su questi tre pin
*/
void MOTORE::inizia(int ora,int an,int ena)
{
     //le prime due variabili che si passano gestiscono il senso di rotazione
     orario=ora; 
     anti=an;
     
     //la terza variabile gestisce la velocit�
     enablePin=ena;
     
     //inzializzo i pin come output
     pinMode(orario, OUTPUT);
     pinMode(anti, OUTPUT);
     pinMode(enablePin, OUTPUT);
     
     //spengo i pin per sicurezza
     digitalWrite(enablePin, LOW);
     digitalWrite(orario, LOW);
     digitalWrite(anti, LOW);
}

//gira in un senso alla velocit� vel 
void MOTORE::avanti(int vel)
{
     analogWrite(enablePin, vel);
     digitalWrite(orario, HIGH);
     digitalWrite(anti, LOW);
}

//gira nell'altro senso alla velocit� vel
void MOTORE::indietro(int vel)
{
     analogWrite(enablePin, vel);
     digitalWrite(orario, LOW);
     digitalWrite(anti, HIGH);     
}

/*
manda un segnale basso su tutti e tre i pin che gesticono il motore
consente di fermare il motore
*/
void MOTORE::freno()
{
     digitalWrite(enablePin, LOW);
     digitalWrite(orario, LOW);
     digitalWrite(anti, LOW);
}

/*
passando un valore da -255 a 255 muove il motore "in avanti" di velocit� vel se 
vel � positivo altrimenti va "all'indietro" di velocit� vel
*/
void MOTORE::muovi(int vel)
{
     //se vel � maggiore di 0 allora fa girare il motore "in avanti" di velocit� vel
     if(vel>0)
     {
          avanti(vel);
          return;
     }
     
     //se vel � minore di 0 allora fa girare il motore "all'indietro" di velocit� vel
     if(vel<0)
     {
          vel=vel*(-1);    
          indietro(vel);
          return;   
     }
     
     //se il parametro vel � uguale a zero il motore si ferma
     if(vel==0)
     {
          freno();
          return;
     }
}
