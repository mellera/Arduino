void attivaLogger() {
  if (DEBUG) {
    Serial.begin(9600);
    while (!Serial);
  }
}

void logger(char text[]) {
  if (DEBUG) {
    Serial.println(text);
  }
}

void logger(String text) {
  if (DEBUG) {
    Serial.println(text);
  }
}

void logger(uint32_t text) {
  if (DEBUG) {
    Serial.println(text);
  }
}

void attivaWarning() {
  digitalWrite(LED_WARNING, HIGH);
}

void disattivaWarning() {
  digitalWrite(LED_WARNING, LOW);
}

void attivaDanger() {
  digitalWrite(LED_DANGER, HIGH);
  digitalWrite(ELETTROVALVOLA_1, LOW);
}

void disattivaDanger() {
  digitalWrite(LED_DANGER, LOW);
}

// in base alla lettura del pot restituisce un valore scala linearizzata
int calcolaZona(int lettura) {
  if (lettura < 55) {
    return 8;
  } else if(lettura >= 55 && lettura < 225) {
    return 7;
  } else if(lettura >= 225 && lettura < 375) {
    return 6;
  } else if(lettura >= 375 && lettura < 510) {
    return 5;
  } else if(lettura >= 510 && lettura < 640) {
    return 4;
  } else if(lettura >= 640 && lettura < 795) {
    return 3;
  } else if(lettura >= 795 && lettura < 970) {
    return 2;
  } else {
    return 1;
  }
}

