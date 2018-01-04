void attivaWarning() {
  digitalWrite(LED_WARNING, HIGH);
}

void disattivaWarning() {
  digitalWrite(LED_WARNING, LOW);
}

void attivaDanger() {
  digitalWrite(LED_DANGER, HIGH);
  digitalWrite(ELETTROVALVOLA_1, LOW);
  digitalWrite(ELETTROVALVOLA_2, LOW);
  digitalWrite(ELETTROVALVOLA_3, LOW);
  digitalWrite(ELETTROVALVOLA_4, LOW);
  digitalWrite(ELETTROVALVOLA_5, LOW);
}

void disattivaDanger() {
  digitalWrite(LED_DANGER, LOW);
}

