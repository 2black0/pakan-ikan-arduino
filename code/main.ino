#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>

// === Konstanta dan Pin ===
const int ldrPin = A0;
const int pHPin = A1;
const int relay1Pin = 3;
const int relay2Pin = 4;
const int buzPin = 5;
const int trigPin = 6;
const int echoPin = 7;
const int servoPin = 8;

// === Parameter Konfigurasi (sesuaikan dengan kebutuhan) ===
String noHP = "\"+628123456789\"";  // Nomor HP tujuan SMS
int feedHour = 9;                   // Jam pemberian makan (24 jam format)
int pfeedDis = 30;                  // Jarak minimal ketinggian pakan (cm)
int turbidWater = 512;             // Ambang kekeruhan (LDR) maksimal
int pHWater = 8;                   // Ambang pH air minimal (semakin besar semakin basa)

// === Variabel Global ===
bool feedStatus = false;
bool emptyStatus = false;
bool dirtyStatus = false;
int feedDis = 0;

DateTime now;
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 RTC;
Servo servoS;

// === Inisialisasi Pin ===
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

// === Fungsi LCD Singkat ===
void lcd_show(bool clear, int row, String text, int waitms) {
  if (clear) lcd.clear();
  lcd.setCursor(0, row);
  lcd.print(text);
  delay(waitms);
}

// === Fungsi Buzzer ===
void buzON()  { digitalWrite(buzPin, HIGH); }
void buzOFF() { digitalWrite(buzPin, LOW);  }

// === Fungsi Servo Pakan ===
void servoON()  { servoS.write(90); }
void servoOFF() { servoS.write(0);  }

// === Fungsi Relay Air ===
void relayON() {
  digitalWrite(relay1Pin, LOW);
  digitalWrite(relay2Pin, LOW);
}
void relayOFF() {
  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);
}

// === Fungsi Pembacaan Sensor ===
int readUltrasonic() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000); // timeout 30ms
  int distance = duration * 0.034 / 2;
  return distance;
}

int readLDR() {
  return analogRead(ldrPin); // nilai kecil = gelap/keruh
}

int readPH() {
  int val = analogRead(pHPin);
  // Konversi nilai ADC ke rentang pH (asumsi linear mapping)
  float voltage = val * (5.0 / 1023.0);
  float phValue = 14.0 - ((voltage - 0.5) * (14.0 / 3.0)); // justifikasi nilai sensor
  return round(phValue);
}

// === Fungsi Kirim SMS (placeholder) ===
void sendSMS(String msg) {
  Serial.print("SMS to ");
  Serial.print(noHP);
  Serial.print(" : ");
  Serial.println(msg);
  // Tambahkan modul SIM800/SIM900 jika digunakan.
}

// === Setup Awal ===
void setup() {
  Serial.begin(4800);
  lcd.init();
  lcd.backlight();
  Wire.begin();
  RTC.begin();
  init_pin();

  if (!RTC.isrunning()) {
    lcd_show(1, 0, "RTC not running!", 1000);
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  lcd_show(1, 0, "Sistem Pakan Ikan", 1000);
  lcd_show(0, 1, "Mulai...", 1000);

  relayOFF();  // Matikan pompa di awal
  servoOFF();  // Servo kembali ke posisi awal
  buzOFF();    // Matikan buzzer
}

// === LOOP Utama ===
void loop() {
  now = RTC.now();
  int currentHour = now.hour();

  // === Pakan Ikan ===
  if (currentHour == feedHour && !feedStatus) {
    feedStatus = true;
    lcd_show(1, 0, "Kasih Makan!", 1000);
    sendSMS("Kasih Makan!");
    servoON(); delay(2000); servoOFF();
    buzON();   delay(1000); buzOFF();
  }
  if (currentHour != feedHour && feedStatus) {
    feedStatus = false;
  }

  // === Cek Isi Pakan ===
  feedDis = readUltrasonic();
  if (feedDis >= pfeedDis && !emptyStatus) {
    emptyStatus = true;
    lcd_show(1, 0, "Pakan Habis!", 1000);
    sendSMS("Pakan Habis!");
    buzON(); delay(1000); buzOFF();
  }
  if (feedDis < pfeedDis && emptyStatus) {
    emptyStatus = false;
  }

  // === Cek Air (Keruh dan pH) ===
  int ldrVal = readLDR();
  int phVal = readPH();

  if ((ldrVal < turbidWater || phVal > pHWater) && !dirtyStatus) {
    dirtyStatus = true;
    lcd_show(1, 0, "Ganti Air!", 1000);
    sendSMS("Air Kotor - Ganti Air!");
    relayON();
    delay(180000);  // 3 menit
    relayOFF();
  }
  if ((ldrVal >= turbidWater && phVal <= pHWater) && dirtyStatus) {
    dirtyStatus = false;
  }

  // === Tampilkan Informasi ===
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("pH:");
  lcd.print(phVal);
  lcd.print(" Turb:");
  lcd.print(ldrVal);
  lcd.setCursor(0, 1);
  lcd.print("Dis:");
  lcd.print(feedDis);
  lcd.print("cm");
  delay(2000);
}
