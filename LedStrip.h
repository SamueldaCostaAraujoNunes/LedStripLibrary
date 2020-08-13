/*
  LedStrip.h

  Author: Samuel da Costa Araujo Nunes
  Date: April 2020
  Version: v0.1
 */

#ifndef LedStrip
#define LedStrip

#include "Arduino.h"

class Fita{
    public:
      Fita(int redPin, int greenPin, int bluePin);//Constructor. The parameters receive the pins for each color of the ribbon.
      void setupFita();
      bool getState();// Returns the current state of the tape, on or off.
      void effect(int effectParam);//Active mode effect
      void activeEffect();//
      void flash();//Effect. Switch between RGB and CMY color patterns.
      void breath();//Effect. It causes the notion of pulsation or breathing.
      void fade();//Effect. Alternates fluidly across the color spectrum.
      void smooth();//Effect. Brief flashes between RGB colors.
      void on();//Turn on the led strip
      void off();//Turn off the led strip
      void notification(int pR,int pG,int pB);//Pulse notification of cores (Passed by parameter).
      void printColors();//Prints colors on the terminal
      void setTimer(int timer);//Defines a time, which determines the duration of the effects
      void setColor(int r, int g, int b);//Change the color of the led strip and    update the actual color value(Using the rgb standard).
      void setColor(int decimalColor);//Change the color of the LED track and update the real value of the color (using the decimal pattern).
      void setColor(String hexadecimalColor);//Change the color of the led strip and update the actual color value (using the hexadecimal pattern).
      void setBrightness(float brightness);//Changes the brightness of the led strip, which varies between 0 and 1.0.
      void setEffectState(bool state);
      void show();
      int * getColors();//Return color red(0-255)
    private:
      int posFlash, posFade, posSmooth;
      bool effectBool;//Effect current state
      int modeEffect;//
      int rPin, gPin, bPin;//Led strip pins
      int red, green, blue;//Current colors
      int rE, gE, bE;// Color effect
      int timer;//Current time.
      bool state;//Current state.
      float bright;//Current bright
      void showColorModes(int r, int g, int b);//Function used to change colors within modes. (RGB)
      void showColorModes(int r, int g, int b, float alpha);//Function used to change colors within modes. (RGBA)
      void convertColor(int pR, int pG, int pB);//

};

#endif
