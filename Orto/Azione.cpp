#include "Arduino.h"
#include "Costanti.cpp"

class Azione {
  public:
    void set(int _comando, uint32_t _durata_acceso, uint32_t _periodo_ripetizione, uint32_t _prossima_esecuzione, int _stato, int _pin_elettrovalvole[]) { // Setta i parametri di un'azione
      setComando(_comando);
      setDurataAcceso(_durata_acceso);
      setPeriodoRipetizione(_periodo_ripetizione);
      setProssimaEsecuzione(_prossima_esecuzione);
      setStato(_stato);
      for(int i = 0; i < 10; i++) {
        pin_elettrovalvole[i] = _pin_elettrovalvole[i];
      }
    }
  
    void esegui(uint32_t _now) {
      if (getStato() != SOVRASCRIVIBILE) {
        // IN QUESTO CALCOLO AGGIUNGERE UN RANGE NON SOLO >=

        //se prossima_esecuzione è adesso o è compresa tra adesso e adesso - periodo routine 

        if (_now >= getProssimaEsecuzione()) { // Se il tempo della prossima esecuzione è passato o è adesso allora eseguo l'azione
          
          if (getComando() == ACCENDI) { // Se il comando è ACCENDI
            
            controllaElettrovalvole(HIGH);
  
            // Reimposto il tempo di prossima esecuzione e setto il comando a SPEGNI
            setComando(SPEGNI);
            setProssimaEsecuzione(_now + getDurataAcceso());
            
          } else if (getComando() == SPEGNI) { // Se il comando è SPEGNI
            
            controllaElettrovalvole(LOW);
    
            if(getStato() == RIPETIZIONE) { // se è un'azione che deve ripetersi
              // reimposto il tempo di prossima esecuzione e setto il comando a ACCENDI
              setComando(ACCENDI);
              setProssimaEsecuzione(_now + getPeriodoRipetizione() - getDurataAcceso());           
            } else if (getStato() == UNA_VOLTA) { // se era un'azione generata manualmente allora una volta che ho spento le elettrovalvole disattivo l'azione
              setStato(SOVRASCRIVIBILE);
            }
          }
        }  
      }    
    }

    void controllaElettrovalvole(int _state) {
      for (int i = 0; i < 10; i++) { // Ciclo sulle elettrovalvole collegate all'azione e setto uno stato alle uscite
        if(pin_elettrovalvole[i] != -1) {
          digitalWrite(pin_elettrovalvole[i], _state);  
        } 
      }
    }

    void setPeriodoRipetizione(int _periodo_ripetizione) {
      periodo_ripetizione = _periodo_ripetizione;
    }

    void setDurataAcceso(int _durata_acceso) {
      durata_acceso = _durata_acceso;
    }

    void setComando(int _comando) {
      comando = _comando;
    }

    void setProssimaEsecuzione(int _prossima_esecuzione) {
      prossima_esecuzione = _prossima_esecuzione;
    }    

    void setStato(int _stato) {
      stato = _stato;
    }

    int getStato() {
      return stato;
    }

    int getProssimaEsecuzione() {
      return prossima_esecuzione;
    }

    int getComando() {
      return comando;
    }

    int getPeriodoRipetizione() {
      return periodo_ripetizione;
    }

    int getDurataAcceso() {
      return durata_acceso;
    }

  private:
    int comando; // comando ACCENDI o SPEGNI
    uint32_t durata_acceso; // tempo di elettrovalvole aperte in secondi
    uint32_t periodo_ripetizione; // intervallo tra un'accensione e l'altra in secondi
    uint32_t prossima_esecuzione; // tempo prossima esecuzione in secondi unixtime
    int stato = 0; // 0 SOVRASCRIVIBILE 1 RIPETIZIONE 2 UNA_VOLTA
    int pin_elettrovalvole[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

};
