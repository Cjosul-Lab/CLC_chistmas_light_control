void serialHandler() {
  if (Serial.available()) {
    char buffer = Serial.read();
    switch(buffer) {
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
    }
  }
}

void lightControl(int mode) {
  switch (mode) {
    case 0:
    digitalWrite(PINLOAD, LOW);
    break;
    case 1:
    analogWrite(PINLOAD, 128);
    break;
  }
}