#include "tempsensor.h"
int solenoidPin = 4;  //This is the output pin on the Arduino we are using
String response;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(solenoidPin, OUTPUT);  //Sets the pin as an output
  delay(1000);
}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming string from the Arduino
    response = Serial.read();
    Serial.println(response);
  }

  if (response == "49") {
    // Serial.println("1");
    digitalWrite(solenoidPin, HIGH);  //Switch Solenoid ON
    response = "h";
  }
  if (response == "48") {
    // Serial.println("0");
    digitalWrite(solenoidPin, LOW);  //Switch Solenoid OFF
    response = "h";
  }
}