// include libs
#include <EEPROM.h> // Подключаем бибилиотеку для работы с EEPROM
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCDMenuLib.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <BH1750.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define OUT_0 34
#define OUT_1 35
#define OUT_2 36
#define OUT_3 37
#define OUT_4 38
#define OUT_5 39
#define OUT_6 40
#define OUT_7 41

int TemperatureSensorHiValueTemperature[2]; // Массив значений температур от верхних датчиков
int TemperatureSensorHiValueHumidity[2]; // Массив значений влажности от верхних датчиков
int TemperatureSensorLowValueTemperature[2]; // Массив значений температур от нижних датчиков
int TemperatureSensorLowValueHumidity[2]; // Массив значений влажности от верхних датчиков

#define auto_man 13

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

// Состояния режимов
boolean heatingState = 0; // Переменная состояния режима нагрева
boolean coolingState = 0; // Переменная состояния режима охлаждения
boolean ventilationState = 0; // Переменная состояния режима вентиляции(перемешивания воздуха внутри теплицы)
boolean humidificationStateLow = 0; // Переменная состояния режима увлажнения воздуха
boolean humidificationStateUp = 0; // Переменная состояния режима увлажнения воздуха
boolean lightingState = 0; // Переменная состояния режима освещения

boolean tControl; //Вкл/выкл авт. контроль температуры
boolean vControl; //Вкл/выкл авт. контроль перемешивания воздуха
boolean hControl; //Вкл/выкл авт. контроль влажности воздуха
boolean lControl; //Вкл/выкл авт. контроль освещённости
boolean co2control; //Вкл/выкл авт. контроль углекислого газа

bool b_button_value = 0;
int g_button_value = 0;
int lHours;
int lMinutes;
int hours;
int minutes;
int pos;
boolean edit;

int debug = 2; // Режим отладки вкл/выкл 

tmElements_t tm;
 
  // lib config
  #define _LCDML_DISP_cfg_button_press_time          200    // button press time in ms
  #define _LCDML_DISP_cfg_initscreen_time            10000  // enable initscreen time
  #define _LCDML_DISP_cfg_scrollbar                  1      // enable a scrollbar
  #define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol  

// ********************************************************************* 
// LCDML TYPE SELECT
// *********************************************************************
  // settings for lcd 
  #define _LCDML_DISP_cols             20
  #define _LCDML_DISP_rows             4
  
  // lcd object
  // liquid crystal needs (rs, e, dat4, dat5, dat6, dat7)
  LiquidCrystal_I2C lcd(0x27, _LCDML_DISP_rows, _LCDML_DISP_rows);

