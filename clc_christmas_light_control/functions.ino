#define FADE_AMOUNT 5
#define FADE_SPEED 200
#define FLASH_SPEED 900

String handleRoot(bool ledStatus = false) {
    String ptr =
            "<html>\
              <head>\
                <title>CLC Christmas light control</title>\
                <style>\
                  body { background-color: #00ffff4d; font-family: Arial, Helvetica, Sans-Serif; Color: blue; }\
                </style>\
              </head>\
              <body>\
                <center>\
                <h1>Albero smart v 1.0</h1>\
                ";
 
    if (ledStatus) {
        ptr +=
                "<p>Albero: ON</p><a class=\"button button-off\" href=\"/ledoff\">OFF</a>\n";
    } else {
        ptr +=
                "<p>Albero: OFF</p><a class=\"button button-on\" href=\"/ledon\">ON</a>\n";
    }
    ptr += "<p><a class=\"button button-fading\" href=\"/fading\">FADING</a>\n</p>";
    ptr += "<p><a class=\"button button-flashing\" href=\"/flashing\">FLASHING</a>\n</p>";
    ptr += "</center>\
            </body>\
            </html>";
 
    return ptr;
}
 
void handleRootDefault(){
    ledStatus = false;
    //digitalWrite(LOAD_PIN, LED_OFF);
    Serial.println("Albero Status: OFF");
    selected_mode = 0;
    server.send(200, "text/html", handleRoot(ledStatus));
}
 
void handleLedOn() {
  ledStatus = true;
  Serial.println("Albero Status: ON");
  //digitalWrite(LOAD_PIN, LED_ON);
  selected_mode = 1;
  server.send(200, "text/html", handleRoot(ledStatus));
}
 
void handleLedOff() {
  ledStatus = false;
  Serial.println("Albero Status: OFF");
  //digitalWrite(LOAD_PIN, LED_OFF);
  selected_mode = 0;
  server.send(200, "text/html", handleRoot(ledStatus));
}

void handleFading() {
  ledStatus = true;
  Serial.println("Albero Status: Fading");
  selected_mode = 2;
  server.send(200, "text/html", handleRoot(ledStatus));
}

void handleFlashing() {
  ledStatus = true;
  Serial.println("Albero Status: Flashing");
  selected_mode = 3;
  server.send(200, "text/html", handleRoot(ledStatus));
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
 
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
 
  server.send(404, "text/plain", message);
}

void lightControl(int mode) {
  switch (mode) {
    case 0:
    digitalWrite(LOAD_PIN, HIGH);
    break;
    case 1:
    digitalWrite(LOAD_PIN, LOW);
    break;
    case 2:
    fader();
    break;
    case 3:
    flasher();
    break;
  }
}

void fader() {
  if (pointer <= 51 && !phase) {
    analogWrite(LOAD_PIN, pointer * FADE_AMOUNT);
    if(millis() - lastTimestamp > FADE_SPEED) {
      pointer++;
      lastTimestamp = millis();
    }
  }
  else {
    phase = 1;
  }
  if (pointer >= 0 && phase) {
    analogWrite(LOAD_PIN, pointer * FADE_AMOUNT);
    if(millis() - lastTimestamp > FADE_SPEED) {
      pointer--;
      lastTimestamp = millis();
    }
  }
  else {
    phase = 0;
  }
}

void flasher () {
  if (pointer < 20) {
    if(pointer % 2)
      digitalWrite(LOAD_PIN, HIGH);
    else
      digitalWrite(LOAD_PIN, LOW);
    if(millis() - lastTimestamp > FLASH_SPEED) {
        pointer++;
        lastTimestamp = millis();
    }
  }
  else
    pointer = 0;
}