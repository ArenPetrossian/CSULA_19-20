/* Robosub 2019-2020 Reading Values from MS5837 Barometer

   Current Revision 03 30 20
   Aren Petrossian
*/

#include <Wire.h>         
#include "MS5837.h"
MS5837 sensor;
float depth, pressure, temperature, altitude;

void setup() {
  Initialize_Barometer();
}

void loop() {
  Barometer_Reading();
}


void Initialize_Barometer() {
  Wire.begin();
  //Wire.beginTransmission(0x76); //don't need for now but will need when we have > 1 sensor
  while (!sensor.init()) {
    Serial.println("Initilization failed");
    delay(2000);
  }
  sensor.setModel(MS5837::MS5837_30BA);
  sensor.setFluidDensity(997);      //(air ~ 1.23, freshwater ~ 997, seawater ~1029)
}                                   //air is not accurate



void Barometer_Reading() {
  sensor.read();
  depth = sensor.depth();
  pressure = sensor.pressure();
  temperature = sensor.temperature();
  //altitude = sensor.altitude();
  
  Serial.print("Depth: ");             //Use Depth in incompressible liquid only
  Serial.print(depth); 
  Serial.println(" m");
   
  Serial.print("Pressure: "); 
  Serial.print(pressure); 
  Serial.println(" mbar");
   
  Serial.print("Temperature: "); 
  Serial.print(temperature); 
  Serial.println(" deg C");
  
  //Serial.print("Altitude: ");         //Use Altitude in air only (not very good data)
  //Serial.print(altitude); 
  //Serial.println(" m above mean sea level");
}