#if (_LCDML_DISP_cfg_scrollbar == 1)  
  const uint8_t scroll_bar[5][8] = {
    {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
    {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1 
    {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
    {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
    {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
  };
#endif  
byte gradus[8] = {0b00110,0b01001,0b01001,0b00110,0b00000,0b00000,0b00000,0b00000};
byte on[8] = {0b00110,0b01111,0b11111,0b11111,0b11111,0b11111,0b11110,0b01100};

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // create menu
  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    27
  
  // LCDMenuLib_add(id, group, prev_layer_element, new_element_num, lang_char_array, callback_function)
  LCDML_DISP_init(_LCDML_DISP_cnt);
  LCDML_DISP_add      (0  , _LCDML_G1  , LCDML_root        , 1  , "Information"        , LCDML_FUNC_information);
  LCDML_DISP_add      (1  , _LCDML_G1  , LCDML_root        , 2  , "Settings"           , LCDML_FUNC);
  LCDML_DISP_add      (2  , _LCDML_G1  , LCDML_root_2      , 1  , "Temperature"        , LCDML_FUNC);
  LCDML_DISP_add      (3  , _LCDML_G1  , LCDML_root_2_1    , 1  , "Set temperature"    , LCDML_FUNC_set_temp);
  LCDML_DISP_add      (4  , _LCDML_G1  , LCDML_root_2_1    , 2  , "Set delta"          , LCDML_FUNC_set_temp_difference);
  LCDML_DISP_add      (5  , _LCDML_G1  , LCDML_root_2_1    , 3  , "Back"               , LCDML_FUNC_back);
  LCDML_DISP_add      (6  , _LCDML_G1  , LCDML_root_2      , 2  , "Humidity"           , LCDML_FUNC);
  LCDML_DISP_add      (7  , _LCDML_G1  , LCDML_root_2_2    , 1  , "Set humidity"       , LCDML_FUNC_set_humidity);
  LCDML_DISP_add      (8  , _LCDML_G1  , LCDML_root_2_2    , 2  , "Set delta"          , LCDML_FUNC_set_humidity_difference);
  LCDML_DISP_add      (9  , _LCDML_G1  , LCDML_root_2_2    , 3  , "Back"               , LCDML_FUNC_back);
  LCDML_DISP_add      (10 , _LCDML_G1  , LCDML_root_2      , 3  , "Ventilation"        , LCDML_FUNC);
  LCDML_DISP_add      (11 , _LCDML_G1  , LCDML_root_2_3    , 1  , "Set delta"          , LCDML_FUNC_set_temp_delta);
  LCDML_DISP_add      (12 , _LCDML_G1  , LCDML_root_2_3    , 2  , "Back"               , LCDML_FUNC_back);
  LCDML_DISP_add      (13 , _LCDML_G1  , LCDML_root_2      , 4  , "Lightning"          , LCDML_FUNC);
  LCDML_DISP_add      (14 , _LCDML_G1  , LCDML_root_2_4    , 1  , "Set lightning"      , LCDML_FUNC_set_lighting);
  LCDML_DISP_add      (15 , _LCDML_G1  , LCDML_root_2_4    , 2  , "Set on time"        , LCDML_FUNC_set_lighting_on_time);
  LCDML_DISP_add      (16 , _LCDML_G1  , LCDML_root_2_4    , 3  , "Back"               , LCDML_FUNC_back);
  LCDML_DISP_add      (17 , _LCDML_G1  , LCDML_root_2      , 5  , "Modes"              , LCDML_FUNC);
  LCDML_DISP_add      (18 , _LCDML_G1  , LCDML_root_2_5    , 1  , "Temp. control"      , LCDML_FUNC_set_tControl);
  LCDML_DISP_add      (19 , _LCDML_G1  , LCDML_root_2_5    , 2  , "Hum.  control"      , LCDML_FUNC_set_hControl);
  LCDML_DISP_add      (20 , _LCDML_G1  , LCDML_root_2_5    , 3  , "Vent. control"      , LCDML_FUNC_set_vControl);
  LCDML_DISP_add      (21 , _LCDML_G1  , LCDML_root_2_5    , 4  , "Ligh. control"      , LCDML_FUNC_set_lControl);
  LCDML_DISP_add      (22 , _LCDML_G1  , LCDML_root_2_5    , 5  , "Back"               , LCDML_FUNC_back);
  LCDML_DISP_add      (23 , _LCDML_G1  , LCDML_root_2      , 6  , "Set time"           , LCDML_FUNC_set_time);
  LCDML_DISP_add      (24 , _LCDML_G1  , LCDML_root_2      , 7  , "Back"               , LCDML_FUNC_back);
  LCDML_DISP_add      (25 , _LCDML_G1  , LCDML_root        , 3  , "Service"            , LCDML_FUNC);
  LCDML_DISP_add      (26 , _LCDML_G1  , LCDML_root_3      , 1  , "State"              , LCDML_FUNC_state);
  LCDML_DISP_add      (27 , _LCDML_G1  , LCDML_root_3      , 2  , "Sensors"            , LCDML_FUNC_sensors);
  
  LCDML_DISP_createMenu(_LCDML_DISP_cnt);



// ********************************************************************* 
// LCDML BACKEND (core of the menu, do not change here anything yet)
// ********************************************************************* 
  // define backend function  
  #define _LCDML_BACK_cnt    1  // last backend function id
  
  LCDML_BACK_init(_LCDML_BACK_cnt);
  LCDML_BACK_new_timebased_dynamic (0  , ( 20UL )         , _LCDML_start  , LCDML_BACKEND_control);
  LCDML_BACK_new_timebased_dynamic (1  , ( 1000UL )       , _LCDML_stop   , LCDML_BACKEND_menu);
  LCDML_BACK_create();


// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {  
  Serial.begin(9600);
//  Wire.begin();
//  time.begin();
//  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.setCursor(5,0);
  lcd.print("Booting...");
  
  pinMode(OUT_0,OUTPUT);
  digitalWrite(OUT_0,HIGH);
  pinMode(OUT_1,OUTPUT);
  digitalWrite(OUT_1,HIGH);
  pinMode(OUT_2,OUTPUT);
  digitalWrite(OUT_2,HIGH);
  pinMode(OUT_3,OUTPUT);
  digitalWrite(OUT_3,HIGH);
  pinMode(OUT_4,OUTPUT);
  digitalWrite(OUT_4,HIGH);
  pinMode(OUT_5,OUTPUT);
  digitalWrite(OUT_5,HIGH);
  pinMode(OUT_6,OUTPUT);
  digitalWrite(OUT_6,HIGH);
  pinMode(OUT_7,OUTPUT);
  digitalWrite(OUT_7,HIGH);

  setTemperature = EEPROMReadInt(0);
  setTemperatureDifference = EEPROMReadInt(2); // Уставка разницы температуры между верхом и низом теплицы
  setHumidity = EEPROMReadInt(4); // Установленная влажность воздуха
  setTemperatureDelta = EEPROMReadInt(6); // Дельта температуры
  setHumidityDifference = EEPROMReadInt(8); // Дельта влажности
  setLighting = EEPROMReadInt(14); // Уставка освещения

  tControl = EEPROM.read(50);
  vControl = EEPROM.read(51);
  hControl = EEPROM.read(52);
  lControl = EEPROM.read(54);
  co2control = EEPROM.read(55);
  lHours = EEPROM.read(56);
  lMinutes = EEPROM.read(57);

// Печатам в порт включен ли режим отладки
  if (debug)
  {
    Serial.println("Debug mode: ON");
    Serial.println();
  } else {
    Serial.println("Debug mode: OFF");
  }
  delay(1000);
  lcd.clear();
  
// LCD Begin
   lcd.home ();                   // go home       
// set special chars for scrollbar
   lcd.createChar(0, (uint8_t*)scroll_bar[0]);
   lcd.createChar(1, (uint8_t*)scroll_bar[1]);
   lcd.createChar(2, (uint8_t*)scroll_bar[2]);
   lcd.createChar(3, (uint8_t*)scroll_bar[3]);
   lcd.createChar(4, (uint8_t*)scroll_bar[4]);
   lcd.createChar(5, on);
   lcd.createChar(6, gradus);
   lcd.setCursor(0,0);
   lcd.print(F("booting"));
  
// Enable all items with _LCDML_G1
   LCDML_DISP_groupEnable(_LCDML_G1); // enable group 1

// LCDMenu Setup
   LCDML_setup(_LCDML_BACK_cnt);
//   LCDML_DISP_jumpToFunc(LCDML_FUNC_set_time);  
  }

// *********************************************************************
// LOOP
// *********************************************************************
  void loop()
  {
//    sensors.requestTemperatures();
    control();
    LCDML_run(_LCDML_priority);
//    Serial.print("Input ");
//    Serial.println(analogRead(A15));
  }


// *********************************************************************
// check some errors - do not change here anything
// *********************************************************************
# if(_LCDML_DISP_rows > _LCDML_DISP_cfg_max_rows)
# error change value of _LCDML_DISP_cfg_max_rows in LCDMenuLib.h
# endif
# if(_LCDML_DISP_cols > _LCDML_DISP_cfg_max_string_length)
# error change value of _LCDML_DISP_cfg_max_string_length in LCDMenuLib.h
# endif
