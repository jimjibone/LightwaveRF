LightwaveRF
===========

Arduino/Raspberry Pi library for communicating with LightwaveRF devices via 433 MHz.

Please see the original [README.md](https://github.com/roberttidey/LightwaveRF) for original history of this project.

With the use of the [wiringPi library](http://wiringpi.com/), conversion from Arduino code to Raspberry Pi C++ code was easy.


Here is a slightly old video of the TX working:

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/UApxWZYKNRU/0.jpg)](http://www.youtube.com/watch?v=UApxWZYKNRU)


Prerequisites
-------------

### Raspberry Pi

- [wiringPi](http://wiringpi.com/)
- Raspbian (tested on this but will probably work on other distros)

### Arduino

- An Arduino


Setting up your device
----------------------

### Raspberry Pi

- The default pin for TX is wiringPi pin 3, or header pin 15
- The default pin for RX is wiringPi pin 2, or header pin 13
- VCC on the modules should be connected to the 3.3V pin(s). Connecting to the 5V pins could lead to you killing your Pi. The GPIOs do not have protection from over voltage! - For this reason the RX range is quite poor. Using the 5V pin for VCC and using a level shifter down to 3.3V for the output data may help.
- See the [wiringPi/pins](http://wiringpi.com/pins/) page for more info

### Arduino

- The default pin for TX is 3 and for RX is 2


Example usage
-------------

The example code is only configured at the moment for the Raspberry Pi, but converting it to work on the Arduino will be easy.

To start off, make sure you have wiringPi installed, then run `make` in the repository directory.

Two programs will be created:

### lwtx

The library used for this, LightwaveTX.{cpp,h}, is based on [lawrie's](https://github.com/lawrie/LightwaveRF) library. Out of the two libraries, this was the best for transmitting using the Raspberry Pi during tests. It's transmission implementation is much simpler than roberttideys and doesn't require the use of hardware timers.

The `lwtx` executable is pretty much the classic blink example, using a real light rather than an LED. To run this use `sudo ./lwtx`. `sudo` is required by wiringPi to access the GPIO pins on the Raspberry Pi.

You may need to pair your device with the code that is running. If you look at the example code, `lwtx.cpp`, you will see that the device ID is hard coded at the top of the file. To pair, just follow the instructions that came with your device and make sure that you time it with the code sending the ON command. If you enable pairing mode on the device and then run the program, the first message that is sent contains the ON command.

You can change the ID to anything you like, as long as you stick to this selection of bytes: `0xF6, 0xEE, 0xED, 0xEB, 0xDE, 0xDD, 0xDB, 0xBE, 0xBD, 0xBB, 0xB7, 0x7E, 0x7D, 0x7B, 0x77, 0x6F`.

See [roberttidey's excellent write up of the protocol](https://github.com/roberttidey/LightwaveRF/blob/master/LightwaveRF433.pdf) for more information.

### lwrx

The library used for this, LightwaveRX.{cpp,h}, is based on [roberttidey's](https://github.com/roberttidey/LightwaveRF/) library. Out of the two libraries, as you can probably guess by now, this was the best for receiving, on both the Raspberry Pi and Arduino. However, the original library contains a load of EEPROM and pairing support, which just seems silly to me, these deserve to be in a separate set of files. So, I just stripped that out.

The `lwrx` executable just runs in an infinite loop, waiting for some action from the 433 MHz receiver. The receivers signal pin is set up as an interrupt using the wiringPi library, and through a timer based state-machine the message is decoded into its byte representation.

Again, see [roberttidey's excellent write up of the protocol](https://github.com/roberttidey/LightwaveRF/blob/master/LightwaveRF433.pdf) for more information.

Eventually additional functions will be added which will convert the output messages into a more understandable form, e.g. spelling out the command that was sent, dim level requested, etc.
