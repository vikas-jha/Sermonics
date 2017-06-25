## LED control using sermonics.

* Upload sermonics to Arduino.
* Connect LED to pin 6. 
   Use blue or white LED, if not connecting resistor.
   * positive (longer pin) of LED to pin 6.
   * negative (shorter pin) of LED to GND.
   * (optional) 100 ohm resistor can be added between pin 6 and LED. 
* Open serial monitor.
   * Type `SPM D06 1; SDV D06 1; DLY 5000; SDV D06 0;`   
   LED should turn on, stay on for 5 seconds and then turn off.

__For below part led must be connected on PWM pin. D06 is PWM pin.__  

   * Type `SAV D06 100;`  
   LED should glow dimly.
   
   * Type `SAV D06 255;`   
   LED should glow bighter.
   
   * Type `SAV D06 0;`   
   LED should turn off.
   
   Values between 0 - 255 can be passed to `SAV` and led's bightness will vary accordingly.
   
