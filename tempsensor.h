//Import componments for Temp Sensor
#include  "max6675.h"

//Setup variables for Temp Sensor
int SO = 5; 
int CS = 6; 
int sck = 7;
MAX6675 thermocouple(sck,  CS,  SO);

float TempSensor() {
  return thermocouple.readCelsius();
}