#include "tempsensor.h"
#include "tdssensor.h"
#include "flowsensor.h"
#include "valvecontrol.h"
#define TdsSensorPin A0

// Initialize flow sensor
int flowPin = 2;
int solenoidPin = 4;

unsigned long currenttime, timebefore;
String response, anstrans, flowandvol;
float temp, tds;

void setup() {

  // (Flow) Setup connection
  //pinMode(flowPin, INPUT);
  pinMode(solenoidPin, OUTPUT);
  //attachInterrupt(0, Flow, RISING);

  // (TDS) Setup pin
  pinMode(TdsSensorPin, INPUT);

  Serial.begin(115200);

  khoitao();
  delay(2000);
}


void loop() {
  temp = TempSensor();
  tds = TDSSensor(temp);
  if (millis() - timebefore >= 1000) {
    flowandvol = flowSensor();
    timebefore = millis();
  }

  if (Serial.available() > 0) {
    // read the incoming string from the Arduino
    response = Serial.read();
    //Serial.println(response);
  }

  // if (respond.equals("49")) {
  //   valveControl(1, solenoidPin);
  // }
  // if (respond.equals("48")) {
  //   valveControl(0, solenoidPin);
  // }

  if (response.equals("10")) {

    anstrans = String(temp) + "," + String(tds) + "," + flowandvol;
    Serial.println();
    Serial.println(anstrans);

    //delay(2000);
    response = "no";
  }
}