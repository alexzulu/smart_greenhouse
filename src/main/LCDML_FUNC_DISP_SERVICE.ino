// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_state)
// *********************************************************************
{ 
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print("Out 0:");
  if(digitalRead(OUT_0)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }
  lcd.setCursor(0, 1);
  lcd.print("Out 1:");
  if(digitalRead(OUT_1)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }
  lcd.setCursor(0, 2);
  lcd.print("Out 2:");
  if(digitalRead(OUT_2)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }
  lcd.setCursor(0, 3);
  lcd.print("Out 3:");
  if(digitalRead(OUT_3)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }
  lcd.setCursor(10, 0);
  lcd.print("Out 4:");
  if(digitalRead(OUT_4)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }
  lcd.setCursor(10, 1);
  lcd.print("Out 5:");
  if(digitalRead(OUT_5)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }
  lcd.setCursor(10, 2);
  lcd.print("Out 6:");
  if(digitalRead(OUT_6)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }
  lcd.setCursor(10, 3);
  lcd.print("Out 7:");
  if(digitalRead(OUT_7)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }
  LCDML_DISP_triggerMenu(100);
}

void LCDML_DISP_loop(LCDML_FUNC_state)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  lcd.setCursor(6, 0);
  if(digitalRead(OUT_0)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }
  lcd.setCursor(6, 1);
  if(digitalRead(OUT_1)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }
  lcd.setCursor(6, 2);
  if(digitalRead(OUT_2)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }
  lcd.setCursor(6, 3);
  if(digitalRead(OUT_3)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }
  lcd.setCursor(16, 0);
  if(digitalRead(OUT_4)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }
  lcd.setCursor(16, 1);
  if(digitalRead(OUT_5)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }
  lcd.setCursor(16, 2);
  if(digitalRead(OUT_6)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }
  lcd.setCursor(16, 3);
  if(digitalRead(OUT_7)){
    lcd.print("OFF");
  }else{
    lcd.print("ON ");
  }

  g_lcdml_initscreen = millis();
  
  if (LCDML_BUTTON_checkAny()){
    if (LCDML_BUTTON_checkEnter()){
    LCDML_DISP_funcend();      
    }
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_state) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_sensors)
// *********************************************************************
{ 
  lcd.setCursor(0, 0);
  lcd.print("T.H 0: ");
  lcd.print(TemperatureSensorHiValueTemperature[0]);
  lcd.setCursor(0, 1);
  lcd.print("T.H 1: ");
  lcd.print(TemperatureSensorHiValueTemperature[1]);
  lcd.setCursor(0, 2);
  lcd.print("T.L 0: ");
  lcd.print(TemperatureSensorLowValueTemperature[0]);
  lcd.setCursor(0, 3);
  lcd.print("T.L 1: ");
  lcd.print(TemperatureSensorLowValueTemperature[1]);
  lcd.setCursor(10, 0);
  lcd.print("H.H 0: ");
  lcd.print(TemperatureSensorHiValueHumidity[0]);
  lcd.setCursor(10, 1);
  lcd.print("H.H 1: ");
  lcd.print(TemperatureSensorHiValueHumidity[1]);
  lcd.setCursor(10, 2);
  lcd.print("H.L 0: ");
  lcd.print(TemperatureSensorLowValueHumidity[0]);
  lcd.setCursor(10, 3);
  lcd.print("H.L 1: ");
  lcd.print(TemperatureSensorLowValueHumidity[1]);
  LCDML_DISP_triggerMenu(100);
}

void LCDML_DISP_loop(LCDML_FUNC_sensors)
{
  lcd.setCursor(7, 0);
  lcd.print("   ");
  lcd.setCursor(7, 0);
  lcd.print(TemperatureSensorHiValueTemperature[0]);
  lcd.setCursor(7, 1);
  lcd.print("   ");
  lcd.setCursor(7, 1);
  lcd.print(TemperatureSensorHiValueTemperature[1]);
  lcd.setCursor(7, 2);
  lcd.print("   ");
  lcd.setCursor(7, 2);
  lcd.print(TemperatureSensorLowValueTemperature[0]);
  lcd.setCursor(7, 3);
  lcd.print("   ");
  lcd.setCursor(7, 3);
  lcd.print(TemperatureSensorLowValueTemperature[1]);
  lcd.setCursor(17, 0);
  lcd.print("   ");
  lcd.setCursor(17, 0);
  lcd.print(TemperatureSensorHiValueHumidity[0]);
  lcd.setCursor(17, 1);
  lcd.print("   ");
  lcd.setCursor(17, 1);
  lcd.print(TemperatureSensorHiValueHumidity[1]);
  lcd.setCursor(17, 2);
  lcd.print("   ");
  lcd.setCursor(17, 2);
  lcd.print(TemperatureSensorLowValueHumidity[0]);
  lcd.setCursor(17, 3);
  lcd.print("   ");
  lcd.setCursor(17, 3);
  lcd.print(TemperatureSensorLowValueHumidity[1]);
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkEnter()) // check if button left is pressed
    {
      LCDML_BUTTON_resetEnter(); // reset the left button
    }
//    LCDML_DISP_funcend();      
  }
}

void LCDML_DISP_loop_end(LCDML_FUNC_sensors) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}
