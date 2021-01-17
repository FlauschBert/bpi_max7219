# MAX7219 on the Banana Pi

7-segment-leds on the MAX7219 on the Banana Pi or Raspberry Pi (not tested).

# Motivation

Show arbitrary numbers and lettes on the 7-segment-display.

# Compile and install wiringBP library and tools

Clone the [repository](https://github.com/LeMaker/WiringBP) and run `./build`.  
This installs includes and library in */usr/local/include* and */usr/local/lib*. Binaries in the */usr/local/bin* folder.

# Compile and install

Go to the *source* directory and use the mighty force of shining CMake :D to compile the pico project.  
The *wiringPi* sub folder contains the internal interface library for the installed wiringBP library.  
Do `make install` to install the library in */usr/local*.

(I used Armbian stretch but also more recent versions should work).

# References

* [Banana Pi LED test](https://github.com/FlauschBert/bpi_led_test/blob/master/README.md) for initial setup
* [Documentation of MAX7219](https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf)
* [LedControl on GitHub](https://github.com/wayoda/LedControl)

