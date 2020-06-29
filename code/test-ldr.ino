/*

Urutan test no 4
Program test untuk blink di Arduino Uno
akan terbaca nilai dari LDR, silahkan coba terangi / tutup sensor untuk melihat perubahan data

kalau tidak berkedip atau tidak bisa diupload pastikan:
driver telah terinstall dengan baik
memilih Arduni Uno di board selection
pilih COM yang terdeteksi dengan benar
LDR -> Pin A0

2black0@gmail.com
http://robot-terbang.web.id

*/

const int ldrPin = A0;
int ldrVal = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(ldrPin, INPUT);
}

void loop()
{
  ldrVal = analogRead(ldrPin);
  Serial.print("ldr Value = ");
  Serial.print(ldrVal);
  delay(5);
}
