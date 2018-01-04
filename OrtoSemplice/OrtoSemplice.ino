#include <MsTimer2.h>
#include "Gestore.cpp"

uint32_t tempo = 0;
uint32_t lastInterrupt = 0;

Gestore manager;

void setup() {

  // Creo il timer gli associo il periodo e la funzione da eseguire
  MsTimer2::set(PERIODO_ESECUZIONE_ROUTINE * 1000, routine);

  // Definisco gli OUTPUT
  pinMode(LED_WARNING, OUTPUT);
  pinMode(LED_DANGER, OUTPUT);
  pinMode(ELETTROVALVOLA_1, OUTPUT);

  // Definisco gli INPUT
  pinMode(BOTTONE, INPUT);

  attivaWarning();

  if(DEBUG) {
    Serial.begin(9600);
    while (!Serial);
    Serial.println("Comunicazione seriale attivata");
    Serial.println("Inizializzo manager");
  }  

  // Inizializzo il manager
  manager.inizializza();

  if(DEBUG) {
    Serial.println("Collego interrupt");  
  }

  // Collego interrupt sul bottone
  attachInterrupt(BOTTONE, interrupt, RISING);

  if(DEBUG) {
    Serial.println("Avvio timer");
  }

  // Avvio il timer
  MsTimer2::start();

  disattivaWarning();
  
}

void routine() {

  attivaWarning();
  
  // Il managare esegue la routine
  manager.routine(tempo);  

  // Incremento il tempo
  tempo = tempo + PERIODO_ESECUZIONE_ROUTINE;

  if(DEBUG) {
    Serial.println(tempo); 
  }

  disattivaWarning();
  
}

void interrupt() {

  cli();

  // Aggiunto per non permettere click consecutivi
  if(lastInterrupt < (tempo - PERIODO_ESECUZIONE_ROUTINE)) {

    // Definisco la zona di tempo
    int zona = calcolaZona(analogRead(POTENZIOMETRO)); //map(analogRead(POTENZIOMETRO), 0, 1023, NUMERO_DIVISIONI_POT, 1);

    // Calcolo i secondi di elettrovalvola aperta
    uint32_t acceso = zona * ((MAX_PERIODO_ACCESO * 60) / NUMERO_DIVISIONI_POT);

    if(DEBUG) {
      String sZona = "zona: ";
      String sAccesoS = " secondi: ";
      String sAccesoM = " minuti: ";
      String result = sZona + zona + sAccesoS + acceso + sAccesoM + (acceso / 60);  
      Serial.println(result);
    }

    // Aggiungo l'azione al manager
    int elettrovalvole[N_ELETTROVALVOLE] = {ELETTROVALVOLA_1};
    manager.aggiungiAzione(ACCENDI, acceso, 0, tempo, UNA_VOLTA, elettrovalvole);
    
    lastInterrupt = tempo;
  
  }  
  
  sei();  
  
}

void loop() {}
