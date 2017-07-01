/*************************************************
    Strictly only for Arduino Uno and Nano
**************************************************/

#include <Wire.h>

#ifdef  ARDUINO_AVR_UNO
char analogPins[] = {A0, A1, A2, A3, A4, A5};
#elif ARDUINO_AVR_NANO
char analogPins[] = {A0, A1, A2, A3, A4, A5, A6, A7};
#endif



String cmd = "";

//loop delay (milliseconds)
int loopDelay = 100;

//pulseIn time out (microseconds)
long pulseInTimeOut = 20000;

//interrupt value
int intrpt = 0;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
}

void loop() {

  if (intrpt > 0) {
    Serial.println(String("INTRPT = ") + String(intrpt));
    intrpt = 0;
  }

  delay(loopDelay);
}

void serialEvent() {
  while (Serial.available()) {
    char c = Serial.read();// read the incoming data as string
    if (c == ';') {
      cmd.toUpperCase();
      processCommand(cmd);
      cmd = "";
    } else {
      cmd += c;
    }
  }
}

void processCommand(String cmd) {
  String a = String(cmd);
  int n = a.indexOf('|');
  if (n > -1) {
    a.remove(n);
  }

  a.trim();
  int pinId = 0;
  int cmdLen = a.length();
  if (cmdLen > 6) {
    pinId = getPinFromString(a, 4);
  }

  int pinIO = 0;
  if (cmdLen > 8) {
    pinIO = a.charAt(8) - '0';
  }

  if (a.startsWith("SPM")) {  ///Set pin mode
    if (pinIO == 0) {
      pinMode(pinId, INPUT);
    } else if (pinIO == 2) {
      pinMode(pinId, INPUT_PULLUP);
    } else {
      pinMode(pinId, OUTPUT);
    }

  } else if (a.startsWith("SDV")) { ///Set digital value
    digitalWrite(pinId, getLowHigh(pinIO));
  } else if (a.startsWith("GPI")) {   ///Get pulseIn value
    writeResponse(cmd, pulseIn(pinId, getLowHigh(pinIO), pulseInTimeOut));
  } else if (a.startsWith("SPT")) {   ///Set pulseIn timeout
    pulseInTimeOut = getIntFromString(a, 4);
  } else if (a.startsWith("SLD")) {   ///Set loop delay
    loopDelay = getIntFromString(a, 4);
  } else if (a.startsWith("SAV")) { ///Set analog value
    int value = getIntFromString(a, 8);
    analogWrite(pinId, value);

  } else if (a.startsWith("GDV")) {   ///Get digital value
    writeResponse(cmd, digitalRead(pinId));
  } else if (a.startsWith("GAV")) {   ///Get analog value
    writeResponse(cmd, analogRead(pinId));
  } else if (a.startsWith("DLY")) {   ///Delay
    int value = getIntFromString(a, 4);
    delay(value);
  } else if (a.startsWith("I2C ")) {   ///I2C communication
    int c = a.charAt(4) - '0';
    if (c == 1) {
      Wire.begin();
    } else if ( c == 2) {
      int addr = getByteFromString(a, 6);
      int nBytes = getByteFromString(a, 9);
      Wire.requestFrom(addr, nBytes);
      String res = String(addr);
      if (nBytes <= Wire.available())
        for ( int i = 0 ; i < nBytes; i++) {
          int reading = Wire.read();
          res += " ";
          res += reading;
        }
      writeResponse(cmd, res);

    } else if ( c == 3) {
      int addr = getByteFromString(a, 6);
      int nBytes = getByteFromString(a, 9);
      String res = String(addr);
      res += " ";
      res += nBytes;
      //Wire.beginTransmission(addr);
      for ( int i = 0 ; i < nBytes; i++) {
        int value = getByteFromString(a, 12 + (3 * i));
        res += " ";
        res += value;
        //Wire.write(byte(value));
      }
      //Wire.endTransmission();
      writeResponse(cmd, res);
    }
  } else if (a.startsWith("DLU")) {   ///Delay
    int value = getIntFromString(a, 4);
    delayMicroseconds(value);
  }  else if (a.startsWith("SEI")) {   ///Set external interrupt
    if (pinId == 2 || pinId == 3) {
      if (pinIO == 0) {
        detachInterrupt(digitalPinToInterrupt(pinId));
      } else {
        pinMode(pinId, INPUT_PULLUP);
        if (pinId == 2) {
          attachInterrupt(digitalPinToInterrupt(pinId), pin2Interrrupt, CHANGE);
        } else if (pinId == 3) {
          attachInterrupt(digitalPinToInterrupt(pinId), pin3Interrrupt, CHANGE);
        }
      }

    }
  } else if (a.startsWith("RPV")) {   ///Read port value
    char port = a.charAt(4);
    int value = 0;
    if (port == 'B') {
      value = PORTB;
    } else if (port == 'C') {
      value = PORTC;
    } else if (port == 'D') {
      value = PORTD;
    }
    writeResponse(cmd, value);
  } else if (a.startsWith("WPV")) {   ///Write port value
    char port = a.charAt(4);
    int value = getIntFromString(a, 6);
    if (port == 'B') {
      PORTB = value;
    } else if (port == 'C') {
      PORTC = (value & B00111111) | (B11000000 & PORTC) ;
    } else if (port == 'D') {
      PORTD = (value & B11111100) | (PORTD & B00000011);
    }
  } else if (a.startsWith("RDR")) {   ///Read port's direction register
    char port = a.charAt(4);
    int value = 0;
    if (port == 'B') {
      value = DDRB;
    } else if (port == 'C') {
      value = DDRC;
    } else if (port == 'D') {
      value = DDRD;
    }
    writeResponse(cmd, value);
    //writeResponse(cmd, value);
  } else if (a.startsWith("WDR")) {   ///Write port's direction register
    char port = a.charAt(4);
    int value = getIntFromString(a, 6);
    if (port == 'B') {
      DDRB = value;
    } else if (port == 'C') {
      DDRC = (value & B00111111) | (B11000000 & DDRC) ;
    } else if (port == 'D') {
      DDRD = (value & B11111100) | (DDRD & B00000011);
    }
  } else if (a.startsWith("HSI")) { ///Hardware specific instruction
    handleHSI(a);
  } else {
    writeResponse(cmd, "NOHANDLER");
  }
}

