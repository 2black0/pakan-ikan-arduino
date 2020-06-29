/*

Urutan test no 9
Program test untuk buzzer di Arduino Uno
buzzer akan bunyi setiap 2 detik

kalau tidak berkedip atau tidak bisa diupload pastikan:
driver telah terinstall dengan baik
memilih Arduni Uno di board selection
pilih COM yang terdeteksi dengan benar

2black0@gmail.com
http://robot-terbang.web.id

*/

int buzPin = 5;

void setup()
{
  pinMode(buzPin, OUTPUT);
}

void loop()
{
  digitalWrite(buzPin, HIGH);
  delay(2000);
  digitalWrite(buzPin, LOW);
  delay(2000);
}
