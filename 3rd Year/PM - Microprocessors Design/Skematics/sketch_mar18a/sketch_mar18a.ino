ISR(TIMER1_COMPA_vect) {
  PORTD ^= (1 << PD6);
}

void setup() {
  DDRD |= (1 << PD6);
  pinMode(13, OUTPUT);
  
  cli();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 279;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS11) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

void loop() {
  OCR1A=279;
  digitalWrite(13, HIGH);
  delay(500);
  OCR1A=559;
  digitalWrite(13, LOW);
  delay(500);
}
