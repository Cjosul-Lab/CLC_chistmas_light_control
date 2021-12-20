void serialHandler() {
  if (Serial.available()) {
    char buffer = Serial.read();
    /*switch(buffer) {
      case '0':
      Serial.print(buffer);
      Serial.println(" --> tree OFF");
      lightControl(0);
      Serial.flush();
      break;
      case '1':
      Serial.print(buffer);
      Serial.println(" --> tree ON");
      lightControl(1);
      Serial.flush();
      break;
      
      default:
      Serial.println("buffer");
      break;
    }*/
    if(buffer >= 48 && buffer <= 57)
      lightControl(buffer);
  }
}

void lightControl(int mode) {
  switch (mode) {
    case 0:
    digitalWrite(LOADPIN, LOW);
    break;
    case 1:
    analogWrite(LOADPIN, 255);
    break;
  }
}