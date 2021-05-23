#include <A2a.h>
#define endereco 0x08
#define pinSensorTanque 11
#define pinSensorReserv 12
#define pinRele   8 
#define pinAlerta 3 
bool estadoTanque = HIGH;
bool estadoReserv = HIGH;
A2a arduinoMaster;
void setup() {
  arduinoMaster.begin(endereco);
  arduinoMaster.onReceive(receberDados);
  arduinoMaster.onRequest(enviarDados);
  pinMode(pinSensorTanque, INPUT_PULLUP);
  pinMode(pinSensorReserv, INPUT_PULLUP); 
  pinMode(pinRele, OUTPUT); 
  pinMode(pinAlerta, OUTPUT); 
  Serial.begin(9600);
}
void loop() {
  estadoTanque = !digitalRead(pinSensorTanque);
  estadoReserv = !digitalRead(pinSensorReserv);
  if (estadoReserv) {
     if (estadoTanque) {
        digitalWrite(pinRele, LOW);
        arduinoMaster.varWireWrite(1, LOW);
     }
     else {
        digitalWrite(pinRele, HIGH);
        arduinoMaster.varWireWrite(1, HIGH);
     }
     digitalWrite(pinAlerta, LOW);
     arduinoMaster.varWireWrite(0, LOW);
  }
  else {
     digitalWrite(pinRele, LOW);
     arduinoMaster.varWireWrite(1, LOW);
     digitalWrite(pinAlerta, HIGH);
     arduinoMaster.varWireWrite(0, HIGH); 
  }
}
void receberDados() {
  arduinoMaster.receiveData(); 
}
void enviarDados() {
  arduinoMaster.sendData(); 
}
