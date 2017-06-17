void control(){
// Управление исполнителями в зависимости от режима

  if (digitalRead(auto_man)) {
    if(tControl == 1){
      temperatureControl ();
    }else{
      if(heatingState){
        heating_off ();
      }
      if(coolingState){
        cooling_off ();
      }
    }
    if(vControl == 1){
      ventilationControl ();
    }else{
      if(ventilationState){
        ventilation_off ();
      }
    }
    if(hControl == 1){
      humidityControl ();
    }else{
      if(humidificationStateLow) {
        humidification_off_low ();
      }
      if(humidificationStateUp) {
        humidification_off_up ();
      }
    }
    if(lControl == 1){
      lightingControl ();
    }else{
      if(lightingState) {
       lighting_off ();
      }
    }
  } else {
    if(heatingState == 0){
      heating_on ();
    }
    if(coolingState){
      cooling_off ();
    }
    if(ventilationState){
      ventilation_off ();
    }
    if(humidificationStateLow) {
      humidification_off_low ();
    }
    if(humidificationStateUp) {
      humidification_off_up ();
    }
    if(lightingState) {
      lighting_off ();
    }
  }
}
