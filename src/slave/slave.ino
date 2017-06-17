#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCDMenuLib.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <BH1750.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "DHT.h" // Подключаем бибилиотеку для датчиков температуры и влажности типа DHT 22, DHT 11
//#define DHTTYPE DHT11 // Тип датчика DHT 11
#define DHTTYPE DHT22 // Тип датчика DHT 22
BH1750 lightMeter;

#define ONE_WIRE_BUS 4
#define TEMPERATURE_PRECISION 9
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
OneWire  ds(4);  // on pin 10 (a 4.7K resistor is necessary)

DeviceAddress TL0 = { 0x28, 0x30, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0x8E };
DeviceAddress TL1 = { 0x28, 0x32, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0xE0 };
DeviceAddress TH0 = { 0x28, 0x32, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0xE0 };
DeviceAddress TH1 = { 0x28, 0x30, 0xC5, 0xB8, 0x00, 0x00, 0x00, 0x8E };

int TemperatureSensorHiPins[2] = {5, 6}; // Массив входов от верхних датчиков
int TemperatureSensorLowPins[2]= {7, 8}; // Массив входов от нижних датчиков
boolean TemperatureSensorHiSwitch[2] = {1, 1}; // Массив включенных верхних датчиков
boolean TemperatureSensorLowSwitch[2] = {1, 1}; // Массив включенных нижних датчиков
int TemperatureSensorHiValueTemperature[2]; // Массив значений температур от верхних датчиков
int TemperatureSensorHiValueHumidity[2]; // Массив значений влажности от верхних датчиков
int TemperatureSensorLowValueTemperature[2]; // Массив значений температур от нижних датчиков
int TemperatureSensorLowValueHumidity[2]; // Массив значений влажности от верхних датчиков

// Установочные данные
int setTemperature; // Установленная температура
int setTemperatureDelta; // Дельта температуры
int setTemperatureDifference; // Уставка разницы температуры между верхом и низом теплицы
int setHumidity; // Установленная влажность воздуха
int setHumidityDifference; // Дельта влажности
int setLighting; // Уставка освещения
int mOffset = 50000;

// Реальные показания
int realTemperatureHi; // Реальная температура верхних датчиков(усреднённое значение)
int realTemperatureLow; // Реальная температура нижних датчиков(усреднённое значение)
int realTemperatureDifference; // Реальная разница температуры верхних и нижних датчиков(Переменная реальной температуры верхних датчиков - Переменная реальной температуры нижних датчиков)
int realHumidity; //Реальная влажность воздуха
int lux; // Освещённость

// Лимиты 
int lowerTemperatureLimit; // Нижний лимит по температуре(заданная температура - дельта температуры)
int upperTemperatureLimit; // Верхний лимит по температуре(заданная температура + дельта температуры)
int lowerHumidityLimit; // Нижний лимит по влажности(заданная влажность - дельта влажности)
int upperHumidityLimit; // Верхний лимит по влажности(заданная влажность + дельта влажности

  // settings for lcd 
#define _LCDML_DISP_cols             20
#define _LCDML_DISP_rows             4
  
// lcd object
// liquid crystal needs (rs, e, dat4, dat5, dat6, dat7)
LiquidCrystal_I2C lcd(0x27, _LCDML_DISP_rows, _LCDML_DISP_rows);

int debug = 2; // Режим отладки вкл/выкл 

void setup() {
   Serial.begin(9600);
//  Wire.begin();
  lightMeter.begin();
//  time.begin();
//  dht.begin();
  sensors.begin();
  sensors.setResolution(TL0, TEMPERATURE_PRECISION);
  sensors.setResolution(TL1, TEMPERATURE_PRECISION);
  sensors.setResolution(TH0, TEMPERATURE_PRECISION);
  sensors.setResolution(TH1, TEMPERATURE_PRECISION);
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.setCursor(5,0);
  lcd.print("Booting...");

}

void loop() {
      getData();

}
