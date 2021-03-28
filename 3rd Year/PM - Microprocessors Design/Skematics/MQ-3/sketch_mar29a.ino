float sensor_volt;
float RS_gas; 
float R0;
float ratio;
float BAC;
int R2 = 2000;

void setup() 
{
    Serial.begin(9600);
}

void loop() 
{
    int sensorValue = analogRead(A0);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas = ((5.0 * R2)/sensor_volt) - R2; 
   /*-Replace the value of R0 with the value of R0 in your test -*/
    R0 = 16000;
    ratio = RS_gas/R0;// ratio = RS/R0
    double x = 0.4*ratio;   
    BAC = pow(x,-1.431);  //BAC in mg/L
    Serial.print("BAC = ");
    Serial.print(BAC*0.0001);  //convert to g/dL
    Serial.print(" g/DL\n\n");
    delay(1000);
}
