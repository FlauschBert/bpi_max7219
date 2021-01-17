
#include <wiringPi.h>
#include <ledcontrol.h>
#include <digit.h>
#include <binary.h>

using namespace ledcontrol;

int main ()
{
	wiringPiSetup ();

	MAX7219 lc (
		12 /*dataPin MOSI*/,
		14 /*clkPin SCLK*/,
		10 /*csPin CE0/CS0*/,
		1  /*numDevices*/
	);

  /*
   The MAX7219 is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,1);
  /* and clear the display */
  lc.clearDisplay(0);

	lc.setDigit(0,7,toDigit('<'));
	lc.setDigit(0,6,toDigit('>'));
	lc.setDigit(0,5,toDigit('g'));
	delay(5000 /*ms*/);

  lc.clearDisplay(0);

	return 0;
}
