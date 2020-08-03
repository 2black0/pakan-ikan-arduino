void sim_com()
{
  Serial.println("AT");
  while (Serial.available())
  {
    data = Serial.readString();
  }
}