
// Variablen für Relais an Pins festlegen.
const int relais1 = 8;
const int relais2 = 9;
const int relais3 = 10;

void setup() {
  // Pins als Output Pins festlegen.
  pinMode(relais1, OUTPUT);
  pinMode(relais2, OUTPUT);
  pinMode(relais3, OUTPUT);
}

void loop() {
  
  digitalWrite(relais1, HIGH);  //ON verbunden /NC getrennt
  delay(1000);
  digitalWrite(relais1, LOW);   //ON getrennt /NC verbunden

  digitalWrite(relais2, HIGH);
  delay(1000);
  digitalWrite(relais2, LOW);
  
  digitalWrite(relais3, HIGH);
  delay(1000);
  digitalWrite(relais3, LOW);
 
}
