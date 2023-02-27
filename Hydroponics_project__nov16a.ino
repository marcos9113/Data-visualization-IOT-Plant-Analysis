#include "arduino_secrets.h"
/*


  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  float humidity;
  float moisture;
  float temperature;
  float water_temp;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <DHT.h>
#define DHTPIN 13    // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22
DHT dht(DHTPIN, DHTTYPE);
unsigned long millisCounter;


#define soil_sensor_pin 14;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  dht.begin();
  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();

  if (millis() - millisCounter > 3000) {
    temperature = dht.readTemperature(); // Read temperature as Celsius
    humidity = dht.readHumidity(); //Read Humidity



    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" *C ");
    Serial.println("");
    millisCounter = millis();



  }
}

void onTemperatureChange() {

}

void onHumidityChange() {

}













/*
  Since WaterTemp is READ_WRITE variable, onWaterTempChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onWaterTempChange()  {
  // Add your code here to act upon WaterTemp change
}