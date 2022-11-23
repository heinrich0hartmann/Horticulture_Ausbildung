void setup() {
 Serial.begin(9600); // Serial-Port öffnen und auf 9600 Baud setzen
 pinMode (11, INPUT); // Pin 11 (digital) auf Input setzen
 pinMode (A3, INPUT); // Pin A0 (analog) auf Input setzen
 }

void loop() {
 int istTrocken = digitalRead(11); // Pin 11 auslesen -> in Variable istTrocken
 int feuchtigkeit = analogRead(A0); // Pin A0 auslesen -> in Variable feuchtigkeit
 int prozent = map(feuchtigkeit,230,1023,100,0); // ungefähre Prozentangabe durch Mapping
 
 Serial.print("Ist der Sensor trocken? "); // Kurzerklärung zum folgenden Wert
 if (istTrocken) // prüfen, ob istTrocken=1 (also true) ist ...
 { 
 Serial.println("Ja"); // ... wenn ja, dann "Ja" ausgeben ...
 }
 else // ... ansonsten ...
 { 
 Serial.println("Nein"); // ... "Nein" ausgeben
 }
 
 Serial.print("Gemessene Feuchtigkeit: "); // Kurzerklärung zum folgenden Wert
 Serial.println(feuchtigkeit); // Wert von "feuchtigkeit" ausgeben
 Serial.print("Feuchtigkeit in Prozent: "); //Kurzerklärung zum folgenden Wert
 Serial.println(prozent); // Wert von "prozent" ausgeben
 delay(1000); // 1 Sekunde warten
}
