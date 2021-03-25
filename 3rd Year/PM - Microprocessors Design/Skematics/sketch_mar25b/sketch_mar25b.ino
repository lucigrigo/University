void setup()
{
  Serial.begin(9600);
  Serial.println("astept comenzi");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

char *buf;

void loop()
{
  if (Serial.available()){
    buf = (char *)malloc(20);
    memset(buf, 0, 20);
    int index = 0;

    while(Serial.available()) {
      char a = Serial.read();
      if(a == '\n')
        break;
      buf[index] = a;
      index++;
    }
    
    Serial.println(buf);
    
    if(strncmp(buf, "on", strlen("on")) == 0)
      digitalWrite(LED_BUILTIN, HIGH);
    if(strncmp(buf, "off", strlen("off")) == 0)
      digitalWrite(LED_BUILTIN, LOW);
    
    Serial.println(buf);
    free(buf);
  }
}
