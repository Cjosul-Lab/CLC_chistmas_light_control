/*
  CLC Christmas Light controller
  Author: Nicola Franceschinis
  Mail: cjosulab@gmail.com
  Start develop: 20211220
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LOAD_PIN LED_BUILTIN
#define LED_ON LOW
#define LED_OFF HIGH
 
const char* ssid = "WIFI-Tele1_d37b";
const char* password = "153624abDF";
 
ESP8266WebServer server(80);

bool ledStatus = false;
 
void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  pinMode(LOAD_PIN, OUTPUT);
 
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", handleRootDefault);
 
  server.on("/ledon", handleLedOn);
  server.on("/ledoff", handleLedOff);
  server.on("/fading", handleFading);
  server.on("/flashing", handleFlashing);
 
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void) {
  server.handleClient();
}