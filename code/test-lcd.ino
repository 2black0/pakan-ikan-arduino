/*

Urutan test no 7
Program test untuk blink di Arduino Uno
akan muncul tulisan di LCD 

"Selamat Datang"
"Pakan Ikan-Uno"

kalau tidak berkedip atau tidak bisa diupload pastikan:
driver telah terinstall dengan baik
memilih Arduni Uno di board selection
pilih COM yang terdeteksi dengan benar
LCD-SDA <-> Uno-A4
LCD-SCL <-> Uno-A5

2black0@gmail.com
http://robot-terbang.web.id

*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.begin();
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("Selamat Datang");
  lcd.setCursor(0, 1);
  lcd.print("Pakan Ikan-Uno");
}