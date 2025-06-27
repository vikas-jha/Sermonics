# Sermonics
Sermonics is Arduino sketch for Uno and Nano. Sermonics stand for serial mnenonics. Mnemonics over the serial port, are used to control the Arduino. This is targeted for getting started with Arduino, without having to upload sketch for every minor change. After uploading this sketch, port operations can be controlled using serial I/O. Serial I/O can be managed using Serial Monitor, USB programs or programming, Wireless, Bluetooth etc.  

__*Refer to [warnings](#warnings) and [limitations](#limitations) at the bottom, before use.*__

## How to use
Upload the sermonics.ino file from version folder (e.g. __*[v0.1/sermonics.ino](/v0.1/sermonics.ino)*__) to the Arduino Uno or Nano. Open serial monitor and start typing sermonics. 

### Sermonics Usage

---
* __*Refer to vesion documentation for sermonics details.*__

   * [v0.1](/v0.1/README.md)
* Refer to examples in examples folder, within the version folder.
* Instructable: [Arduino-CommandLine](https://www.instructables.com/Arduino-CommandLine/)

---

## Warnings 
* Do not modify digital pin 0 and 1 (Pins D00 and D01). Serial communication may stop working.
* If using I2C, don't modify A0 and A1 (Pins A00 and A01). I2C may stop working.
* This sketch doesn't check for safety or validity of sermonics.
* Using invalid command might stop arduino and reset might be required.

## Limitations
* I2C is not supported.
* Microsecond accuracy is not available. Accuracy only upto milliseconds is available.
* Communication is asynchronous.
