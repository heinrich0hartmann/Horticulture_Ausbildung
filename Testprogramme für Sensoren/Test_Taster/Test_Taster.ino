#include <Wire.h>

int UP = 3;
int SELECT = 4;
int DOWN = 5;
int taster = 0;
const int LED = 13; 

void setup() {
pinMode(UP, INPUT);
pinMode(LED, OUTPUT);


}

void loop() {

taster = digitalRead(UP); 
if (taster == HIGH){
  digitalWrite(LED, HIGH);
}
else {
  digitalWrite(LED, LOW);
  
}
}
