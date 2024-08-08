// Include the DHT library which provides functions to interact with DHT sensors.
#include "DHT.h"

// Define the GPIO pin where the data pin of the DHT sensor is connected.
#define DHTPIN D6 

// Define the type of DHT sensor being used. It can be either DHT11 or DHT22.
#define DHTTYPE DHT22 

// Create an instance of the DHT class with the specified pin and type.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial communication at a baud rate of 9600 bits per second.
  Serial.begin(9600);
  Serial.println(F("DHT11 test!"));
  
  // Set the pin mode for the LED pin as output.
  pinMode(D8, OUTPUT);
  
  // Initialize the DHT sensor.
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  
  // Read humidity in percentage
  float h = dht.readHumidity();
  
  // Read temperature in Celsius (default)
  float t = dht.readTemperature();
  
  // Read temperature in Fahrenheit
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (default)
  float hif = dht.computeHeatIndex(f, h);
  
  // Compute heat index in Celsius
  float hic = dht.computeHeatIndex(t, h, false);

  // Print the humidity and temperature values to the serial monitor.
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

   // Check the temperature and print the appropriate message
  if (t >= 30.0) {
    Serial.println("Getting Heat!!!");
  } else {
    Serial.println("Normal");
  }

  // Wait for a second before the next loop iteration
  delay(1000);
}
