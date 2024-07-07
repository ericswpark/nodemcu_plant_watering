/*
Prerequisites:
 - ESP8266 board definitions (install using additional boards)
 - Adafruit ADS1X15 library
*/
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <Adafruit_ADS1X15.h>

#include "Header.h"
#include "WiFiCredentials.h"
#include "Config.h"
#include "HTMLData.h"

ESP8266WebServer server(80);

Adafruit_ADS1115 ads;
uint8_t motorPins[] = { RELAY_ONE, RELAY_TWO, RELAY_THREE, RELAY_FOUR };

bool motorStatus[CHANNEL_COUNT];
int16_t rawAdc[CHANNEL_COUNT];
float volt[CHANNEL_COUNT];

void handleMain(void) {
  String html = pageMain;
  server.send(200, "text/html", html);
}

void handleSensor(int pin)
{
  fetchSensorValue(pin);
  server.send(200, "text/plain", String(volt[pin]).c_str());
}

void handleS1(void) {
  handleSensor(0);
}

void handleS2(void)
{
  handleSensor(1);
}

void handleS3(void)
{
  handleSensor(2);
}

void handleS4(void)
{
  handleSensor(3);
}

void handleMotor(int pin)
{
  bool status = motorStatus[pin];
  motorStatus[pin] = !status;

  if (status) {
    digitalWrite(motorPins[pin], LOW);
    server.send(200, "text/plain", "OFF");
  } else {
    digitalWrite(motorPins[pin], HIGH);
    server.send(200, "text/plain", "ON");
  } 
}

void handleM1(void)
{
  handleMotor(0);
}

void handleM2(void)
{
  handleMotor(1);
}

void handleM3(void)
{
  handleMotor(2);
}

void handleM4(void)
{
  handleMotor(3);
}

void setup(void)
{
  // Initialize motor values to false and setup pins
  for (int chan = 0; chan < CHANNEL_COUNT; chan++)
  {
    motorStatus[chan] = false;
    pinMode(motorPins[chan], OUTPUT);
    digitalWrite(motorPins[chan], LOW);
  }

  // Setup serial and begin setup process
  Serial.begin(115200);
  Serial.println(); // Clear ESP8266 setup output
  Serial.println("Setup in progress, please wait...");

  // Setup Wi-Fi
  WiFi.persistent(true);
  WiFi.mode(WIFI_STA);
  // This is required due to an interaction bug
  // See https://github.com/esp8266/Arduino/issues/8412
  WiFi.setPhyMode(WIFI_PHY_MODE_11G);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi...");
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Could not connect to WiFi. Rebooting...");
    delay(3000);
    ESP.restart();
  }
  Serial.println();

  Serial.print("Successfully connected with IP address: ");
  Serial.println(WiFi.localIP());

  // Setup OTA
  ArduinoOTA.setPassword(ota_pw);
    ArduinoOTA.onStart([]() {
    Serial.println("Receiving new firmware through OTA...");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nFinished OTA process.");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();

  server.on("/", handleMain);
  server.on("/s1", handleS1);
  server.on("/s2", handleS2);
  server.on("/s3", handleS3);
  server.on("/s4", handleS4);
  server.on("/m1", handleM1);
  server.on("/m2", handleM2);
  server.on("/m3", handleM3);
  server.on("/m4", handleM4);

  Serial.println("Starting server...");
  server.begin();
  Serial.println("Server started");

  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  if (!ads.begin())
  {
    Serial.println("Failed to initialize ADS.");
    while (1) {
      yield();
    }
  }

  Serial.println("Setup complete.");
}

void loop(void) 
{
  server.handleClient();
}

void fetchSensorValue(int chan)
{
  rawAdc[chan] = ads.readADC_SingleEnded(chan);
  volt[chan] = ads.computeVolts(rawAdc[chan]);
}

void fetchSensorValues(void)
{
  for (int ain_pin = 0; ain_pin < CHANNEL_COUNT; ain_pin++)
  {
    fetchSensorValue(ain_pin);
  }
}