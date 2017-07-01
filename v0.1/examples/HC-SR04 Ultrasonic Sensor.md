## HC-SR04 Ultrasonic Sensor control using sermonics.

* Upload sermonics sketch to Arduino.
* HC-SR04 connection
   * Connect Vcc to 5V pin.
   * Connect GND to GND pin.
   * Connect Trig to D5 pin.
   * Connect Echo to D6 pin.
* Open serial monitor.
   * Type `SPM D05 1; SPM D06 0; SDV D05 0;`   
   This will prepare the pins.

   * Type `SDV D05 1;DLU 10; SDV D05 0; GPI D06;`  
   If everything is connected properly, Arduino will response with something like `GPI D06 = <value>` e.g `GPI D06 = 3134`.
   Multiplying the <value> by 0.017 will return the distance in centimeters. This can be use repeatedly to get the data from the sensor.
