void send_sms(String text) {
  Serial.println("AT");
  // updateSerial();
  Serial.println("AT+CMGF=1");
  // updateSerial();
  Serial.println("AT+CMGS=" + noHP);
  // updateSerial();
  Serial.print(text);
  // updateSerial();
  Serial.write(26);
}

void updateSerial() {
  String data = "";
  delay(500);
  while (Serial.available()) {
    data = Serial.readString();
    lcd_show(1, 0, data, 500);
  }
}