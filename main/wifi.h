void connect_wifi() {
  tft.fillScreen(ILI9341_WHITE);

  tft.drawBitmap(60,0,stjlogo,120,88,ILI9341_STJC);

  tft.setFont(&FreeSans12pt7b);
  tft.setCursor(7,110);
  tft.setTextColor(ILI9341_STJB);
  tft.print(intro);
  
  tft.setFont(&FreeSans9pt7b);
  tft.setCursor(7, 140);
  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(1);

  tft.print("Connecting to ");
  tft.println(ssid);
  
  WiFi.begin(ssid, password);

  int connect_count = 0;
  tft.setCursor(7, 165);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    tft.print(".");
    connect_count++;
    if(connect_count == 4) {
      tft.fillRect(7,165,30,2,ILI9341_WHITE);
      connect_count = 0;
      tft.setCursor(7, 165);
    }
  }
  tft.println(" connected");  
  tft.setCursor(7, 195);
  tft.print("IP address: ");
  tft.println(WiFi.localIP());

  delay(1000);

  tft.fillRect(0,0,240,210,ILI9341_WHITE);
}
