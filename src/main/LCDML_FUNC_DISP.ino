// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_back)
// *********************************************************************
{
  // setup
  // is called only if it is started
}
   
void LCDML_DISP_loop(LCDML_FUNC_back)
{
  // loop
  // is called when it is triggert
  LCDML_DISP_resetIsTimer(); // reset the initscreen timer
  LCDML.goBack();            // go back
  LCDML_DISP_funcend();      // LCDML_DISP_funcend calls the loop_end function
}
   
void LCDML_DISP_loop_end(LCDML_FUNC_back)
{
  // loop end
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing 
}


// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_information)
// *********************************************************************
{
  // setup function 
  lcd.setCursor(0, 0);
  lcd.print("Temp. Hi : ");
  lcd.print(realTemperatureHi);
  lcd.write(6);
  lcd.setCursor(19, 0);
  if(ventilationState){
    lcd.write(5);
  }
  lcd.setCursor(0, 1);
  lcd.print("Temp. Low: ");
  lcd.print(realTemperatureLow);
  lcd.write(6);
  lcd.print("(");
  lcd.print(setTemperature);
  lcd.write(6);
  lcd.print(")");
  lcd.setCursor(19, 1);
  if(heatingState){
    lcd.write(5);
  }
  if(coolingState){
    lcd.write(5);
  }
  lcd.setCursor(0, 2);
  lcd.print("Humidity : ");
  lcd.print(realHumidity);
  lcd.print("%");
  lcd.print("(");
  lcd.print(setHumidity);
  lcd.print("%)");
  lcd.setCursor(19, 2);
  if(!digitalRead(OUT_6)){
    lcd.write(5);
  }
  lcd.setCursor(0, 3);
  lcd.print("Lighting : ");
  lcd.print(lux);
  lcd.print("lx");
  LCDML_DISP_triggerMenu(100);
}

void LCDML_DISP_loop(LCDML_FUNC_information) 
{
  lcd.setCursor(11, 0);
  lcd.print("         ");
  lcd.setCursor(11, 0);
  lcd.print(realTemperatureHi);
  lcd.write(6);
  lcd.setCursor(19, 0);
  lcd.setCursor(11, 1);
  lcd.print("         ");
  lcd.setCursor(11, 1);
  lcd.print(realTemperatureLow);
  lcd.write(6);
  lcd.print("(");
  lcd.print(setTemperature);
  lcd.write(6);
  lcd.print(")");
  lcd.setCursor(19, 1);
  if(heatingState){
    lcd.print("\xd9");
  }
  if(coolingState){
    lcd.print("\xda");
  }
  lcd.setCursor(11, 2);
  lcd.print("         ");
  lcd.setCursor(11, 2);
  lcd.print(realHumidity);
  lcd.print("%");
  lcd.print("(");
  lcd.print(setHumidity);
  lcd.print("%)");
  lcd.setCursor(19, 2);
  if(!digitalRead(OUT_2)){
    lcd.write(5);
  }
  lcd.setCursor(11, 3);
  lcd.print("         ");
  lcd.setCursor(11, 3);
  lcd.print(lux); 
  lcd.print(" lx");

  if (LCDML_BUTTON_checkAny()){
      LCDML_DISP_funcend();      
  } 
}

void LCDML_DISP_loop_end(LCDML_FUNC_information)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing  
}  


// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_set_temp)
// *********************************************************************
{ 
  g_button_value = setTemperature;
  lcd.setCursor(0, 0);
  lcd.print(F("Temperature: "));
  if(setTemperature < 10){
    lcd.print("0");
  }
  lcd.print(setTemperature);
  lcd.setCursor(0, 1);
  lcd.print(F("Temperature: "));
  lcd.setCursor(13, 1); // set cursor
  if(g_button_value < 10){
    lcd.print("0");
  }
  lcd.print(g_button_value); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_set_temp)
{
  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      if (g_button_value < 25) {
        g_button_value++;
      }      
      // update lcd content
      lcd.setCursor(13, 1); // set cursor   
      lcd.print(g_button_value); // print change content
    }
    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      if (g_button_value > 5) {
        g_button_value--;
      }      
      // update lcd content
      lcd.setCursor(13, 1); // set cursor   
      lcd.print(g_button_value); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      if(g_button_value != setTemperature){
        setTemperature = g_button_value;
        EEPROMUpdateInt(0, setTemperature);
      }
    LCDML_DISP_funcend();      
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_set_temp) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_set_temp_difference)
// *********************************************************************
{ 
  // setup function
  // print lcd content
  g_button_value = setTemperatureDifference;
  if(g_button_value < 0){
    g_button_value = 0;
  }
  lcd.setCursor(0, 0);
  lcd.print(F("Delta: "));
  if(setTemperatureDifference < 10){
    lcd.print("0");
  }
  lcd.print(setTemperatureDifference); 
  lcd.setCursor(0, 1);
  lcd.print(F("Delta: "));
  lcd.setCursor(7, 1); // set cursor
  if(g_button_value < 10){
    lcd.print("0");
  }   
  lcd.print(g_button_value); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_set_temp_difference)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      if (g_button_value < 10) {
        g_button_value++;
      }      
      // update lcd content
      lcd.setCursor(7, 1); // set cursor
      if(g_button_value < 10){
        lcd.print("0");
      }  
      lcd.print(g_button_value); // print change content
    }
    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      if (g_button_value > 0) {
        g_button_value--;
      }      
      // update lcd content
      lcd.setCursor(7, 1); // set cursor
      if(g_button_value < 10){
           lcd.print("0");
      }
      lcd.print(g_button_value); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      if(g_button_value != setTemperatureDifference){
        setTemperatureDifference = g_button_value;
        EEPROMUpdateInt(2, setTemperatureDifference);
      }
    LCDML_DISP_funcend();      
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_set_temp_difference) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_set_humidity)
// *********************************************************************
{ 
  // setup function
  // print lcd content
  g_button_value = setHumidity;
  lcd.setCursor(0, 0);
  lcd.print(F("Set humidity: "));
  if(setHumidity < 10){
    lcd.print("0");
  }
  lcd.print(setHumidity);  
  lcd.setCursor(0, 1);
  lcd.print(F("Set humidity: "));
  lcd.setCursor(14, 1); // set cursor
  if(g_button_value < 10){
    lcd.print("0");
  }   
  lcd.print(g_button_value); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_set_humidity)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  if (LCDML_BUTTON_checkAny()){
    if (LCDML_BUTTON_checkUp()){
      LCDML_BUTTON_resetUp(); // reset the left button
      if (g_button_value < 99) {
        g_button_value++;
      }      
      // update lcd content
      lcd.setCursor(14, 1); // set cursor
      if(g_button_value < 10){
        lcd.print("0");
      }  
      lcd.print(g_button_value); // print change content
    }
    if (LCDML_BUTTON_checkDown()){
      LCDML_BUTTON_resetDown(); // reset the left button
      if (g_button_value > 0) {
        g_button_value--;
      }      
      // update lcd content
      lcd.setCursor(14, 1); // set cursor
      if(g_button_value < 10){
           lcd.print("0");
      }
      lcd.print(g_button_value); // print change content
    }
    if (LCDML_BUTTON_checkEnter()){
      LCDML_BUTTON_resetEnter(); // reset the left button
      if(g_button_value != setHumidity){
        setHumidity = g_button_value;
        EEPROMUpdateInt(4, setHumidity);
      }
    LCDML_DISP_funcend();      
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_set_humidity) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_set_humidity_difference)
// *********************************************************************
{ 
  // setup function
  // print lcd content
  g_button_value = setHumidityDifference;
  lcd.setCursor(0, 0);
  lcd.print(F("Delta: "));
  if(setHumidityDifference < 10){
    lcd.print("0");
  }
  lcd.print(setHumidityDifference);  
  lcd.setCursor(0, 1);
  lcd.print(F("Delta: "));
  lcd.setCursor(7, 1); // set cursor
  if(g_button_value < 10){
    lcd.print("0");
  }   
  lcd.print(g_button_value); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_set_humidity_difference)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      if (g_button_value < 99) {
        g_button_value++;
      }      
      // update lcd content
      lcd.setCursor(7, 1); // set cursor
      if(g_button_value < 10){
        lcd.print("0");
      }  
      lcd.print(g_button_value); // print change content
    }
    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      if (g_button_value > 0) {
        g_button_value--;
      }      
      // update lcd content
      lcd.setCursor(7, 1); // set cursor
      if(g_button_value < 10){
           lcd.print("0");
      }
      lcd.print(g_button_value); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      if(g_button_value != setHumidityDifference){
        setHumidityDifference = g_button_value;
        EEPROMUpdateInt(8, setHumidityDifference);
      }
    LCDML_DISP_funcend();      
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_set_humidity_difference) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_set_lighting)
// *********************************************************************
{ 
  // setup function
  // print lcd content
  g_button_value = setLighting;
  lcd.setCursor(0, 0);
  lcd.print(F("Light: "));
  if(setLighting < 10){
    lcd.print("0");
  }
  lcd.print(setLighting);  
  lcd.setCursor(0, 1);
  lcd.print(F("Light: "));
  lcd.print(g_button_value); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_set_lighting)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      if (g_button_value < 99) {
        g_button_value++;
      }      
      // update lcd content
      lcd.setCursor(0, 1);
      lcd.print(F("Light: "));
      lcd.print(g_button_value); // print change content
    }
    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      if (g_button_value > 0) {
        g_button_value--;
      }      
      // update lcd content
      lcd.setCursor(0, 1);
      lcd.print(F("Light: "));
      lcd.print(g_button_value); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      if(g_button_value != setLighting){
        setLighting = g_button_value;
        EEPROMUpdateInt(14, setLighting);
      }
    LCDML_DISP_funcend();      
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_set_lighting) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}


// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_set_lighting_on_time)
// *********************************************************************
{
  pos = 15;
  edit = 0;
  hours = lHours;
  minutes = lMinutes;
  
  lcd.setCursor(0, 0);
  lcd.print("Current time: ");
  if(lHours < 10){
    lcd.print("0");
  }
  lcd.print(lHours);
  lcd.print(":");
  if(lMinutes < 10){
    lcd.print("0");
  }
  lcd.print(lMinutes);
  lcd.setCursor(0, 1);
  lcd.print("New time    : ");
  if(hours < 10){
    lcd.print("0");
  }
  lcd.print(hours);
  lcd.print(":");
  if(minutes < 10){
    lcd.print("0");
  }
  lcd.print(minutes);
  LCDML_DISP_triggerMenu(100);
}

void LCDML_DISP_loop(LCDML_FUNC_set_lighting_on_time)
{
  
  lcd.setCursor(14, 0);
  if(lHours < 10){
    lcd.print("0");
  }
  lcd.print(lHours);
  lcd.print(":");
  if(lMinutes < 10){
    lcd.print("0");
  }
  lcd.print(lMinutes);
  lcd.setCursor(14, 1);
  if(hours < 10){
    lcd.print("0");
  }
  lcd.print(hours);
  lcd.print(":");
  if(minutes < 10){
    lcd.print("0");
  }
  lcd.print(minutes);
  if(edit){
    lcd.setCursor(pos, 1);
  }
  if (LCDML_BUTTON_checkAny()){
    if (LCDML_BUTTON_checkUp()){
      LCDML_BUTTON_resetUp();
      if(edit && pos == 15){
        hours++;
        if(hours > 23){
          hours = 0;
        }
      }else{
        minutes++;
        if(minutes > 59){
          minutes = 0;
        }
      }
    }
  }
  if (LCDML_BUTTON_checkDown()){
    LCDML_BUTTON_resetDown();
    if(edit && pos == 15){
      hours--;
      if(hours < 0){
        hours = 23;
      }
    }else{
      minutes--;
      if(minutes < 0){
        minutes = 59;
      }
    }
  }
  if (LCDML_BUTTON_checkRight()){
    LCDML_BUTTON_resetRight();
    if(edit && pos == 15){
      pos = 18;
      lcd.setCursor(pos, 1);
    }else{
      pos = 15;
      lcd.setCursor(pos, 1);
    }
  }
  if (LCDML_BUTTON_checkLeft()){
    LCDML_BUTTON_resetLeft();
    if(edit && pos == 15){
      pos = 18;
      lcd.setCursor(pos, 1);
    }else{
      pos = 15;
      lcd.setCursor(pos, 1);
    }
  }
  if (LCDML_BUTTON_checkEnter()){
    LCDML_BUTTON_resetEnter();
    if(!edit){
      edit = 1;
      lcd.setCursor(pos ,1);
      lcd.blink();
    }else{
      edit = 0;
      lcd.noBlink();
      pos = 15;
      if(lHours != hours){
        lHours = hours;
        EEPROM.write(56, lHours);
      }
      if(lMinutes != minutes){
        lMinutes = minutes;
        EEPROM.write(57, lMinutes);
      }
    }
//    LCDML_DISP_funcend();      
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_set_time) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_set_temp_delta)
// *********************************************************************
{ 
  // setup function
  // print lcd content
  g_button_value = setTemperatureDelta;
  lcd.setCursor(0, 0);
  lcd.print(F("Delta: "));
  if(setTemperatureDelta < 10){
    lcd.print("0");
  }
  lcd.print(setTemperatureDelta);  
  lcd.setCursor(0, 1);
  lcd.print(F("Delta: "));
  lcd.print(g_button_value); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_set_temp_delta)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      if (g_button_value < 10) {
        g_button_value++;
      }      
      // update lcd content
      lcd.setCursor(7, 1); // set cursor
      if(g_button_value < 10){
        lcd.print("0");
      }  
      lcd.print(g_button_value); // print change content
    }
    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      if (g_button_value > 0) {
        g_button_value--;
      }      
      // update lcd content
      lcd.setCursor(7, 1); // set cursor
      if(g_button_value < 10){
           lcd.print("0");
      }
      lcd.print(g_button_value); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      if(g_button_value != setTemperatureDelta){
        setTemperatureDelta = g_button_value;
        EEPROMUpdateInt(6, setTemperatureDelta);
      }
    LCDML_DISP_funcend();      
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_set_temp_delta) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_set_tControl)
// *********************************************************************
{ 
  // setup function
  // print lcd content
  b_button_value = tControl;
  if(b_button_value < 0){
    b_button_value = 0;
  }
  lcd.setCursor(0, 0);
  lcd.print(F("Temp. control: "));
  lcd.print(tControl);
  lcd.setCursor(0, 1);
  lcd.print(F("Temp. control: "));
  lcd.setCursor(15, 1); // set cursor
  lcd.print(b_button_value); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_set_tControl)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      if (b_button_value < 1) {
        b_button_value = 1;
      }      
      // update lcd content
      lcd.setCursor(15, 1); // set cursor
      lcd.print(b_button_value); // print change content
    }
    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      if (b_button_value > 0) {
        b_button_value = 0;
      }      
      // update lcd content
      lcd.setCursor(15, 1); // set cursor
      lcd.print(b_button_value); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      if(b_button_value != tControl){
        tControl = b_button_value;
        EEPROM.write(50, tControl);
      }
    LCDML_DISP_funcend();      
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_set_tControl) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_set_hControl)
// *********************************************************************
{ 
  // setup function
  // print lcd content
  b_button_value = hControl;
  if(b_button_value < 0){
    b_button_value = 0;
  }
  lcd.setCursor(0, 0);
  lcd.print(F("Hum. control: "));
  lcd.print(hControl);
  lcd.setCursor(0, 1);
  lcd.print(F("Hum. control: "));
  lcd.setCursor(14, 1); // set cursor
  lcd.print(b_button_value); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_set_hControl)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      if (b_button_value < 1) {
        b_button_value = 1;
      }      
      // update lcd content
      lcd.setCursor(14, 1); // set cursor
      lcd.print(b_button_value); // print change content
    }
    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      if (b_button_value > 0) {
        b_button_value = 0;
      }      
      // update lcd content
      lcd.setCursor(14, 1); // set cursor
      lcd.print(b_button_value); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      if(b_button_value != hControl){
        hControl = b_button_value;
        EEPROM.write(52, hControl);
      }
    LCDML_DISP_funcend();      
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_set_hControl) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}


// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_set_vControl)
// *********************************************************************
{ 
  // setup function
  // print lcd content
  b_button_value = vControl;
  if(b_button_value < 0){
    b_button_value = 0;
  }
  lcd.setCursor(0, 0);
  lcd.print(F("Vent. control: "));
  lcd.print(vControl);
  lcd.setCursor(0, 1);
  lcd.print(F("Vent. control: "));
  lcd.setCursor(15, 1); // set cursor
  lcd.print(b_button_value); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_set_vControl)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      if (b_button_value < 1) {
        b_button_value = 1;
      }      
      // update lcd content
      lcd.setCursor(15, 1); // set cursor
      lcd.print(b_button_value); // print change content
    }
    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      if (b_button_value > 0) {
        b_button_value = 0;
      }      
      // update lcd content
      lcd.setCursor(15, 1); // set cursor
      lcd.print(b_button_value); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      if(b_button_value != vControl){
        vControl = b_button_value;
        EEPROM.write(51, vControl);
      }
    LCDML_DISP_funcend();      
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_set_vControl) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_set_lControl)
// *********************************************************************
{ 
  // setup function
  // print lcd content
  b_button_value = lControl;
  if(b_button_value < 0){
    b_button_value = 0;
  }
  lcd.setCursor(0, 0);
  lcd.print(F("Ligh. control: "));
  lcd.print(lControl);
  lcd.setCursor(0, 1);
  lcd.print(F("Ligh. control: "));
  lcd.setCursor(15, 1); // set cursor
  lcd.print(b_button_value); // print change content
}

