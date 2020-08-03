#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"
#include <Servo.h>

const int ldrPin = A0;
const int pHPin = A1;
const int relay1Pin = 3;
const int relay2Pin = 4;
const int buzPin = 5;
const int trigPin = 6;
const int echoPin = 7;
const int servoPin = 8;

int ldrVal = 0;
int pHVal = 0;

String year;
String month;
String day;
String hour;
String minute;
String second;

String data;

long duration;
int distance;

DateTime now;

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 RTC;
Servo servoS;

void init_pin()
{
  pinMode(ldrPin, INPUT);
  pinMode(pHPin, INPUT);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(buzPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servoS.attach(servoPin, 600, 2300);
}

void setup()
{
  Serial.begin(4800);
  lcd.init();
  Wire.begin();
  RTC.begin();
  init_pin();

  if (!RTC.isrunning())
  {
    lcd_show(1, 0, "RTC not Run!", 500);
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  delay(100);

  lcd_show(1, 0, "Pakan Ikan", 1);
  lcd_show(0, 1, "Arduino Uno", 1000);
}

void loop()
{
}
