const int SR1_in = 1;
const int SR2_in = 4;
const int SR1_clk = 3;
const int SR2_clk = 6;
const int SR1_out = 2;
const int SR2_out = 5;
const int SR1_clr = 7;
const int SR2_clr = 8;

int low_lim;
int high_lim;

void setup() {
  pinMode(SR1_in, OUTPUT);
  pinMode(SR2_in, OUTPUT);
  pinMode(SR1_clk, OUTPUT);
  pinMode(SR2_clk, OUTPUT);
  pinMode(SR1_out, OUTPUT);
  pinMode(SR2_out, OUTPUT);
  pinMode(SR1_clr, OUTPUT);
  pinMode(SR2_clr, OUTPUT);

  low_lim = 0;
  high_lim = 8;
}

void loop() {
  int delayPeriod = 1000;

  if(low_lim == 5) {
    low_lim = 0;
    high_lim = 8;
  }

  digitalWrite(SR1_out, LOW);
  digitalWrite(SR2_out, LOW);

  for(int i = 0; i < 8; i++) {
    if(i < low_lim) {
      digitalWrite(SR1_clk, LOW);
      digitalWrite(SR1_in, LOW);
      digitalWrite(SR1_clk, HIGH);

      digitalWrite(SR2_clk, LOW);
      digitalWrite(SR2_in, LOW);
      digitalWrite(SR2_clk, HIGH);
    } else if (i > low_lim < high_lim) {
      digitalWrite(SR1_clk, LOW);
      digitalWrite(SR1_in, HIGH);
      digitalWrite(SR1_clk, HIGH);

      digitalWrite(SR2_clk, LOW);
      digitalWrite(SR2_in, HIGH);
      digitalWrite(SR2_clk, HIGH);
    } else {
      digitalWrite(SR1_clk, LOW);
      digitalWrite(SR1_in, LOW);
      digitalWrite(SR1_clk, HIGH);

      digitalWrite(SR2_clk, LOW);
      digitalWrite(SR2_in, LOW);
      digitalWrite(SR2_clk, HIGH);
    }
    
  }

  digitalWrite(SR1_out, HIGH);
  digitalWrite(SR2_out, HIGH);

  delay(delayPeriod);

  digitalWrite(SR1_clr, LOW);
  digitalWrite(SR2_clr, LOW);

  high_lim = high_lim - 1;
  low_lim = low_lim + 1;
}

  // smiley face
  
  // digitalWrite(SR1_clr, HIGH);
  // digitalWrite(SR2_clr, HIGH);
  
  // // litera I
  // digitalWrite(SR1_out, LOW);
  // digitalWrite(SR2_out, LOW);
  
  // // VCC SR
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, LOW);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, LOW);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, LOW);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, HIGH);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, HIGH);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, LOW);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, LOW);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, LOW);
  // digitalWrite(SR1_clk, HIGH);
  
  // // GND SR
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, LOW);
  // digitalWrite(SR2_clk, HIGH);
  
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, HIGH);
  // digitalWrite(SR2_clk, HIGH);
  
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, HIGH);
  // digitalWrite(SR2_clk, HIGH);
  
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, HIGH);
  // digitalWrite(SR2_clk, HIGH);
  
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, HIGH);
  // digitalWrite(SR2_clk, HIGH);
  
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, HIGH);
  // digitalWrite(SR2_clk, HIGH);
  
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, HIGH);
  // digitalWrite(SR2_clk, HIGH);
  
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, LOW);
  // digitalWrite(SR2_clk, HIGH);
  
  // // afisare litera I
  // digitalWrite(SR1_out, HIGH);
  // digitalWrite(SR2_out, HIGH);
  
  // delay(delayPeriod);
  
  // // golire SR
  // digitalWrite(SR1_clr, LOW);
  // digitalWrite(SR2_clr, LOW);
  // digitalWrite(SR1_clr, HIGH);
  // digitalWrite(SR1_clr, HIGH);

  // // afisare spatiu gol
  // digitalWrite(SR1_out, LOW);
  // digitalWrite(SR2_out, LOW);
  // for(int i = 0; i < 8; ++i) {
  //  	digitalWrite(SR1_clk, LOW);
  //   digitalWrite(SR1_in, LOW);
  //   digitalWrite(SR1_clk, HIGH);
    
  //   digitalWrite(SR2_clk, LOW);
  //   digitalWrite(SR2_in, LOW);
  //   digitalWrite(SR2_clk, HIGH);
  // }
  // digitalWrite(SR1_out, HIGH);
  // digitalWrite(SR2_out, HIGH);
  
  // delay(delayPeriod);
  
  // // golire SR
  // digitalWrite(SR1_clr, LOW);
  // digitalWrite(SR2_clr, LOW);
  // digitalWrite(SR1_clr, HIGH);
  // digitalWrite(SR1_clr, HIGH);
  
  // // litera C
  // digitalWrite(SR1_out, LOW);
  // digitalWrite(SR2_out, LOW);
  
  // // VCC SR
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, LOW);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, HIGH);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, HIGH);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, HIGH);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, HIGH);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, HIGH);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, HIGH);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, LOW);
  // digitalWrite(SR1_clk, HIGH);
  
  // // GND SR
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, LOW);
  // digitalWrite(SR2_clk, HIGH);
  
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, HIGH);
  // digitalWrite(SR2_clk, HIGH);
  
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, HIGH);
  // digitalWrite(SR2_clk, HIGH);
  
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, LOW);
  // digitalWrite(SR2_clk, HIGH);
  
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, LOW);
  // digitalWrite(SR2_clk, HIGH);
  
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, HIGH);
  // digitalWrite(SR2_clk, HIGH);
  
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, HIGH);
  // digitalWrite(SR2_clk, HIGH);
  
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, LOW);
  // digitalWrite(SR2_clk, HIGH);
  
  // // afisare litera C
  // digitalWrite(SR1_out, HIGH);
  // digitalWrite(SR2_out, HIGH);
  
  // delay(delayPeriod);
  
  // // golire SR
  // digitalWrite(SR1_clr, LOW);
  // digitalWrite(SR2_clr, LOW);
  // digitalWrite(SR1_clr, HIGH);
  // digitalWrite(SR1_clr, HIGH);

  // // afisare spatiu gol
  // digitalWrite(SR1_out, LOW);
  // digitalWrite(SR2_out, LOW);
  // for(int i = 0; i < 8; ++i) {
  //  	digitalWrite(SR1_clk, LOW);
  //   digitalWrite(SR1_in, LOW);
  //   digitalWrite(SR1_clk, HIGH);
    
  //   digitalWrite(SR2_clk, LOW);
  //   digitalWrite(SR2_in, LOW);
  //   digitalWrite(SR2_clk, HIGH);
  // }
  // digitalWrite(SR1_out, HIGH);
  // digitalWrite(SR2_out, HIGH);
  
  // delay(delayPeriod);
  // // golire SR
  // digitalWrite(SR1_clr, LOW);
  // digitalWrite(SR2_clr, LOW);
  // digitalWrite(SR1_clr, HIGH);
  // digitalWrite(SR1_clr, HIGH);
  
  // // litera U
  // digitalWrite(SR1_out, LOW);
  // digitalWrite(SR2_out, LOW);
  
  // // VCC SR
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, LOW);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, HIGH);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, HIGH);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, HIGH);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, HIGH);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, HIGH);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, HIGH);
  // digitalWrite(SR1_clk, HIGH);
  
  // digitalWrite(SR1_clk, LOW);
  // digitalWrite(SR1_in, LOW);
  // digitalWrite(SR1_clk, HIGH);
  
  // // GND SR
  // digitalWrite(SR2_clk, LOW);
  // digitalWrite(SR2_in, 
  // digitalWrite(SR2_clk, HIGH);
 
  // digitalWrite(SR2_clk, LOW);

  // digitalWrite(SR2_clk, HIGH);
 
  // digitalWrite(SR2_clk, LOW);

  // digitalWrite(SR2_clk, HIGH);
 
  // digitalWrite(SR2_clk, LOW);

  // digitalWrite(SR2_clk, HIGH);
 
  // digitalWrite(SR2_clk, LOW);

  // digitalWrite(SR2_clk, HIGH);
 
  // digitalWrite(SR2_clk, LOW);

  // digitalWrite(SR2_clk, HIGH);
 
  // digitalWrite(SR2_clk, LOW);

  // digitalWrite(SR2_clk, HIGH);
 
  // digitalWrite(SR2_clk, LOW);

  // digitalWrite(SR2_clk, HIGH); 
  
  // // afisare litera U
  // digitalWrite(SR1_out, HIGH);
  // digitalWrite(SR2_out, HIGH);
  // delay(delayPeriod);
  
  // // golire SR
  // digitalWrite(SR1_clr, LOW);
  // digitalWrite(SR2_clr, LOW);
  // digitalWrite(SR1_clr, HIGH);
  // digitalWrite(SR1_clr, HIGH);

  // // afisare spatiu gol
  // digitalWrite(SR1_out, LOW);
  // digitalWrite(SR2_out, LOW);
  // for(int i = 0; i < 8; ++i) {
  //  	digitalWrite(SR1_clk, LOW);
  //   digitalWrite(SR1_in, LOW);
  //   digitalWrite(SR1_clk, HIGH);
    
  //   digitalWrite(SR2_clk, LOW);
  //   digitalWrite(SR2_in, LOW);
  //   digitalWrite(SR2_clk, HIGH);
  // }
  // digitalWrite(SR1_out, HIGH);
  // digitalWrite(SR2_out, HIGH);
  
  // delay(delayPeriod);
  
  // // litera L
  // digitalWrite(SR1_out, LOW);
  // digitalWrite(SR2_out, LOW);
  
  // // VCC SR
  
  // // GND SR
  
  // // afisare litera L
  // digitalWrite(SR1_out, HIGH);
  // digitalWrite(SR2_out, HIGH);
  
  // delay(delayPeriod);
  
  // // golire SR
  // digitalWrite(SR1_clr, LOW);
  // digitalWrite(SR2_clr, LOW);
  // digitalWrite(SR1_clr, HIGH);
  // digitalWrite(SR1_clr, HIGH);

  // // afisare spatiu gol
  // digitalWrite(SR1_out, LOW);
  // digitalWrite(SR2_out, LOW);
  // for(int i = 0; i < 8; ++i) {
  //  	digitalWrite(SR1_clk, LOW);
  //   digitalWrite(SR1_in, LOW);
  //   digitalWrite(SR1_clk, HIGH);
    
  //   digitalWrite(SR2_clk, LOW);
  //   digitalWrite(SR2_in, LOW);
  //   digitalWrite(SR2_clk, HIGH);
  // }
  // digitalWrite(SR1_out, HIGH);
  // digitalWrite(SR2_out, HIGH);
  
  // delay(delayPeriod);
  
// }