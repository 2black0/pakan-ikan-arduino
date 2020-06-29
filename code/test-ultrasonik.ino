/*

Urutan test no 6
Program test untuk serial usb Arduino Uno
buka serial monitor dan set baudrate 9600 untuk menampilkan data yang dikirim
akan muncul tulisan 'Distance: x' dimana x adalah jarak benda yang ada didepan sensor ultrasonik

kalau tidak dapat di upload atau data tidak muncul pastikan:
driver telah terinstall dengan baik
memilih Uno di board selection
pilih COM yang terdeteksi dengan benar
pilih baudrate pada serial monitor 9600
kabel SR04:
SR04-Trigger <- Uno-D6
SR04-Echo <-> Uno-D7

2black0@gmail.com
http://robot-terbang.web.id

*/

const int trigPin = 6;
const int echoPin = 7;

long duration;
int distance;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
}