// Menü zum Einstellen der Grenzwerte mit Hilfe des EEPROM

void UpperHumid (int value, int address, int x)
{ 
  /*
  byte byte_2 = (value & 0xFF);
  byte byte_1 = ((value >> 8) & 0xFF);
  EEPROM.update (0, byte_2);
  EEPROM.update (1 + 1, byte_1);
  */
  x = EEPROM.read (0);
   while (UpperHumid == true )  
    {
    if (HochSta == HIGH && (millis() - alteZeit) > entprellZeit)  // Limit hoch
    {
      x = x += 1;
      ONrWasser = x;
      lcd.setCursor (16,0);
      lcd.print (ONrWasser);
    }
    if (RunterSta == HIGH && (millis() - alteZeit) > entprellZeit) // Limit runter
    {
      x = x -= 1;
      ONrWasser = x;
      lcd.setCursor (16,1);
      lcd.print (ONrWasser);
    }
    if (x > 100)  //Grenzwerte
    {
      x = 100;
    }
    if (x < 0)
    {
      x = 0;
    }
    if (OkSta == HIGH && (millis() - alteZeit) > entprellZeit)    // EEPROM Ausgabe und Beenden des Einstellmenü
    {
      EEPROM.write(0, x)
      UpperHumid = false;
      Humid = true;
    }
    
    } // Klammer while
} // Klammer Void
