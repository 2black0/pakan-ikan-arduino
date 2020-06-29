/*

Urutan test no 5
Program test untuk blink di Arduino Uno
servo akan bergerak ke sudut 0, 90, 135, dan 180

kalau tidak berkedip atau tidak bisa diupload pastikan:
driver telah terinstall dengan baik
memilih Arduni Uno di board selection
pilih COM yang terdeteksi dengan benar
Servo Data -> D8

2black0@gmail.com
http://robot-terbang.web.id

*/

#include <Servo.h>

int servoPin = 8;

Servo servoS;

void setup()
{
  servoS.attach(servoPin, 600, 2300);
}

void loop()
{
  servoS.write(0);
  delay(1000);

  servoS.write(90);
  delay(500);

  servoS.write(135);
  delay(500);

  servoS.write(180);
  delay(1500);
}