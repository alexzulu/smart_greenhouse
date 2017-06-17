/*
void getValueSoilHygrometer (){
  for(int i = 0; i < 8; i++) {
    if(SoilHygrometerSensorSwitch[i]) {
      // drive a current through the divider in one direction
      digitalWrite(divider_top,HIGH);
      digitalWrite(divider_bottom,LOW);

      // wait a moment for capacitance effects to settle
      delay(10);

      // take a reading
      if(SoilHygrometerSensorSwitch[i] == 1 && i == 0) {
        SoilHygrometerSensorValue[i] = analogRead(A0);
      }
      if(SoilHygrometerSensorSwitch[i] == 1 && i == 1) {
        SoilHygrometerSensorValue[i] = analogRead(A1);
      }
      if(SoilHygrometerSensorSwitch[i] == 1 && i == 2) {
        SoilHygrometerSensorValue[i] = analogRead(A2);
      }
      if(SoilHygrometerSensorSwitch[i] == 1 && i == 3) {
        SoilHygrometerSensorValue[i] = analogRead(A3);
      }
      if(SoilHygrometerSensorSwitch[i] == 1 && i == 4) {
        SoilHygrometerSensorValue[i] = analogRead(A4);
      }
      if(SoilHygrometerSensorSwitch[i] == 1 && i == 5) {
        SoilHygrometerSensorValue[i] = analogRead(A5);
      }
      if(SoilHygrometerSensorSwitch[i] == 1 && i == 6) {
        SoilHygrometerSensorValue[i] = analogRead(A6);
      }
      if(SoilHygrometerSensorSwitch[i] == 1 && i == 7) {
        SoilHygrometerSensorValue[i] = analogRead(A7);
      }
      // reverse the current
      digitalWrite(divider_top,LOW);
      digitalWrite(divider_bottom,HIGH);
  
      // give as much time in 'reverse' as in 'forward'
      delay(10);

      // stop the current
      digitalWrite(divider_bottom,LOW);
      if (debug == 2){
        Serial.print("Soil ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(SoilHygrometerSensorValue[i]);
      }
    } else {
      if (debug == 2){
        Serial.print("Soil ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println("Sensor is OFF");
      }
    }
  }
  if (debug == 2){
    Serial.println("");
  }
}
void getRealSoilMoisture (){
  int divide = 0;
  int allSoilMoisture = 0;
  for (int i = 0; i < 8; i++)
  {
    if (SoilHygrometerSensorSwitch[i])
    {
      allSoilMoisture = allSoilMoisture + SoilHygrometerSensorValue[i];
      divide++;
      if (debug == 3)
      {
        Serial.print("Soil Moisture ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(TemperatureSensorHiValueHumidity[i]);
      }
    } else {
      if (debug == 3)
      {
        Serial.print("Soil Moisture ");
        Serial.print(i);
        Serial.println(" sensor is OFF ");
      }
    }
  }
  if (divide) {
    realSoilMoisture = allSoilMoisture / divide;
  }
  if (debug == 2){
    Serial.print("Real Soil Moisture: ");
    Serial.println(realSoilMoisture);
    Serial.println("");
  }
}

void getRealSoilMoistureDifference () {
  realSoilMoistureDifference = setSoilMoisture - realSoilMoisture;
  if (debug == 2){
    Serial.print("Real Soil Moisture Difference");
    Serial.print(": ");
    Serial.println(realSoilMoistureDifference);
  }
}
*/
