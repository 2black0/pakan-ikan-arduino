/*

Urutan test no 10
Program test untuk ph sensor di Arduino Uno

kalau tidak berkedip atau tidak bisa diupload pastikan:
driver telah terinstall dengan baik
memilih Arduni Uno di board selection
pilih COM yang terdeteksi dengan benar
ph-Data -> Pin-A1

2black0@gmail.com
http://robot-terbang.web.id

*/

const int pHPin = A1;
int pHVal = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(pHPin, INPUT);
}

void loop()
{
  pHVal = analogRead(pHPin);
  Serial.print("ldr Value = ");
  Serial.print(pHVal);
  delay(5);
}
