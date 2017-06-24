# sermonics
Sermoncs is Arduino sketch for Uno and Nano. Mnemonics over the serial port is used to control the Arduino.

### How to use
Upload the sermonics.ino file to the Arduino. Open serial monitor and type mnemonics.

### Mnemonics Usage

#### PIN in mnemonics
Most of the mnemonics require pin value. This sketch can support D00 - D99 digital pins, but only A0-A5 analog pins are supported. Pin are specified for mnemonics using a letter for pin type (A- analog, D - digital) and two digit pin number combination 
i.e. D00 , D01, D12, A05 etc.


* SPM - Set pin mode.
   SPM [PIN] [PIN_MODE]   
    PIN_MODE   
     * 0  INPUT  
     * 1  OUTPUT   
     * 2  INPUT_PULLUP   
e.g. SPM D06 1 - Sets digital pin 6 to output mode. 

