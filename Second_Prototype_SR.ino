#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
String receivedData = "";

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(4);
  display.setCursor(8, 28);
  display.println(":)");
  display.display();
  delay(5000);
}

void loop() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.display();

  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (receivedData.length() > 0) {
        processData(receivedData);
        receivedData = "";
      }
    } else {
      receivedData += c;
    }
  }
}

void processData(String data) {
  data.trim();
  String label = "";

  // Parse JSON: {"label":"Class 1","confidence":0.85}
  if (data.indexOf("{") >= 0) {
    int labelStart = data.indexOf("\"label\":\"") + 9;
    int labelEnd = data.indexOf("\"", labelStart);
    if (labelEnd > labelStart) {
      label = data.substring(labelStart, labelEnd);
    }
  }
  // Parse CSV: Class 1,0.85
  else if (data.indexOf(",") > 0) {
    label = data.substring(0, data.indexOf(","));
  }
  // Plain label
  else {
    label = data;
  }

  if (label == "Class 1") {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("This reminds me of    your old home.");
    display.display();
    delay(1000);
    display.clearDisplay();
  }
  if (label == "Class 2") {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("This is a close match to your garages.");
    display.display();
    delay(1000);
    display.clearDisplay();
  }
  if (label == "Class 3") {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("This is simialar to   your nearby woods.");
    display.display();
    delay(1000);
    display.clearDisplay();
  }
  if (label == "Class 4") {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Your old park         looked like this.");
    display.display();
    delay(1000);
    display.clearDisplay();
  }
}
