/*

Urutan test no 11
Program test untuk rtc di Arduino Uno
akan terbaca tanggal dan waktu

kalau tidak berkedip atau tidak bisa diupload pastikan:
driver telah terinstall dengan baik
memilih Arduni Uno di board selection
pilih COM yang terdeteksi dengan benar
RTC-SDA <-> Uno-A4
RTC-SCL <-> Uno-A5

2black0@gmail.com
http://robot-terbang.web.id

*/

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  if (!RTC.isrunning())
  {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}
void loop()
{
  DateTime now = RTC.now();
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(1000);
}