void LCDML_DISP_loop(LCDML_FUNC_set_lControl)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetUp(); // reset the left button
      if (b_button_value < 1) {
        b_button_value = 1;
      }      
      // update lcd content
      lcd.setCursor(15, 1); // set cursor
      lcd.print(b_button_value); // print change content
    }
    if (LCDML_BUTTON_checkDown()) // check if button left is pressed
    {
      LCDML_BUTTON_resetDown(); // reset the left button
      if (b_button_value > 0) {
        b_button_value = 0;
      }      
      // update lcd content
      lcd.setCursor(15, 1); // set cursor
      lcd.print(b_button_value); // print change content
    }
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
      if(b_button_value != lControl){
        lControl = b_button_value;
        EEPROM.write(54, lControl);
      }
    LCDML_DISP_funcend();      
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_set_lControl) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_set_time)
// *********************************************************************
{
  RTC.read(tm);
  hours = tm.Hour;
  minutes = tm.Minute;
  pos = 15;
  edit = 0;
  
  lcd.setCursor(0, 0);
  lcd.print("Current time: ");
  if(tm.Hour < 10){
    lcd.print("0");
  }
  lcd.print(tm.Hour);
  lcd.print(":");
  if(tm.Minute < 10){
    lcd.print("0");
  }
  lcd.print(tm.Minute);
  lcd.setCursor(0, 1);
  lcd.print("New time    : ");
  if(tm.Hour < 10){
    lcd.print("0");
  }
  lcd.print(tm.Hour);
  lcd.print(":");
  if(tm.Minute < 10){
    lcd.print("0");
  }
  lcd.print(tm.Minute);
  LCDML_DISP_triggerMenu(100);
}

void LCDML_DISP_loop(LCDML_FUNC_set_time)
{
  RTC.read(tm);
  lcd.setCursor(14, 0);
  if(tm.Hour < 10){
    lcd.print("0");
  }
  lcd.print(tm.Hour);
  lcd.print(":");
  if(tm.Minute < 10){
    lcd.print("0");
  }
  lcd.print(tm.Minute);
  lcd.setCursor(14, 1);
  if(hours < 10){
    lcd.print("0");
  }
  lcd.print(hours);
  lcd.print(":");
  if(minutes < 10){
    lcd.print("0");
  }
  lcd.print(minutes);
  if(edit){
    lcd.setCursor(pos, 1);
  }
  if (LCDML_BUTTON_checkAny()){
    if (LCDML_BUTTON_checkUp()){
      LCDML_BUTTON_resetUp();
      if(edit && pos == 15){
        hours++;
        if(hours > 23){
          hours = 0;
        }
      }else{
        minutes++;
        if(minutes > 59){
          minutes = 0;
        }
      }
    }
  }
  if (LCDML_BUTTON_checkDown()){
    LCDML_BUTTON_resetDown();
    if(edit && pos == 15){
      hours--;
      if(hours < 0){
        hours = 23;
      }
    }else{
      minutes--;
      if(minutes < 0){
        minutes = 59;
      }
    }
  }
  if (LCDML_BUTTON_checkRight()){
    LCDML_BUTTON_resetRight();
    if(edit && pos == 15){
      pos = 18;
      lcd.setCursor(pos, 1);
    }else{
      pos = 15;
      lcd.setCursor(pos, 1);
    }
  }
  if (LCDML_BUTTON_checkLeft()){
    LCDML_BUTTON_resetLeft();
    if(edit && pos == 15){
      pos = 18;
      lcd.setCursor(pos, 1);
    }else{
      pos = 15;
      lcd.setCursor(pos, 1);
    }
  }
  if (LCDML_BUTTON_checkEnter()){
    LCDML_BUTTON_resetEnter();
    if(!edit){
      edit = 1;
      lcd.setCursor(pos ,1);
      lcd.blink();
    }else{
      edit = 0;
      lcd.noBlink();
      pos = 15;
      tm.Hour = hours;
      tm.Minute = minutes;
      RTC.write(tm);
    }
//    LCDML_DISP_funcend();      
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_set_lighting_on_time) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}
