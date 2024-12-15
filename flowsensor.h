#include <Arduino.h>
#include <FlowSensor.h>

#define type YFS201
#define pin1 2  // flow1
#define pin2 3  // flow2

FlowSensor Sensor1(type, pin1);
FlowSensor Sensor2(type, pin2);
unsigned long reset = 0;

void count1() {
  Sensor1.count();
}

void count2() {
  Sensor2.count();
}

void khoitao() {
  Sensor1.begin(count1);
  Sensor2.begin(count2);
}

String flowSensor() {

  Sensor1.read();
  Sensor2.read();
  return String(Sensor1.getFlowRate_m()) + "," + String(Sensor1.getVolume()) + "," + String(Sensor2.getFlowRate_m()) + "," + String(Sensor2.getVolume());

  // // Reset Volume
  // if (millis() - reset >= 60000) {
  //   Sensor1.resetVolume();
  //   Sensor2.resetVolume();
  //   reset = millis();
  // }
}