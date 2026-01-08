#include <Arduino.h>
#include <arduino_homekit_server.h>

//Wifi
#include "wifi_info.h"

#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

//LED
#include <Adafruit_NeoPixel.h>
#define LED_PIN D6
#define LED_NUM 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800); 
// Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);


boolean valuesUpdated = false;

#include "LedController.h"
LedController *lights;

//Homekit
#include "HomeKit.h"

//Alexa
#include "Alexa.h"

void setup() {

  Serial.begin(115200);

  EEPROM.begin(4096);

	wifi_connect();

  lights = new LedController(&strip, LED_NUM, 1500);

  setupHomeKit();
  setupAlexa();

  syncValuesHomekit();
  syncValuesAlexa();
}

long syncLoopTimer = 0;

void loop() {

	homeKitLoop();
  espalexa.loop();

  lights->frame();

  if(valuesUpdated){

    syncValuesHomekit();
    syncValuesAlexa();
    
    valuesUpdated = false;
  }

	delay(10);
}