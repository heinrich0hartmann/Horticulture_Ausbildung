#include <Wire.h>
#include <AS_BH1750.h>

AS_BH1750 sensor;

void setup()
{
    Serial.begin(9600);

    // for normal sensor resolution (1 lx resolution, 0-65535 lx, 120ms, no PowerDown)
    // use: sensor.begin(RESOLUTION_NORMAL, false);

    if(!sensor.begin()) {
        Serial.println("BH1750 init failed!");
        while(true);
    }
}

void loop()
{
    float lux = sensor.readLightLevel();
    Serial.println("Light level: " + String(lux) + " lx");
    delay(1000);
}
