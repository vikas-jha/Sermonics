# sermonics
Sermoncs is Arduino sketch for Uno and Nano. Mnemonics over the serial port is used to control the Arduino.

### How to use
Upload the sermonics.ino file to the Arduino. Open serial monitor and type mnemonics.

### Sermonics Usage
* Refer the sermonics desciption for usage details. 
* All sermonics must end with semi-colon (;). 
* Sermonics returning value have response syntax "sermonics = value". 
* Multiple sermonics can be provided in single sentence upto 50 characters e.g. "SPM D06 1; SDV D06 1; DLY 1000; SDV D06 0;". 
* Sermonics are case-insensitive. Response will always in upper-case.

#### PIN in Sermonics
Most of the sermonics require pin value. This sketch can support D00 - D99 digital pins, but only A0-A5 analog pins are supported. Pin are specified for mnemonics using a letter for pin type (A- analog, D - digital) and two digit pin number combination. Single-digit pin number should be zero-padded. e.g. D00 , D01, D12, A05 etc.


* SPM - Set pin mode.
   SPM [PIN] [PIN_MODE];   
    PIN_MODE   
     * 0  INPUT  
     * 1  OUTPUT   
     * 2  INPUT_PULLUP  

SPM D06 1; - Sets digital pin 6 to output mode.

* SDV - Set digital value. Pin should be in output mode.
   SDV [PIN] [PIN_VALUE];   
    PIN_VALUE   
     * 0  LOW  
     * 1  HIGH   

SDV D04 1; - Sets digital pin 4 to HIGH.

* SAV - Set analog value. Only PWM output pins must be used. Pin should be in output mode.
   SAV [PIN] [ANALOG_VALUE];   
    ANALOG_VALUE  - [0 - 255]  

SAV D06 240; - Sets PWM value of digital pin 6 to 240. Analog value must be in range 0 -255.

* GDV - Get digital value. Returns digital vlue of pin. Pin should be in input mode.
   GDV [PIN]; 

GDV D04; - Gets digital pin 4 to HIGH. If D04 is high, it will return "GDV D04 = 1;". 
The value is 0 - LOW and 1 - HIGH.

* GAV - Get analog value. Only analog input pins must be used. Pin should be in input mode.
   GAV [PIN];    

GAV A03; - Get the analog value of analog pin 6. If  analog value of A04 is 1012, it will return "GAV A03 = 1012;". Analog input can have range 0 - 1024.

* DLY - Waits for given milliseconds.
   DLY [MILLISECONDS];
 
DLY 20; - waits for 20 milliseconds. 

* DLU - Waits for given microseconds.
   DLU [MICROSECONDS];
 
DLU 2000; - waits for 2000 microseconds. 

