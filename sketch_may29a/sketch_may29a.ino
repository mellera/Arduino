#include <MsTimer2.h>
#include <time.h>
#include <TimeLib.h>

time_t tempo;

void setup() {  

  MsTimer2::set(10000, runtime); // 60000ms period
  MsTimer2::start();

  Serial.begin(9600);

  tempo = (unsigned long) 0;

}

void runtime() {
  String minuti = "minuti ";
  String secondi = " secondi ";
  Serial.println(minuti + minute(tempo) + secondi + second(tempo));
  tempo = (time_t) ((unsigned long) tempo + 10);
}

void loop() {
  
}
