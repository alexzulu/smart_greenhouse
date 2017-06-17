int lxCount = millis();
void getLight () {
  int currentMillis = millis();
  int offset = currentMillis - lxCount;
  if(offset > mOffset){
    lux = lightMeter.readLightLevel();
    lxCount = currentMillis;
  }
}

