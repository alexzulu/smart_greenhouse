void EEPROMWriteInt(int p_address, int p_value){
  byte lowByte = ((p_value >> 0) & 0xFF);
  byte highByte = ((p_value >> 8) & 0xFF);

  EEPROM.write(p_address, lowByte);
  EEPROM.write(p_address + 1, highByte);
}

void EEPROMUpdateInt(int p_address, int p_value){
  byte lowByte = ((p_value >> 0) & 0xFF);
  byte highByte = ((p_value >> 8) & 0xFF);

  EEPROM.update(p_address, lowByte);
  EEPROM.update(p_address + 1, highByte);
}

int EEPROMReadInt(int p_address){
  byte lowByte = EEPROM.read(p_address);
  byte highByte = EEPROM.read(p_address + 1);
  return word(highByte, lowByte);
}

void EEPROMData () {
  for(int i = 0; i < 16; i + 2){
    Serial.println(EEPROMReadInt(i));
  }
}

