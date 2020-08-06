int readPH() {
  int spHVal;
  spHVal = analogRead(pHPin);
  delay(5);
  return (spHVal);
}