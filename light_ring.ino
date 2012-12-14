#include <avr/interrupt.h>

volatile boolean stateChanged = false;

int rPin = 15;  // R
int gPin = 16;  // G
int bPin = 14;  // B

int mode_1_delay = 50; //msec

void setup() {     
  // Setup random 
  randomSeed();
  
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
void allOff() {
  for (int i = 2; i <=16; ++i) {
    digitalWrite(i,LOW);
  }
}

void allOn() {
  for (int i = 2; i <=16; ++i) {
    digitalWrite(i,HIGH);
  }
}

void loop() {
    
  //Mode 1 - spinning lights Blue lights on
  stateChanged = false;
  allOff();
  while(!stateChanged) {
    
    digitalWrite(bPin, HIGH); // blue lights on
    
    for (int led = 2 ; (led <= 7 || stateChanged); ++ led) {
      digitalWrite(led, HIGH);       // set the inner LEDs on
      digitalWrite(led + 6, HIGH);   // set the outter LEDs on
      delay(mode_1_delay);           // wait 
      digitalWrite(led, LOW);        // set the inner LEDs off
      digitalWrite(led + 6, LOW);    // set the outter LEDs off
      delay(mode_1_delay);           // wait 
    }
  } // end Mode 1
  
  // Mode 2 - random RGB values
  stateChanged = false;
  allOff();
  while(!stateChanged) {
   
   int rInc = random(50);
   int gInc = random(50);
   int bInc = random(50); 
   int rVal = 0;
   int gVal = 0;
   int bVal = 0;
   int innerPin = random(6) + 2;
   int outterPin = random(6) + 8;
   digitalWrite(innerPin,HIGH);
   digitalWrite(outterPin,HIGH);
   for (int i = 1 ; (i < 500 || stateChanged); ++i) { //5secs with 10 msec delay in loop
    rVal += rInc;
    if (rVal > 255) rVal = rVal - 255;
    gVal += gInc;
    if (gVal > 255) gVal = gVal - 255;
    bVal += bInc;
    if (bVal > 255) bVal = bVal - 255;
    
    analogWrite(rPin,rVal);
    analogWrite(gPin,gVal);
    analogWrite(bPin,bVal);
    delay(10); 
   }
   digitalWrite(innerPin,LOW);
   digitalWrite(outterPin,LOW);
  } // end Mode 2
  
  // Mode 3 - All on
  stateChanged = false;
  allOn();
  while(!stateChanged) {
      // Wait
  }
  
  
}
