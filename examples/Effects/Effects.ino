/*
  Effects.ino
  Author: Samuel da Costa Araujo Nunes
  Date: April 2020
  Version: v0.1
 */
#include <LedStrip.h>

//Tip, test each effect individually
void setup() {
  LED stripLed(5, 4, 16);//Insert here the pins of the led strip, rgb respectively.
}

void loop() {
  //stripLed.fade();//Effect. Alternates fluidly across the color spectrum.
  //stripLed.flash();//Effect. Switch between RGB and CMY color patterns.
  //stripLed.breath();//Effect. It causes the notion of pulsation or breathing.
  //stripLed.smooth();//Effect. Brief flashes between RGB colors.
  //stripLed.on();//Turn on the led strip
  //stripLed.off();//Turn off the led strip
  //stripLed.notification(0,255,0);//Pulse notification of cores (Passed by parameter).
  //stripLed.printColors();//Prints colors on the terminal
  //stripLed.setTimer(50);//Defines a time, which determines the duration of the effects
  //stripLed.setColor(234, 213, 175);//Change the color of the led strip and update the actual color value(Using the rgb standard).
  //stripLed.setColor(3093151);//Change the color of the LED track and update the real value of the color (using the decimal pattern).
  //stripLed.setColor("ff00ff");//Change the color of the led strip and update the actual color value (using the hexadecimal pattern).
}
