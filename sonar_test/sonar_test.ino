unsigned long send_time = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

  pinMode(11, OUTPUT); 
  pinMode(10, INPUT); 
  pinMode(9, OUTPUT); 
  pinMode(8, OUTPUT);

  digitalWrite(11, LOW);
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
//  if (millis()%50 == 0) {
//    delay(1); // Must wait to avoid multiple pulses in one millis
  delay(50);
  digitalWrite(9, LOW);
  delayMicroseconds(4);
  digitalWrite(9, HIGH);
  delayMicroseconds(10);
  digitalWrite(9, LOW);
  send_time = millis();
  Serial.println("Preparing pulse...");

  if (!digitalRead(10)) { // Right when the pules is tiggered, echo pin should be low
  
    while (!digitalRead(10))  { // Once the pulse is sent, the echo pin should go high, wait till then
      if ((millis()-send_time) > 4000) break;
    }

    if (digitalRead(10)) { // The pulse has been sent
      Serial.println("    pulsed.");
    
      Serial.println("Waiting for echo...");
      while (digitalRead(10))  {
        if ((millis()-send_time) > 4000) break;
      }

      if (!digitalRead(10)) {
        Serial.print("    Response time (millis): ");
        Serial.println((millis()-send_time));
      }
    }
  }
//  }

}
