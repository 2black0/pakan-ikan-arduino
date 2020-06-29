/*

Urutan test no 3
Program test untuk relay di Arduino Uno
Relay akan ON/OFF dengan jeda setiap 3 detik

kalau tidak berkedip atau tidak bisa diupload pastikan:
driver telah terinstall dengan baik
memilih Arduni Uno di board selection
pilih COM yang terdeteksi dengan benar

2black0@gmail.com
http://robot-terbang.web.id

*/

int relayPin1 = 3;
int relayPin2 = 4;

void setup()
{
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
}

void loop()
{
  digitalWrite(relayPin1, HIGH);
  digitalWrite(relayPin2, HIGH);
  delay(3000);
  digitalWrite(relayPin1, LOW);
  digitalWrite(relayPin2, LOW);
  delay(3000);
}
