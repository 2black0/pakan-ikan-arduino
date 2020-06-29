/*

Urutan test no 2
Program test untuk serial usb Arduino Uno
buka serial monitor dan set baudrate 9600 untuk menampilkan data yang dikirim
akan muncul tulisan 'data ke: i' sesuai dengan nilai i yang ada pada loop

kalau tidak dapat di upload atau data tidak muncul pastikan:
driver telah terinstall dengan baik
memilih Uno di board selection
pilih COM yang terdeteksi dengan benar
pilih baudrate pada serial monitor 9600

2black0@gmail.com
http://robot-terbang.web.id

*/

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  for (int i = 0; i < 100; i++)
  {
    Serial.print('data ke: ');
    Serial.println(i);
    delay(25);
  }
}
