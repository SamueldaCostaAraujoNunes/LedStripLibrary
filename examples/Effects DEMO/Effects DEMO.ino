/*
  FitaLed exemplo

  Autor: Samuel da Costa Araujo Nunes
  Abril de 2020
 */
#include<FitaLed.h>

Fita mesa(15,12,14);

void setup() {}

void loop() {
  mesa.flash();
  mesa.strobe();
  mesa.breath();
  mesa.fade();
  mesa.smooth();
  mesa.turnOn();
  mesa.turnOff();
  mesa.setTimer(10);
  mesa.setColor(210, 32, 123);
  mesa.setColor(1000000);
  mesa.setColor("FFFFFF");
  mesa.setBrightness(0.5);
}
