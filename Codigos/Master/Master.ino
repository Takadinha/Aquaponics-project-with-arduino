#include <A2a.h>
#include "config.h"
#define endereco 0x08
#define tempoAtualizacao 500
AdafruitIO_Feed *reserv = io.feed("reserv");
AdafruitIO_Feed *bomba = io.feed("bomba");
A2a arduinoSlave;
void configuraMQTT();
unsigned long controleTempo = 0;
bool estadoReserv = LOW;
bool estadoBomba = LOW;
bool estadoReservAnt = LOW;
bool estadoBombaAnt = LOW;
void setup() {
  Serial.begin(9600);
  while (! Serial);
  configuraMQTT();
  arduinoSlave.begin(0, 2);
  Serial.println("Fim Setup");
}
void loop() {
  io.run();
  if (millis() > controleTempo + tempoAtualizacao) {
    estadoReserv = arduinoSlave.varWireRead(endereco, 0);
    if (estadoReserv != estadoReservAnt) {
      reserv->save(estadoReserv);
    }
    estadoReservAnt = estadoReserv;
    estadoBomba  = arduinoSlave.varWireRead(endereco, 1);
    if (estadoBomba != estadoBombaAnt) {
      bomba->save(estadoBomba);
    }
    estadoBombaAnt = estadoBomba;
    controleTempo = millis();
  }
}
void configuraMQTT() {
  Serial.print("Conectando ao Adafruit IO");
  io.connect();
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());
}
