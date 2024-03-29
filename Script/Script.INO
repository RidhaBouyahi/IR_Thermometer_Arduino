#include <Wire.h>
#include <SparkFunMLX90614.h>  //IR Sensor model Library

#include <SPI.h>            // Serial communication protocol used to link the adafruit display to arduino
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define MOSI   9
#define CLK   10
#define DC    11
#define CS    12
#define RESET 13
Adafruit_SSD1306 display(MOSI, CLK, DC, RESET, CS); // Initialize adafruit display  funtion using spi pins

IRTherm therm;                //predefined function IRTherm

void setup()
{
  Serial.begin(9600);       // Initialize baud rate
  therm.begin();            // Initialize therm sensor
  therm.setUnit(TEMP_C);

   display.begin(SSD1306_SWITCHCAPVCC);     //Initialize display
   display.clearDisplay();
   display.setRotation(2);

}

String temperature;
char runner;

void loop()
{
  if (therm.read()) // On success, read() will return 1, on fail 0.
  {
    temperature = String(therm.object(), 2);                              // get temperature from thermogun
    Serial.print("Object: ");
    Serial.print(temperature); Serial.println("C");
    display.clearDisplay();
    runner++;
    delay(5);
  }

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(display.width()/4,display.height()/12);

  if (therm.object()>=100)
  display.setCursor(display.width()/4,display.height()/12);

  display.println(temperature);

  display.drawLine(display.width()/runner,display.height() - display.height()/2.5, display.width()/runner+1, display.height() - display.height()/2.5, WHITE);

  display.setCursor(0,display.height()-display.height()/4);
  display.setTextSize(1);
  display.println("   Arduino Thermlgun");
  display.setCursor(display.width()- display.width()/4,display.height()/12);
  display.println("deg C");
  display.display();

  if (runner>20)
  runner=0;
}
