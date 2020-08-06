int readLDR() {
  int ldrVal;
  ldrVal = analogRead(ldrPin);
  delay(5);
  return (ldrVal);
}