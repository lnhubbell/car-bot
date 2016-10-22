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
  Serial.println("Lezz Do This");
}

void loop() {
    char t[1000];
    char pin10[1000];
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
    // record 1000 data points
    Serial.print("test0");
    for (int i = 0; i < 10; i ++){
        t[i] = micros();
        pin10[i] = digitalRead(10);
        } // for
    Serial.print("test1");
    // Print data to screen
    for (int j = 0; j > 10; j++){
    Serial.print(pin10[j]);
    } // for
    Serial.print("test2");
    delay(500);  
  }

