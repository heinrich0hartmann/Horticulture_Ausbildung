
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//-----Hardware Adressierung-----
//Bei falscher Funktion bitte obere Zeile auskommentieren,
//und untere Zeile freigeben
LiquidCrystal_I2C lcd(0x27,20,4);
//LiquidCrystal_I2C lcd(0x27,20,4);
//LiquidCrystal_I2C lcd(0x3F,20,4);
//Die beiden Adressierungsarten.

void setup()
{
lcd.init();
lcd.backlight();
//Nachricht ausgeben
lcd.setCursor(0,0);
lcd.print(" LCD Displays");
lcd.setCursor(0,1);
lcd.print(" Sind richtige ");
lcd.setCursor(0,2);
lcd.print(" Hurensöhne");
lcd.setCursor(0,3);
lcd.print(" LCD");

}
void loop()
{

}
