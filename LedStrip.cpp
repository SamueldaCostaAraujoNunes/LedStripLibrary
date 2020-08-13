/*
  LedStrip.cpp

  Author: Samuel da Costa Araujo Nunes
  Date: April 2020
  Version: v0.1
 */

#include "Arduino.h"
#include "LedStrip.h"

/* Class constructor */
Fita::Fita(int redPin, int greenPin, int bluePin){
	posFlash=0;
	posFade=0;
	posSmooth=0;

	effectBool = false;
	modeEffect = 0;

	rPin = redPin;//Sets the pins
	gPin = greenPin;
	bPin = bluePin;
	
	red = 255;//Sets the colors
	green = 255;
	blue = 255;

	rE=0;
	gE=0;
	bE=0;
	
	bright = 1.0;//Set the bright
	timer = 40;//Set the timer
	state = false;//Set state initial
 }
void Fita::setupFita(){
	analogWriteRange(255);//Defines a PWM interval of 255
	pinMode(rPin, OUTPUT);//Pin initialization
	pinMode(gPin, OUTPUT);
	pinMode(bPin, OUTPUT);
}

void Fita::effect(int effectParam){
	effectBool = true;
	modeEffect = effectParam;
	state = true;
}
void Fita::activeEffect(){
	if (effectBool && state){
		switch (modeEffect){
			case 0:
				convertColor(red, green, blue);
				effectBool = false;
			break;
			case 1:
				breath();
			break;
			case 2:
				fade();
			break;
			case 3:
				smooth();
			break;
			case 4:
				flash();
		}
	}
}

void Fita::flash(){
	showColorModes(255,0,0);//Red
	delay(timer*10);
	showColorModes(0,255,0);//Green
	delay(timer*10);
	showColorModes(0,0,255);//Blue
	delay(timer*10);
	showColorModes(255,255,0);//Yellow
	delay(timer*10);
	showColorModes(255,0,255);//Magenta
	delay(timer*10);
	showColorModes(0,255,255);//Cyan
	delay(timer*10);
	showColorModes(255,255,255);//White
	delay(timer*10);

}
void Fita::breath(){//Breathing mode, the brightness of the led strip, will vary its items slowly rising and falling.
	float i = bright;//The maximum brightness of the effect is the brightness chosen by the user.
	for(i = bright; i > 0; i = i-0.05){//Decreasing
		showColorModes(red, green, blue, i);
		delay(timer);
	}
	digitalWrite(rPin, LOW);//Turn it off
	digitalWrite(gPin, LOW);
	digitalWrite(bPin, LOW);
	delay(timer*4);
	i=0;
	for(i = 0; i < bright; i = i+0.05){//Increasing
		showColorModes(red, green, blue, i);
		delay(timer);
	}
	delay(timer*14);
}
void Fita::fade(){
	int r, g, b, aux;
	switch (posFade){
		case 0:
			r = 255;//Start with red
			g = 0;
			b = 0;
			aux = 255;
			convertColor(r,g,b);
			for(aux = 255; aux > 0; aux--){//Reduces red and increases green
				r = aux;
				g = 255 - aux;
				showColorModes(r,g,b);
				delay(timer/3);
			}
			rE = r;
			gE = g;
			bE = b;
			posFade++;
		break;
		case 1:
			r=0;
			g=255;
			b=0;
			convertColor(r,g,b);
			for(aux = 0; aux < 256; aux++){//Decrease green and increase blue
				b = aux;
				g = 255 - aux;
				showColorModes(r,g,b);
				delay(timer/3);
			}
			rE = r;
			gE = g;
			bE = b;
			posFade++;
		break;
		case 2:
			r=0;
			g=0;
			b=255;
			convertColor(r,g,b);
			for(aux = 255; aux > 0; aux--){// Decrease blue and increase red.
				b = aux;
				r = 255 - aux;
				g = 0;
				showColorModes(r,g,b);
				delay(timer/3);
			}
			rE = r;
			gE = g;
			bE = b;
			posFade = 0;
		break;
	}
}
void Fita::smooth(){
	showColorModes(255,0,0);//Changing the color to Red
	delay(timer);
	showColorModes(0,255,0);//Changing the color to Green
	delay(timer);
	showColorModes(0,0,255);//Changing the color to Blue
	delay(timer);
}
void Fita::notification(int pR,int pG,int pB){//Receive the colors that you must notify by parameter
	int r = red;//Saves the current colors of the led strip
	int g = green;
	int b = blue;

	setColor(pR,pG,pB);

	if(state){//turns the tape on and off several times to report something.
		off();
		on();
		off();
		on();
		off();
		on();
		setColor(r,g,b);
		show();
	}else{
		on();
		off();
		on();
		off();
		on();
		off();
		setColor(r,g,b);
	}
}

