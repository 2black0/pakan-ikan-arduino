/*

Urutan test no 8
Program test untuk blink di Arduino Uno
akan muncul tulisan di LCD 

"OK"

kalau tidak berkedip atau tidak bisa diupload pastikan:
driver telah terinstall dengan baik
memilih Arduni Uno di board selection
pilih COM yang terdeteksi dengan benar
SIM800-TX -> Uno-RX
SIM800-RX <- Uno-TX

2black0@gmail.com
http://robot-terbang.web.id

*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

String data;

void setup()
{
  Serial.begin(4800);
  lcd.begin();
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("SIM800 Test");
}

void loop()
{
  Serial.println("AT");
  while (Serial.available())
  {
    data = Serial.readString();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(data);
  }
  delay(5000);
}