/*
pakan ikan bebasis arduino uno
2black0@gmail.com
*/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"
#include <Servo.h>

int relayPin1 = 3;
int relayPin2 = 4;
int buzPin = 5;
const int trigPin = 6;
const int echoPin = 7;
int servoPin = 8;
const int ldrPin = A0;
const int pHPin = A1;

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 RTC;
Servo servoS;

void setup()
{
  Serial.begin(4800);
  lcd.begin();
  setupPin();
  servoS.attach(servoPin, 600, 2300);
  Wire.begin();
  RTC.begin();
  delay(100);
  if (!RTC.isrunning())
  {
    lcdShow(1, "RTC not Run", 1);
    delay(500);
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  lcdShow(1, "Pakan Ikan", 1);
  lcdShow(0, "Arduino Uno", 2);
  delay(1000);
}

void loop()
{
}

void setupPin()
{
  pinMode(buzPin, OUTPUT);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(pHPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void lcdShow(bool clear, String text, int line)
{
  if (clear == 1)
  {
    lcd.clear();
  }
  if (line == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(text);
  }
  elif (line == 2)
  {
    lcd.setCursor(0, 0);
    lcd.print(text);
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Wrong Line");
  }
}

float readAnalog(const int analogPin)
{
  float analogVal = 0;
  for (int i = 0; i < 50; i++)
  {
    analogVal += analogRead(analogPin);
    delay(1);
  }
  return analogVal / 50;
}

long readUltrasonic()
{
  long duration;
  int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

String readRTC()
{
  DateTime now = RTC.now();
  String dates = "";
  String times = "";
  String datetime = "";
  dates = String(now.day(), DEC) + "/" + String(now.month(), DEC) + "/" + String(now.year(), DEC);
  times = String(now.hour(), DEC) + ":" + String(now.minute(), DEC) + ":" + String(now.second(), DEC);
  datetime = dates + times;
  return datetime;
}

void servoMove()
{
  servoS.write(0);
  delay(1000);
  servoS.write(90);
  delay(1000);
  servoS.write(135);
  delay(1000);
  servoS.write(180);
  delay(1000);
}

String simCom()
{
  String data;

  Serial.println("AT");
  while (Serial.available())
  {
    data = Serial.readString();
    lcdShow(1, data, 1);
  }
  return data;
}