/*
 *    MAX7219.cpp - A library for controling Leds with a MAX7219/MAX7221
 *    Copyright (c) 2007 Eberhard Fahle
 * 
 *    Permission is hereby granted, free of charge, to any person
 *    obtaining a copy of this software and associated documentation
 *    files (the "Software"), to deal in the Software without
 *    restriction, including without limitation the rights to use,
 *    copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following
 *    conditions:
 * 
 *    This permission notice shall be included in all copies or 
 *    substantial portions of the Software.
 * 
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *    OTHER DEALINGS IN THE SOFTWARE.
 */

#include <wiringPi.h>

#include "ledcontrol.h"

// from Arduino.h
#define LSBFIRST 0
#define MSBFIRST 1

//the opcodes for the MAX7219
#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

namespace {

// from ArduinoCore-avr/cores/arduino/wiring_shift.c
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
	uint8_t i;

	for (i = 0; i < 8; i++)  {
		if (bitOrder == LSBFIRST) {
			digitalWrite(dataPin, val & 1);
			val >>= 1;
		} else {	
			digitalWrite(dataPin, (val & 128) != 0);
			val <<= 1;
		}

		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);		
	}
}

} // anonymous

namespace ledcontrol {

MAX7219::MAX7219(int dataPin, int clkPin, int csPin, int numDevices) {
	SPI_MOSI=dataPin;
	SPI_CLK=clkPin;
	SPI_CS=csPin;

	if(numDevices<=0 || numDevices>8 )
		numDevices=8;
	maxDevices=numDevices;

	pinMode(SPI_MOSI,OUTPUT);
	pinMode(SPI_CLK,OUTPUT);
	pinMode(SPI_CS,OUTPUT);

	digitalWrite(SPI_CS,HIGH);

	SPI_MOSI=dataPin;
	for(int i=0;i<64;i++) 
		status[i]=0x00;
	for(int i=0;i<maxDevices;i++) {
		spiTransfer(i,OP_DISPLAYTEST,0);
		//scanlimit is set to max on startup
		setScanLimit(i,7);
		//decode is done in source
		spiTransfer(i,OP_DECODEMODE,0);
		clearDisplay(i);
		//we go into shutdown-mode on startup
		shutdown(i,true);
	}
}

void MAX7219::shutdown(int device, bool b) {
	if(device<0 || device>=maxDevices)
		return;
	if(b)
		spiTransfer(device, OP_SHUTDOWN,0);
	else
		spiTransfer(device, OP_SHUTDOWN,1);
}

void MAX7219::setScanLimit(int device, int limit) {
	if(device<0 || device>=maxDevices)
		return;
	if(limit>=0 && limit<8)
		spiTransfer(device, OP_SCANLIMIT,limit);
}

void MAX7219::setIntensity(int device, int intensity) {
	if(device<0 || device>=maxDevices)
		return;
	if(intensity>=0 && intensity<16)	
		spiTransfer(device, OP_INTENSITY,intensity);
}

void MAX7219::clearDisplay(int device) {
	int offset;

	if(device<0 || device>=maxDevices)
		return;

	offset=device*8;
	for(int i=0;i<8;i++) {
		status[offset+i]=0;
		spiTransfer(device, i+1,status[offset+i]);
	}
}

void MAX7219::setDigit(int device, int digit, uint8_t value) {
	int offset;
	if(device<0 || device>=maxDevices)
		return;
	if(digit<0 || digit>7)
		return;
	offset=device*8;
	status[offset+digit]=value;
	spiTransfer(device, digit+1,status[offset+digit]);
}

void MAX7219::spiTransfer(int device, volatile uint8_t opcode, volatile uint8_t data) {
	//Create an array with the data to shift out
	int offset=device*2;
	int maxuint8_ts=maxDevices*2;

	for(int i=0;i<maxuint8_ts;i++)
		spidata[i]=(uint8_t)0;
	//put our device data into the array
	spidata[offset+1]=opcode;
	spidata[offset]=data;
	//enable the line 
	digitalWrite(SPI_CS,LOW);
	//Now shift out the data 
	for(int i=maxuint8_ts;i>0;i--)
		shiftOut(SPI_MOSI,SPI_CLK,MSBFIRST,spidata[i-1]);
	//latch the data onto the display
	digitalWrite(SPI_CS,HIGH);
}    

} // ledcontrol

