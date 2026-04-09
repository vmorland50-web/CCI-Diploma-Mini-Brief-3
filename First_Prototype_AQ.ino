#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);  //  sets the serial port to 9600
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(8, 28);
  display.println("Keep Safe Out There");
  display.display();
  delay(5000);  // Show greeting for 5 seconds
}

void loop() {
  display.clearDisplay();
  int sensorValue = analogRead(0);   //  read analog input pin 0
  Serial.println(sensorValue);       // prints the value read

  display.setTextSize(1);
  display.setCursor(10, 0);
  display.print("CO2 Density:");
  display.print(sensorValue);
  display.print("PPM");
  display.display();
  delay(30);
}
