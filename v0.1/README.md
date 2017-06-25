# Sermonics V0.1
Sermoncs is Arduino sketch for Uno and Nano. Sermonics stand for serial mnenonics. Mnemonics over the serial port, are used to control the Arduino. This is targeted for getting started with Arduino, without having to upload sketch for every minor change. After uploading this sketch port operations can be controlled using serial I/O. Serail I/O can be managed using Serial Monitor, USB programs / programming, Wireless, Bluetooth etc.  

__*Refer to [warnings](#warnings) and [limitations](#limitations) at the bottom, before use.*__

## How to use
Upload the sermonics.ino file (from v0.1 folder) to the Arduino Uno or Nano. Open serial monitor and start typing sermonics.

### Sermonics Usage

---
* Refer the sermonics desciption for usage details. 
* All sermonics must end with semi-colon (;). 
* Sermonics returning value have response syntax `sermonics = value;`. 
* Multiple sermonics can be provided in single sentence upto 50 characters.
    `"SPM D06 1; SDV D06 1; DLY 1000; SDV D06 0;"` 
* Sermonics are case-insensitive, but space sensitive.
* Response will always in upper-case.
* Sermonics may have extra information for identification after '&#124;'e.g. `SPV D06 1 | 16;`
* An unhandled sermonics will return `sermonics = NOHANDLER;`

### PIN in Sermonics

---
Most of the sermonics require pin. This sketch can support D00 - D99 digital pins, but only A0-A5 analog pins are supported. Pin are specified for mnemonics using a letter for pin type (A- analog, D - digital) and two digit pin number combination. Single-digit pin number should be zero-padded. e.g. D02 , D03, D12, A05 etc.

### Basic Sermonics

---
* __SPM [PIN] [PIN_MODE];__  - Set pin mode.   
       PIN_MODE
     * 0 - INPUT  
     * 1 - OUTPUT   
     * 2 - INPUT_PULLUP   
     
  ```SPM D06 1;``` - Sets digital pin 6 to output mode.

---
* __SDV [PIN] [DIGITAL_VALUE];__ - Set digital value. Pin should be in output mode.      
    DIGITAL_VALUE   
     * 0 - LOW  
     * 1 - HIGH   

  ```SDV D04 1;``` - Sets digital pin 4 to HIGH.
  
---
* __SAV [PIN] [ANALOG_VALUE];__ - Set analog value. Only PWM output pins must be used. Pin should be in output mode.  
        
    ANALOG_VALUE  - [0 - 255]  

   ```SAV D06 240;``` - Sets PWM value of digital pin 6 to 240.  
   Analog value must be in range 0 -255.  
   
---
* __GDV [PIN];__ - Get digital value. Returns digital value of pin. Pin should be in input mode.  
     

  ```GDV D04;``` - Gets the value of digital pin 4. If D04 is high, it will return `GDV D04 = 1;`. 
  The value is 
  * 0 - LOW 
  * 1 - HIGH.
  
---
* __GAV [PIN];__ - Get analog value. Only analog input pins must be used. Pin should be in input mode.     

  ```GAV A03;``` - Get the analog value of analog pin 6. If  analog value of A03 is 1012, it will return `GAV A03 = 1012;`.    
  Analog input can  have range 0 - 1023.
  
---
* __DLY [MILLISECONDS];__  - Waits for given milliseconds.  
 
   ```DLY 20;``` - waits for 20 milliseconds. 
   
---
* __DLU [MICROSECONDS];__ - Waits for given microseconds.  
    
  ```DLU 2000;``` - waits for 2000 microseconds.   
  
---

### Advance Sermonics
---
* __GPI [PIN] [DIGITAL_VALUE];__ - Gets length of pulse. Same as pulseIn().   
   DIGITAL_VALUE
     * 0 - LOW  
     * 1 - HIGH  
    
  ```GPI D08 1;``` - Returns the length of next HIGH pulse on digital pin 8. 20000 microseconds is timeout period. If pulse is longer, returns 0.   
  
---

* __SPT [MICROSECONDS];__ - Sets pulseIn() timeout in microseconds.
    
  ```SPT 10000;``` - Sets pulseIn timeout to 10000 microseconds.
  
---

* __SEI [PIN] [ENABLE];__ - Enables external interrupt on pin D02 and/or D03. These are pin change interrupt. __Only pin D02 or D03 must be used.__    
    ENABLE  
     * 0 - Disable interrupt  
     * 1 - Enable interrupt
     
  ```SEI D02 1;``` - Enable external interrupt on pin D02. If pin D02 changes from LOW to HIGH, it will send `INTRPT = 1028`. 
  The response is two byte data. Higher order bits contain pins. For `INTRPT = <value>` the information can be extracted as:
  
| Test           | If true                  | If false                |
| :------------- |:-------------------------| :-----------------------|
| value && 0x400 | Interrupt on D02         | D02 not interrupted     |
| value && 0x4   | D02 value change to HIGH | D02 value change to LOW | 
| value && 0x800 | Interrupt on D03         | D03 not interrupted     |
| value && 0x8   | D03 value change to HIGH | D03 value change to LOW |

---

## Warnings 
* Do not modify digital pin 0 and 1 (pins D00 and D01). Serial communication may stop working.
* If using I2C, don't modify A0 and A1 (pins A00 and A01). I2C may stop working.
* This sketch doesn't check for safety or validity of sermonics.
* Using invalid command might stop arduino and reset might be required.

## Limitations
* I2C is not supported.
* Microsecond accuracy is not available. Accuracy only upto milliseconds is available.
* Communication is asynchronous.
