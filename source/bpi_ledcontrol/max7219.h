/*
 *    LedControl.h - A library for controling Leds with a MAX7219/MAX7221
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
#pragma once

#include <cstdint>

namespace bpi_ledcontrol {

class MAX7219 {
		/* The array for shifting the data to the devices */
		uint8_t spidata[16];
		/* Send out a single command to the device */
		void spiTransfer(int device, uint8_t opcode, uint8_t data);

		/* We keep track of the led-status for all 8 devices in this array */
		uint8_t status[64];
		/* Data is shifted out of this pin*/
		int SPI_MOSI;
		/* The clock is signaled on this pin */
		int SPI_CLK;
		/* This one is driven LOW for chip selectzion */
		int SPI_CS;
		/* The maximum number of devices we use */
		int maxDevices;

	public:
		/* 
		 * Create a new controler 
		 * Params :
		 * dataPin		(MOSI) pin on the Arduino where data gets shifted out
		 * clockPin		(SCLK) pin for the clock
		 * csPin		  (CE/CS) pin for selecting the device 
		 * numDevices	maximum number of devices that can be controled
		 */
		MAX7219(int dataPin, int clkPin, int csPin, int numDevices=1);

		/* 
		 * Set the shutdown (power saving) mode for the device
		 * Params :
		 * device	The deviceess of the display to control
		 * status	If true the device goes into power-down mode. Set to false
		 *		for normal operation.
		 */
		void shutdown(int device, bool status);

		/* 
		 * Set the number of digits (or rows) to be displayed.
		 * See datasheet for sideeffects of the scanlimit on the brightness
		 * of the display.
		 * Params :
		 * device	deviceess of the display to control
		 * limit	number of digits to be displayed (0..7)
		 */
		void setScanLimit(int device, int limit);

		/* 
		 * Set the brightness of the display.
		 * Params:
		 * device		the deviceess of the display to control
		 * intensity	the brightness of the display. (0..15)
		 */
		void setIntensity(int device, int intensity);

		/* 
		 * Switch all Leds on the display off. 
		 * Params:
		 * device	deviceess of the display to control
		 */
		void clearDisplay(int device);

		/* 
		 * Set all 8 Led's in a row to a new state
		 * Params:
		 * device	number of the display (2 blocks with 4 digits each)
		 * digit  which is to be set (0..7)
		 * value	each bit set to 1 will light up the
		 *		    corresponding Led.
		 */
		void setDigit(int device, int digit, uint8_t value);
};

} // bpi_ledcontrol

