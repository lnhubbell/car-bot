void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

DDRB = 0x20;
}

void loop() {
  // put your main code here, to run repeatedly:
long x = millis();
delay(500);
PORTB = PORTB ^ 0x20;
//Serial.println(TCNT0);
//Serial.println(PORTB, BIN);
//Serial.println(PORTB);
Serial.println("split time");
Serial.println(millis() - x);
Serial.println("-------");
}
