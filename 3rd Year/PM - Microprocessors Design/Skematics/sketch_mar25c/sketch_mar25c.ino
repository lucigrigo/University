void setup()
{
  Serial.begin(9600);
  Serial.println("astept comenzi");
}
 
void loop()
{
  if (Serial.available()) {
    char a = Serial.read();
    char buf[20];
    sprintf(buf, "%s: %c", "primit caracter", a);
    Serial.println(buf);
  }
}
