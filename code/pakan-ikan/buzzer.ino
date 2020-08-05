void buzzer_on(int timedelay) {
  digitalWrite(buzPin, LOW);
  delay(timedelay);
  digitalWrite(buzPin, HIGH);
}