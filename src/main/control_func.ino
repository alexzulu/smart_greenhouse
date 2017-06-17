//#######################################################
//        Автоматический контроль температуры
//#######################################################

// Включение/выключение подогрева
void heating_on () {
  if (heatingState == 0) {
    digitalWrite(OUT_4, HIGH);
    heatingState = 1;
  }
}

void heating_off () {
  if (heatingState == 1) {
    digitalWrite(OUT_4, LOW);
    heatingState = 0;
  }
}

// Включение/выключение охлаждения
void cooling_on () {
  if (coolingState == 0) {
    digitalWrite(OUT_5, LOW);
    digitalWrite(OUT_0, LOW);
    coolingState = 1;
  }
}

void cooling_off () {
  if (coolingState == 1) {
    if(!humidificationStateUp && !ventilationState){
      digitalWrite(OUT_0, HIGH);
    }
    if(!humidificationStateUp){
      digitalWrite(OUT_5, HIGH);
    }
    coolingState = 0;
  }
}

// Контроль температуры
void temperatureControl () {
  if (realTemperatureLow <= lowerTemperatureLimit){
    heating_on();
  }
  if (realTemperatureLow >= setTemperature){
    heating_off();
  }
  
  if (realTemperatureLow >= upperTemperatureLimit){
    cooling_on ();
  } 
  if (realTemperatureLow <= setTemperature){
    cooling_off ();
  } 
}

//#######################################################
//     Автоматический контроль перемешивания воздуха
//#######################################################

void ventilation_on () {
  if (ventilationState == 0) {
    digitalWrite(OUT_0, LOW);
    ventilationState = 1;
  }
}

void ventilation_off () {
  if(ventilationState == 1){
    if(!humidificationStateUp && !coolingState){
      digitalWrite(OUT_0, HIGH);
    }
    ventilationState = 0;
  }
}

void ventilationControl () {
  if (realTemperatureDifference > setTemperatureDifference){
    ventilation_on ();
  } 
  if (realTemperatureDifference <= 0){
    ventilation_off ();
  }
}

//#######################################################
//      Автоматический контроль влажности воздуха
//#######################################################

void humidification_on_low () {
  if (humidificationStateLow == 0) {
    digitalWrite(OUT_6, LOW);
    humidificationStateLow = 1;
  }
}

void humidification_off_low () {
  if (humidificationStateLow == 1) {
    digitalWrite(OUT_6, HIGH);
    humidificationStateLow = 0;
  }
}

void humidification_on_up () {
  if (humidificationStateUp == 0) {
    digitalWrite(OUT_0, LOW);
    digitalWrite(OUT_5, LOW);
    humidificationStateUp = 1;
  }
}

void humidification_off_up () {
  if (humidificationStateUp == 1){
    if(!coolingState && !ventilationState) {
      digitalWrite(OUT_0, HIGH);
    }
    if(!coolingState){
      digitalWrite(OUT_5, HIGH);
    }
    humidificationStateUp = 0;
  }
}


void humidityControl () {
  if (realHumidity < lowerHumidityLimit){
    humidification_on_low ();
  } 
  if (realHumidity >= setHumidity){
    humidification_off_low ();
  }
  if (realHumidity > upperHumidityLimit){
    humidification_on_up ();
  } 
  if (realHumidity <= setHumidity){
    humidification_off_up ();
  }
}

//#######################################################
//       Автоматический контроль освещённости
//#######################################################

void lighting_on () {
  if (lightingState != 1) {
    digitalWrite(OUT_1, LOW);
    lightingState = 1;
  }
}

void lighting_off () {
  if (lightingState != 0) {
    digitalWrite(OUT_1, HIGH);
    lightingState = 0;
  }
}

void lightingControl () {
  if (lux < setLighting){
    lighting_on ();
  } 
  if (lux > setLighting){
    lighting_off ();
  }
}

