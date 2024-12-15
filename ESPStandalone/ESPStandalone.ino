/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6KhoqhAWT"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "beqlOrBhAn2Yazy0XiyHmhTilT_FqPHZ"


//#include "tempsensor.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "wpa2_enterprise.h"
#include <ezTime.h>

BlynkTimer timer;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "VinUni Students";
char username[] = "23anh.ht";
char password[] = "xxxxx";
String reponse, temp, tds, flow1, res, vol1, flow2, vol2, check, haha;

// BLYNK_WRITE(V0) {
//   int value = param.asInt();
//   Serial.println(value);
// }

void setup() {
  // Debug console
  Serial.begin(115200);

  //Wifi connection
  struct station_config wifi_config;

  memset(&wifi_config, 0, sizeof(wifi_config));
  strcpy((char*)wifi_config.ssid, ssid);

  wifi_station_set_config(&wifi_config);

  wifi_station_clear_cert_key();
  wifi_station_clear_enterprise_ca_cert();

  wifi_station_set_wpa2_enterprise_auth(1);
  wifi_station_set_enterprise_identity((uint8*)username, strlen(username));
  wifi_station_set_enterprise_username((uint8*)username, strlen(username));
  wifi_station_set_enterprise_password((uint8*)password, strlen(password));

  wifi_station_connect();  // Commented out with blynk.
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);


  // Setup a function to be called every second
  timer.setInterval(1000L, realTimeData);

  delay(1000);
  // Serial.println("yes");
}

void realTimeData() {
  // read the incoming string from the Arduino
  //response = Serial.readString();

  // temp = Serial.readString();
  // tds = Serial.readString();
  // flow = Serial.readString();
  Blynk.beginGroup();
  {
    Blynk.virtualWrite(V5, temp.toDouble());
    Blynk.virtualWrite(V6, tds.toDouble());
    Blynk.virtualWrite(V7, flow1.toDouble());
    Blynk.virtualWrite(V8, vol1.toDouble());
    Blynk.virtualWrite(V9, flow2.toDouble());
    Blynk.virtualWrite(V10, vol2.toDouble());
    Blynk.virtualWrite(V11, abs((vol2.toDouble()) - (vol1.toDouble())));
  }
  Blynk.endGroup();
  //Serial.println("yes");
  // Serial.println(temp);
  // Serial.println(tds);
  // Serial.println(flow);
}


void loop() {
  if (Serial.available() == 0) {
    timer.run();
    Blynk.run();
  }

  if (Serial.available() > 0) {
    check = Serial.read();

    if (check == "10") {
      Serial.println();
      haha = Serial.readString();
      Serial.println(haha);

      temp = getValue(haha, ',', 0);
      tds = getValue(haha, ',', 1);
      flow1 = getValue(haha, ',', 2);
      vol1 = getValue(haha, ',', 3);
      flow2 = getValue(haha, ',', 4);
      vol2 = getValue(haha, ',', 5);
      
    }

    check = "0";
    res = "n";
  }
}


String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}