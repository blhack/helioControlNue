//each pin that is connected to a sparkplug gets its very own counter!  These are all offset by +8.  
//So counter[0] refers to pin 8, counter[1] refers to pin 9, etc.
int counters[6] = {0,0,0,0,0,0};

//these are the pins with buttons connected to them.  They are in an array because we will
//check them all inside of a loop.  buttons[0] will effect counters[0], buttons[1] will
//effect counters[1] and so on.
int buttons[6] = {2,3,4,5,6,7};

//how many plugs/buttons do we have?
int numPlugs = sizeof(counters);

void setup() {
  for (int i=0; i<numPlugs; i++) {
    pinMode(8+i, OUTPUT);
    digitalWrite(8+i, LOW);
  }

  for (int i=0; i<numPlugs; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
}

void loop() {
  for (int i=0; i<numPlugs; i++) {
    if (digitalRead(buttons[i]) == LOW) {
			//190 * 27 = ~5000 = 5 seconds of on time per button press
			//this is to make SURE that the propane lights.  A short burst of spark 
			//doesn't ensure ignition
      counters[i] = 190;
    }
  }
  for (int i=0; i<numPlugs; i++) {
    if (counters[i] > 0) {
      digitalWrite(i+8, HIGH);
      counters[i]--;
    }
  }
  delay(3);
  for (int i=0; i<numPlugs; i++) {
    digitalWrite(i+8, LOW);
  }
  delay(24);
}
