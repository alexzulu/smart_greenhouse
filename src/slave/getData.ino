void getData(){
  // Опрашиваем датчики
  getValueHiTemperatureSensors ();
  getValueLowTemperatureSensors ();
  getLight ();

// Вычисляем усреднённые значения
// getRealTemperatureHi ();
// getRealTemperatureLow ();
// getRealHumidityLow ();
  
  getTemperatureDifference ();

  lowerTemperatureLimit = setTemperature - setTemperatureDelta - 1;
  upperTemperatureLimit = setTemperature + setTemperatureDelta + 1;
  
  lowerHumidityLimit = setHumidity - setHumidityDifference - 1;
  upperHumidityLimit = setHumidity + setHumidityDifference + 1;

  lowerHumidityLimit = setHumidity - setHumidityDifference - 1;
  upperHumidityLimit = setHumidity + setHumidityDifference + 1;
}

