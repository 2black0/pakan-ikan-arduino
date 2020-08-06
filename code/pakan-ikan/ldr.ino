int readLDR() {
  int sldrVal;
  sldrVal = analogRead(ldrPin);
  delay(5);
  return (sldrVal);
}