#include "thingProperties.h"
#include <DHT.h>

// Pin DHT22 tersambung ke G4 (GPIO4)
#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(1500); 

  dht.begin(); // Inisialisasi DHT22

  initProperties(); // Inisialisasi variable IoT Cloud

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();

  // Baca sensor DHT22 setiap 2 detik
  static unsigned long lastRead = 0;
  if (millis() - lastRead >= 2000) {
    lastRead = millis();
    
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (isnan(t) || isnan(h)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Kirim ke Arduino IoT Cloud
    temp = t;
    hum = h;

    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print(" °C, Humidity: ");
    Serial.print(hum);
    Serial.println(" %");
  }
}

// Tidak digunakan karena temp dan hum bersifat READ_ONLY
void onTempChange() {}
void onHumChange() {}
