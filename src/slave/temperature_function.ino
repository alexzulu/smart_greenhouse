int hCount = millis();
void getValueHiTemperatureSensors (){
  int currentMillis = millis();
  for (int i = 0; i < 2; i++){
    DHT dht(TemperatureSensorHiPins[i], DHTTYPE);
    dht.begin();
    if (TemperatureSensorHiSwitch[i]){
      if(dht.readHumidity() > 0 && dht.readTemperature() > 0){
        TemperatureSensorHiValueHumidity[i] = dht.readHumidity();
      }
    }
  }
//  TemperatureSensorHiValueTemperature[0] = temperatureRequest(TH0);
//  Serial.print("TH0 = ");
//  Serial.println(TemperatureSensorHiValueTemperature[0]);
//  Serial.print("TH1 = ");
//  TemperatureSensorHiValueTemperature[1] = temperatureRequest(TH1);
//  Serial.println(TemperatureSensorHiValueTemperature[1]);
  hCount = currentMillis;
  if (debug == 2){
    Serial.println("");
  }
}

int lCount = millis();
void getValueLowTemperatureSensors (){
  int currentMillis = millis();
  int offset = currentMillis - lCount;
  if(offset > mOffset){
    for (int i = 0; i < 2; i++){
      DHT dht(TemperatureSensorLowPins[i], DHTTYPE);
      dht.begin();
      if (TemperatureSensorLowSwitch[i]){
        if(dht.readHumidity() > 0 && dht.readTemperature() > 0){
          TemperatureSensorLowValueHumidity[i] = dht.readHumidity();
//          TemperatureSensorLowValueTemperature[i] = dht.readTemperature();
        }
      } else {
        if (debug == 2){
          Serial.print("Low T");
          Serial.print(i);
          Serial.println(" sensor is OFF ");
        }
      }
    }
//    TemperatureSensorLowValueTemperature[0] = temperatureRequest(TL0);
//    Serial.print("TL0 = ");
//    Serial.println(TemperatureSensorLowValueTemperature[0]);
//    TemperatureSensorLowValueTemperature[1] = temperatureRequest(TL1);
//    Serial.print("TL1 = ");
//    Serial.println(TemperatureSensorLowValueTemperature[1]);
  getTempOneWire(TL0);
    lCount = currentMillis;
    if (debug == 2){
      Serial.println("");
    }
  }
}

void getTemperatureDifference () {
  realTemperatureDifference = realTemperatureHi - realTemperatureLow;
}

void getRealTemperatureHi () {
  int divide = 0;
  int allTemp = 0;
  for (int i = 0; i < 2; i++) {
    if(TemperatureSensorHiValueTemperature[i] > 0){
      if (TemperatureSensorHiSwitch[i]) {
        divide++;
        allTemp = allTemp + TemperatureSensorHiValueTemperature[i];
      }
    }
  }
  if (debug == 1) {
    Serial.print("Divide Hi: ");
    Serial.println(divide);
    Serial.print("Real allTemp Hi: ");
    Serial.println(allTemp);
  }
  if (divide != 0) {
    realTemperatureHi = allTemp / divide;
    if (debug == 1) {
      Serial.print("Real Temp Hi: ");
      Serial.println(realTemperatureHi);
    }
  }
  if (debug == 1) {
    Serial.println();
  }
}

void getRealTemperatureLow () {
  int divide = 0;
  int allTemp = 0;
  for (int i = 0; i < 2; i++) {
    if (TemperatureSensorLowSwitch[i]) {
      if(TemperatureSensorLowValueTemperature[i] > 0){
        divide++;
        allTemp = allTemp + TemperatureSensorLowValueTemperature[i];
      }
    }
  }
  if (debug == 1) {
    Serial.print("Divide Low: ");
    Serial.println(divide);
    Serial.print("Real allTemp Low: ");
    Serial.println(allTemp);
  }
  if (divide != 0) {
    realTemperatureLow = allTemp / divide;
    if (debug == 1) {
      Serial.print("Real Temp Low: ");
      Serial.println(realTemperatureLow);
    }
  }
  if (debug == 1) {
    Serial.println();
  }
}

void getRealHumidityLow () {
  int divide = 0;
  int allHum = 0;
  for (int i = 0; i < 2; i++) {
    if (TemperatureSensorLowSwitch[i]) {
      if(TemperatureSensorLowValueHumidity[i] > 0){
        divide++;
        allHum = allHum + TemperatureSensorLowValueHumidity[i];
      }
    }
  }
  if (debug == 1) {
    Serial.print("Divide Low: ");
    Serial.println(divide);
    Serial.print("Real allHum Low: ");
    Serial.println(allHum);
  }
  if (divide != 0) {
    realHumidity = allHum / divide;
    if (debug == 1) {
      Serial.print("Real Humidity: ");
      Serial.println(realHumidity);
    }
  }
  if (debug == 1) {
    Serial.println();
  }
}

float temperatureRequest(DeviceAddress addr){
  float temp;
  
  sensors.requestTemperatures();

  temp = sensors.getTempC(addr);
  return temp;
}

void getTempOneWire(DeviceAddress addr){
  float celsius, fahrenheit;
  byte present = 0;
  byte i;
  byte data[12];
  
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(800);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  Serial.print("  Data = ");
  Serial.print(present, HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  byte cfg = (data[4] & 0x60);
  // at lower res, the low bits are undefined, so let's zero them
  if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
  else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
  else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
  //// default is 12 bit resolution, 750 ms conversion time

  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.print(" Celsius, ");
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit");
}