void Fita::on(){
	if(!state){//If turned off
		if(!effectBool){
			float i = 0;
			for(i = 0; i < bright; i = i+0.1){//The brightness of the led strip will gradually increase to the maximum brightness
				showColorModes(red, green, blue, i);
				delay(timer);
			}
		}else{
			convertColor(red, green, blue);
		}
		state = true;//Change the state
	}
}
void Fita::off(){
	if(state){//If turned on
		if(!effectBool){
			float i = bright;
			for(i = bright; i > 0; i = i-0.1){//The brightness of the led strip gradually decreases to the minimum brightness
				showColorModes(red, green, blue, i);
				delay(timer);
			}
			digitalWrite(rPin, LOW);//Turn it off
			digitalWrite(gPin, LOW);
			digitalWrite(bPin, LOW);
		}else{
			convertColor(0,0,0);
			digitalWrite(rPin, LOW);//Turn it off
			digitalWrite(gPin, LOW);
			digitalWrite(bPin, LOW);
		}
		state = false;//Change the state
	}
}
void Fita::show(){
	if(state){//If connected
		int r = (int) map((analogRead(rPin)/bright), 0, 1023, 0, 255);
		int g = (int) map((analogRead(gPin)/bright), 0, 1023, 0, 255);
		int b = (int) map((analogRead(bPin)/bright), 0, 1023, 0, 255);

		float rDif = (r - red)/10;//It will generate a value corresponding to the difference between the old and the current, and divide by 10.
		float gDif = (g - green)/10;
		float bDif = (b - blue)/10;
		int i =0;	
		for (i = 1; i < 11; ++i){//He made a gradual change between one color and another
			r += (int) rDif;
			g += (int) gDif; 
			b += (int) bDif;
			showColorModes(r, g, b);
			delay(timer);
		}
		showColorModes(red, green, blue);

	}else{//If disconnected
		on();//Change the colors and turn on the led strip.
	}	
	state = true;//Att state.
}

void Fita::showColorModes(int r, int g, int b){//toggles the visible colors, but does not change the control variables. Function used in the effects.
	float rF = bright*r;
	float gF = bright*g;
	float bF = bright*b;
	
	analogWrite(rPin, (int) rF);
	analogWrite(gPin,(int) gF);
	analogWrite(bPin,(int) bF);

	rE = r;
	gE = g;
	bE = b;
}
void Fita::showColorModes(int r, int g, int b, float alpha){//toggles the visible colors, but does not change the control variables. Function used in the effects.
	float rF = alpha*r;
	float gF = alpha*g;
	float bF = alpha*b;
	
	analogWrite(rPin, (int) rF);
	analogWrite(gPin,(int) gF);
	analogWrite(bPin,(int) bF);

	rE = r;
	gE = g;
	bE = b;
}

void Fita::printColors(){//Prints the current color and brightness
	Serial.print("Color: ");
	Serial.print(red);
	Serial.print(",");
	Serial.print(green);
	Serial.print(",");
	Serial.println(blue);
	Serial.print("Brightness: ");
	Serial.println(bright);
}

void Fita::setEffectState(bool state){
	effectBool = state;
}

void Fita::setColor(int r, int g, int b){//Changes like cores
	red = r;
	green = g;
	blue = b;
}
void Fita::setColor(int decimalColor){//Converts decimal to rgb standard
	String hexstring =  String(decimalColor, HEX);
	hexstring = "#" + hexstring;
	int number = (int) strtol( &hexstring[1], NULL, 16);
	int r = number >> 16;
	int g = number >> 8 & 0xFF;
	int b = number & 0xFF;

	setColor(r,g,b);
}
void Fita::setColor(String hexadecimalColor){//Converts hexadecimal to rgb standard
	String hexstring = "#" + hexadecimalColor;
	int number = (int) strtol( &hexstring[1], NULL, 16);
	int r = number >> 16;
	int g = number >> 8 & 0xFF;
	int b = number & 0xFF;
	setColor(r,g,b);
}

void Fita::setTimer(int t){//Interval update
	timer = t;
}

void Fita::setBrightness(float brightness){//Updates the brightness of the led strip
	bright = brightness;
	setColor(red,green,blue);
}

void Fita::convertColor(int pR, int pG, int pB){
	if(effectBool){
		float rDif = (pR - rE)/10;//It will generate a value corresponding to the difference between the old and the current, and divide by 10.
		float gDif = (pG - gE)/10;
		float bDif = (pB - bE)/10;
		int i =0;	
		for (i = 1; i < 11; ++i){//He made a gradual change between one color and another
			rE = rE + (int) rDif;
			gE = gE + (int) gDif;
			bE = bE + (int) bDif;
			showColorModes(rE, gE, bE);
			delay(timer);
		}
	}else{
		float rDif = (pR - red)/10;//It will generate a value corresponding to the difference between the old and the current, and divide by 10.
		float gDif = (pG - green)/10;
		float bDif = (pB - blue)/10;
		int i =0;	
		for (i = 1; i < 11; ++i){//He made a gradual change between one color and another
			red = red + (int) rDif;
			green = green + (int) gDif;
			blue = blue + (int) bDif; 
			showColorModes(red, green, blue);
			delay(timer);
		}
	}
}

int * Fita::getColors(){
	return {red,green,blue};
}

bool Fita::getState(){
	return state;
}
