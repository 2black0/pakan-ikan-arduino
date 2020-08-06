void relayON() {
  digitalWrite(relay1Pin, LOW);
  digitalWrite(relay2Pin, LOW);
  delay(10);
}

void relayOFF() {
  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);
  delay(10);
}