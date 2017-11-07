#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "ESP8266WiFi.h"
#include "SocketIoClient.h"
#include "Fonts/FreeSans12pt7b.h"
#include "Fonts/FreeSans9pt7b.h"
#include "ArduinoJson.h"
#include "TimeLib.h"

#define TFT_DC D4
#define TFT_CS D2
#define TFT_MOSI D8
#define TFT_CLK D6
#define TFT_RST D1
#define TFT_MISO D7
#define ILI9341_LGBG 0xE73C
#define ILI9341_LGBO 0xDEFB
#define ILI9341_DGBG 0x73AE
#define ILI9341_BLBG 0x33D6
#define ILI9341_STJC 0x057C
#define ILI9341_STJB 0x0804

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
SocketIoClient socket;

#include "config.h"
#include "switch_channel.h"
#include "display.h"
#include "events.h"
#include "wifi.h"

void timer0_ISR (void) {
  draw_wifi_strength();
  check_display_is_current();

  timer0_write(ESP.getCycleCount() + 40000000L); // at 80MHz, 0.5s
}

void setup() {
  Serial.begin(115200);
  delay(10);

  tft.begin();
  connect_wifi();
  
  socket.begin(host, port);
  socket.on("user connected", user_connected);
  socket.on("user disconnected", user_disconnected);
  socket.on("notify change", notify_change);
  socket.on("notify message", notify_message);
  socket.on("update times", update_times);

  drawui();
  
  // initialise all the channels
  initialise_channels();
  check_display_is_current();
  
  noInterrupts();
  timer0_isr_init();
  timer0_attachInterrupt(timer0_ISR);
  timer0_write(ESP.getCycleCount() + 40000000L); // at 80MHz, 0.5s
  interrupts();
}

void loop() {
  socket.loop();

  if(WiFi.status() != WL_CONNECTED) {
    setup();
  }

  yield();
}
