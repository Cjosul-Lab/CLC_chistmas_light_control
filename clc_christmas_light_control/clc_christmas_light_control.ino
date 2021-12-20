/*
  CLC Christmas Light controller
  Author: Nicola Franceschinis
  Mail: cjosulab@gmail.com
  Start develop: 20211220
*/
#define LOADPIN 11
void setup() {
  Serial.begin(9600);
  pinMode(LOADPIN, OUTPUT);
}

void loop() {
  serialHandler();
}
