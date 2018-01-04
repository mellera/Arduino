/*
 Example sketch for the RFCOMM/SPP Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */
//includo la libreria per gestire il robot
#include <ROBOT.h>
#include <SPP.h>
#include <usbhub.h>

USB Usb;
USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
SPP SerialBT(&Btd,"arduino","0000"); 


//creo un oggeto ROBOT per poter comandare il robot 
ROBOT Robot;

boolean firstMessage = true;

void setup() {
  Serial.begin(115200);
  //while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nSPP Bluetooth Library Started"));
  Robot.inizia(2,4,3,6,7,5,60);  
}

byte ricevi[4];

void loop() 
{
  
  int i,acc,deAcc,sterzo;
  Usb.Task(); // The SPP data is actually not send until this is called, one could call SerialBT.send() directly as well

  if (SerialBT.connected) 
  {
    i=0;
    while (SerialBT.available())
    {
      ricevi[i]=SerialBT.read();
      i++;
    }
    acc=ricevi[0];
    deAcc=ricevi[1];
    if(ricevi[2]>0)
      sterzo=map(ricevi[2],0,255,0,32767);
    if(ricevi[3]>0)
      sterzo=map(ricevi[3],0,255,0,-32768);
    if(ricevi[2]==0 && ricevi[3]==0)
      sterzo=0;
    Robot.muovi(acc,deAcc,sterzo,0,1);
    //Serial.print("acc: ");Serial.print(acc);Serial.print("deacc: ");Serial.print(deAcc);Serial.print("sterzo: ");Serial.println(sterzo);
  }
  /*
  i=0;  
  while(i<4)
  {
    Serial.print("ricevi[");Serial.print(i);Serial.print("]= "); Serial.print(ricevi[i]);
    i++;
  }
  Serial.println();
  */
  
    
}
