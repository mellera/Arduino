#include "Azione.cpp"

class Gestore {

  public:
    void inizializza() { // Azzero tutte le azioni
      for(int i = 100; i < 100; i++) {
        azioni[i].setStato(SOVRASCRIVIBILE);
      }
    }

    void aggiungiAzione(int _comando, int _durata_acceso, int _durata_spento, int _prossima_esecuzione, int _stato, int _pin_elettrovalvole[]) { // Aggiungo un'azione nel primo posto disponibile
      for(int i = 0; i < 100; i++) {
        if(azioni[i].getStato() == SOVRASCRIVIBILE) {
          azioni[i].set(_comando, _durata_acceso, _durata_spento, _prossima_esecuzione, _stato, _pin_elettrovalvole);
          break;
        }
      }
    }

    void eliminaAzione(int posizione) { // Elimino l'azione che si trova nella determinata posizione
      azioni[posizione].setStato(SOVRASCRIVIBILE);
    }

    void routine(uint32_t _now) {
      for(int i = 0; i < 100; i++) { // Ciclo sulle azioni
        azioni[i].esegui(_now); // Le eseguo passando il tempo 
      }
    }

  private:
    Azione azioni[100]; // Array di azioni corrispondenti ai programmi
    
};