void pin2Interrrupt() {
  int value = PORTD;
  intrpt = intrpt | (value & 0x4) | ( 0x400 );
}

void pin3Interrrupt() {
  int value = PORTD;
  intrpt = intrpt | (value & 0x8) | ( 0x800 );
}

int getLowHigh(int v) {
  if ( v == 0) {
    return LOW;
  } else {
    return HIGH;
  }
}

int getPinFromString(String a, int start) {
  int  pinId = (a.charAt(start + 1) - '0') * 10 + (a.charAt(start + 2) - '0');
  if (a.charAt(start) == 'A') {
    pinId = analogPins[pinId];
  }
  return pinId;
}

long getIntFromString(String s, int start) {
  String a = String(s);
  a.remove(0, start);
  a.trim();
  return a.toInt();
}

long getByteFromString(String s, int start) {
  String a = String(s);
  a.remove(0, start);
  int b = 0;
  if (a.charAt(0) >= '0' && a.charAt(0) <= '9') {
    b +=  (a.charAt(0) - '0') << 4;
  } else if (a.charAt(0) >= 'A' && a.charAt(0) <= 'F') {
    b +=  (a.charAt(0) - 'A' + 10) << 4;
  }
  if (a.charAt(1) >= '0' && a.charAt(1) <= '9') {
    b +=  (a.charAt(1) - '0');
  } else if (a.charAt(1) >= 'A' && a.charAt(1) <= 'F') {
    b +=  (a.charAt(1) - 'A' + 10);
  }
  return b;
}

void writeResponse(String a, String response) {
  Serial.println(a + " = " + response + ";");
}

void writeResponse(String a, long response) {
  Serial.println(a + " = " + response + ";");
}


/****************************************************
   Add hardware specific instruction handling here
*****************************************************/
void handleHSI(String a) {
  if (a.startsWith("HSI USR")) {

    int pin = getPinFromString(a, 8);
    pinMode(pin, OUTPUT);

    digitalWrite(pin, LOW);
    delayMicroseconds(2);
    digitalWrite(pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pin, LOW);
    pinMode(pin, INPUT);
    int duration = pulseIn(pin, HIGH);
    writeResponse(cmd, duration);
  }
}
