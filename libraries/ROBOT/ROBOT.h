#ifndef ROBOT_H
#define ROBOT_H

/*
includo la libreria Arduino.h per poter utilizzare le funzioni base di arduino
includo anche la libreria per gestire un singolo motore
*/
#include "Arduino.h"
#include "MOTORE.h"

/*
la classe ROBOT contiene una variabile che indica la velocità minima di rotazione
dei motori e due metodi uno per inizializzare il robot e indicare i pin utilizzati
da arduino e uno per gestire il movimento.
*/
class ROBOT
{
    private:
        int para;
    public:
        void muovi(int acc, int deAcc, int sterzo, int freno, int massimo); 
        void inizia(int m1ora, int m1anti, int m1ena, int m2ora, int m2anti, int m2ena, int parametro);   
	void avanti(int ac);
	void gira(int d);   
};

#endif
