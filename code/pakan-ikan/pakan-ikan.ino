#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>

const int ldrPin = A0;
const int pHPin = A1;
const int relay1Pin = 3;
const int relay2Pin = 4;
const int buzPin = 5;
const int trigPin = 6;
const int echoPin = 7;
const int servoPin = 8;

// parameter change with yours
String noHP = "\"+628123456789\""; // ganti no hp penerima
int pfeedDis = 30;                 // ganti jarak minimal pakan kosong (cm)
int feedHour = 9;                  // ganti mau jam brp dikasih makan
int turbidWater = 512;             // ganti dengan nilai kekeruhan maksimal
int pHWater = 8;                   // ganti dengan nilai ph minimal

int ldrVal = 0;
int pHVal = 0;

String year;
String month;
String day;
String hour;
String minute;
String second;

bool feedStatus = false;
bool emptyStatus = false;
bool dirtyStatus = false;

int feedDis = 0;

DateTime now;

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 RTC;
Servo servoS;

void init_pin() {
  pinMode(ldrPin, INPUT);
  pinMode(pHPin, INPUT);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(buzPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servoS.attach(servoPin, 600, 2300);
}

void setup() {
  Serial.begin(4800);
  lcd.init();
  Wire.begin();
  RTC.begin();
  init_pin();

  if (!RTC.isrunning()) {
    lcd_show(1, 0, "RTC not Run!", 500);
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  delay(100);

  lcd_show(1, 0, "Pakan Ikan", 1);
  lcd_show(0, 1, "Arduino Uno", 1000);
}

void loop() {

  // program pakan ikan tiap jam tertentu
  now = RTC.now();
  hour = now.hour(), DEC;

  if (hour == feedHour && feedStatus == false) {
    feedStatus = true;
    lcdSHOW(1, 0, "Kasih Makan!", 1);
    sendSMS("Kasih Makan!");
    servoON();
    buzON();
    delay(2000);
    servoOFF();
    buzOFF();
  }
  if (hour != feedHour && feedStatus == true) {
    feedStatus = false;
  }

  // program baca isi pakan
  feedDis = readUltrasonic();

  if (feedDis <= pfeedDis && emptyStatus == false) {
    emptyStatus = true;
    lcdSHOW(1, 0, "Pakan Habis!", 1);
    sendSMS("Pakan Habis!");
    buzON();
    delay(1000);
    buzOFF();
  }
  if (feedDis > pfeedDis && emptyStatus == true) {
    emptyStatus = false;
  }

  // program baca air keruh dan ph air
  ldrVal = readLDR();
  pHVal = readPH();

  if (ldrVal < turbidWater && pHVal > pHWater) {
    dirtyStatus = false;
    lcdSHOW(1, 0, "Ganti Air!", 1);
    relayON();
    delay(180000);
    relayOFF();
  }
  if ((ldrVal >= turbidWater || pHVal <= pHWater) && (dirtyStatus == true)) {
    dirtyStatus = true;
    delay(100);
  }
}
