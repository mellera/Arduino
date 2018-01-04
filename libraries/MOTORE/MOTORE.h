#ifndef MOTORE_H
#define MOTORE_H

//includo la libreria Arduino.h per poter utilizzare le funzioni base di arduino
#include "Arduino.h"

/*
creo la classe motore contenente tre variabili che indicano i pin con cui arduino
si collega all'L293DNE e i metodi (funzioni) per poter controllare il movimento
del motore
*/
class MOTORE
{
    private:
	    int orario;
	    int anti;
        int enablePin;
        
    public:
        void muovi(int vel);
        void inizia(int ora, int an, int ena);
        void freno();
        void avanti(int vel);
        void indietro(int vel);        
};

#endif    	
