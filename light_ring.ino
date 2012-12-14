#include <avr/interrupt.h>

volatile boolean stateChanged = false;

int innerStartPin = 3;  //Inner
int innerStopPin = 8;   //Inner Stop
int outterStartPin = 9; //Outter
int outterStopPin = 14; //Outter Stop

int rPin = 15;  // R
int gPin = 16;  // G
int bPin = 17;  // B

int mode_1_delay = 50; //msec

void setup() {     
  // Setup random
  Serial.begin(9600); 
  //randomSeed();
  
  // initialise intterupt for button 
  attachInterrupt(0,flagChange, FALLING);
  pinMode(2, INPUT); 

  // initialize the digital pins as an output.
  for (int led = innerStartPin ; led <= bPin ; ++led)
  {
    pinMode(led, OUTPUT);     
  }
}

void flagChange()
{
  // Flag State Changed
  stateChanged = true;
  delay(10); //debounce
  Serial.println("Flagged");  
}
void allOff() {
  for (int i = innerStartPin; i <= bPin; ++i) {
    digitalWrite(i,LOW);
  }
}

void allOn() {
  for (int i = innerStartPin; i <= outterStopPin; ++i) {
    digitalWrite(i,HIGH);
  }
  digitalWrite(bPin,HIGH);
}

void loop() {

  //Mode 1 - spinning lights Blue lights on
  stateChanged = false;
  allOff();
  Serial.println("Mode 1"); 
  while(!stateChanged) {
    
    digitalWrite(bPin, HIGH); // blue lights on
    
    for (int led = innerStartPin ; led <= innerStopPin; ++ led) {
      digitalWrite(led, HIGH);       // set the inner LEDs on
      digitalWrite(led + 6, HIGH);   // set the outter LEDs on
      if (stateChanged) break;
      delay(mode_1_delay);           // wait 
      digitalWrite(led, LOW);        // set the inner LEDs off
      digitalWrite(led + 6, LOW);    // set the outter LEDs off
      if (stateChanged) break;
      delay(mode_1_delay);           // wait 
    }
  } // end Mode 1
  
  // Mode 2 - random RGB values
  stateChanged = false;
  allOff();
  Serial.println("Mode 2"); 
  while(!stateChanged) {
   
   int rInc = random(50);
   int gInc = random(50);
   int bInc = random(50); 
   int rVal = 0;
   int gVal = 0;
   int bVal = 0;
   int innerPin = random(6) + innerStartPin;
   int outterPin = random(6) + outterStartPin;
   digitalWrite(innerPin,HIGH);
   digitalWrite(outterPin,HIGH);
   for (int i = 1 ; (i < 1000); ++i) { //1 secs with 1 msec delay in loop
    rVal += rInc;
    if (rVal > 255) rVal = rVal - 255;
    gVal += gInc;
    if (gVal > 255) gVal = gVal - 255;
    bVal += bInc;
    if (bVal > 255) bVal = bVal - 255;
    
    analogWrite(rPin,rVal);
    analogWrite(gPin,gVal);
    analogWrite(bPin,bVal);
    if (stateChanged) break;
    delay(1); 
   }
   digitalWrite(innerPin,LOW);
   digitalWrite(outterPin,LOW);
  } // end Mode 2
  
  // Mode 3 - All on
  stateChanged = false;
  allOff();
  allOn();
  Serial.println("Mode 3"); 
  while(!stateChanged) {
      // Wait
  }
  
  // mode 4 
  stateChanged = false;
  allOff();
  allOn();
  Serial.println("Mode 3"); 
  while(!stateChanged) {
      //outter on
      for (int i = outterStartPin; i<= outterStopPin; i++) {
        digitalWrite(i,HIGH);
      }
      delay(100);
      for (int i = outterStartPin; i<= outterStopPin; i++) {
        digitalWrite(i,LOW);
      }
      for (int i = innerStartPin; i<= innerStopPin; i++) {
        digitalWrite(i,HIGH);
      }
      delay(100);
      for (int i = innerStartPin; i<= innerStopPin; i++) {
        digitalWrite(i,LOW);
      }
      digitalWrite(bPin,HIGH);
      delay(500);
      digitalWrite(bPin,LOW);
      delay(100);
  }
  
}
