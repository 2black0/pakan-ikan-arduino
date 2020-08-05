void send_sms() {
  Serial.println("AT");
  updateSerial();
  Serial.println("AT+CMGF=1");
  updateSerial();
  Serial.println("AT+CMGS=\"+628123456789\"");
  updateSerial();
  Serial.print("Kasih Makan!!!");
  updateSerial();
  Serial.write(26);
}

void updateSerial() {
  delay(500);
  while (Serial.available()) {
    data = Serial.readString();
    lcd_show(1, 0, data, 500);
  }
}