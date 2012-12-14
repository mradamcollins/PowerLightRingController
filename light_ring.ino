#include <avr/interrupt.h>

volatile boolean stateChanged = false;

int mode_1_delay = 50; //msec

void setup() {     
  // initialise intterupt for button 
  attachInterrupt(0,flagChange, FALLING);
    
  // initialize the digital pins as an output.
  for (int led = 2 ; led <=16 ; ++led)
  {
    pinMode(led, OUTPUT);     
  }
}

void flagChange()
{
  // Flag State Changed
  stateChanged = true;
}

void loop() {
    
  //Mode 1 - spinning lights 
  stateChanged = false;
  while(!stateChanged) {
    
    digitalWrite(14, HIGH); // blue lights on
    for (int led = 2 ; (led <= 7 || stateChanged); ++ led) {
      digitalWrite(led, HIGH);       // set the inner LEDs on
      digitalWrite(led + 6, HIGH);   // set the outter LEDs on
      delay(mode_1_delay);           // wait 
      digitalWrite(led, LOW);        // set the inner LEDs off
      digitalWrite(led + 6, LOW);    // set the outter LEDs off
      delay(mode_1_delay);           // wait 
    }
  } // end Mode 1
  
  // Mode 2
  stateChanged = false;
  while(!stateChanged) {
   int rInc = random(50);
   int gInc = random(50);
   int bInc = random(50); 
   int rVal = 0;
   int gVal = 0;
   int bVal = 0;
   for (int i = 1 ; i < 500; ++i) { //5secs with 10 msec delay in loop
    rVal += rInc;
    if (rVal > 255) rVal = 255 - rVal;
    gVal += gInc;
    if (gVal > 255) gVal = 255 - gVal;
    bVal += bInc;
    if (bVal > 255) bVal = 255 - bVal;
    
    analogWrite(15,rVal);
    analogWrite(16,gVal);
    analogWrite(14,bVal);
    delay(10); 
   }
  } // end Mode 2
}
