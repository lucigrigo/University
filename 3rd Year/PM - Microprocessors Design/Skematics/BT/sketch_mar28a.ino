#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);
void setup()
{ 
mySerial.begin(9600);
Serial.begin(9600);

pinMode(LED_BUILTIN,OUTPUT);
}
void loop()
{
int i;
if (mySerial.available())
{
i=mySerial.read(); 
// Serial.println(i); 
Serial.println("DATA RECEIVED:"); 
if(i=='1')
{
digitalWrite(LED_BUILTIN,1);
Serial.println("led on");
}
if(i=='0')
{
digitalWrite(LED_BUILTIN,0);
Serial.println("led off");
}
}
}
