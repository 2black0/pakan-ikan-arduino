/*

Urutan test no 1
Program test untuk blink di Arduino Uno
Led yang ada pada Board akan berkedip setiap 1 detik

kalau tidak berkedip atau tidak bisa diupload pastikan:
driver telah terinstall dengan baik
memilih Arduni Uno di board selection
pilih COM yang terdeteksi dengan benar

2black0@gmail.com
http://robot-terbang.web.id

*/

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
