void relay_on()
{
  digitalWrite(relay1Pin, LOW);
  digitalWrite(relay2Pin, LOW);
  delay(10);
}

void relay_off()
{
  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);
  delay(10);
}