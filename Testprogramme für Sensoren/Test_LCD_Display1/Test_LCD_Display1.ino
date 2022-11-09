// Einbinden Wire Bibliothek
#include <Wire.h>
// Einbinden der LiquidCrystal Bibliothek für das I2C Modul des Displays.
#include <LiquidCrystal_I2C.h> 

// Es gibt min. 2 Adressen welche ein Display verwenden kann: 0x3F oder 0x27.
// Setzt die PINs des I2C Moduls für die Kommunikation mit dem Display.
// Adresse: 0x27
// EN: 2
// RW; 1
// RS: 0
// D4: 4
// D5: 5
// D6: 6
// D7: 7
// BL: 3
// BLPOL: POSITIVE
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3); 
 
 
void setup()
{
  // initialisieren des Displays mit 20 Zeichen und 4 Zeilen
  lcd.begin(20,4);
  // setzten des Cursors auf die erste Zeile (gebinnend bei 0) und dem ersten Zeichen
  lcd.setCursor ( 0, 0 );
  // setzten eines Textes
  lcd.print("LCD 20x4 Modul");  
  // setzten des Cursors auf die zweite Zeile (1) und dem ersten Zeichen (0)
  lcd.setCursor ( 0, 1 );        
  // setzten eines Textes
  lcd.print ("01234567890123456789");   
  // setzten des Cursors auf die dritte Zeile (2) und dem ersten Zeichen (0)
  lcd.setCursor ( 0, 2 );
  // setzten eines Textes
  lcd.print ("!@$%&/()=?");     
  // setzten des Cursors auf die vierte Zeile (3) und dem ersten Zeichen (0)
  lcd.setCursor ( 0, 3 );
  // setzten eines Textes       
  lcd.print ("www.draeger-it.blog");    
}
 
void loop()
{
 
}
