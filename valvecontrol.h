//int solenoidPin = 4; // This is the output pin on the Arduino we are using

void valveControl(int check, int solenoidPin)
{
    Serial.println("Close or open valve");
    if (check == 1)
        digitalWrite(solenoidPin, HIGH); // Let the water flow

    if (check == 0)
        digitalWrite(solenoidPin, LOW); // Shut the water flow
}