#include <AtabeyAutopilot.h>

using namespace atabey::drivers;

GpsSensor gps;

void setup() {

    Serial.begin(115200);
      while(!Serial);

    Serial.println("GPS test basladi");

    if(!gps.init()) {
        Serial.println("GPS init FAILED");
        while(1);
    }

    Serial.println("GPS init OK");
}

void loop() {

    gps.update();

    Serial.print("Healthy: ");
    Serial.print(gps.isHealthy());

    Serial.print(" | Fix: ");
    Serial.println(gps.hasFix());

    if(gps.isHealthy() && gps.hasFix()) {

        float lat = gps.getLat() * 1e-7f;
        float lon = gps.getLon() * 1e-7f;
        float alt = gps.getAlt() * 1e-3f;

        Serial.print("LAT: ");
        Serial.println(lat, 7);

        Serial.print("LON: ");
        Serial.println(lon, 7);

        Serial.print("ALT(m): ");
        Serial.println(alt);

        Serial.println("---------------------");
    }

    delay(50);
}