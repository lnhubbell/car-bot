unsigned long send_time = 0;
unsigned long break_time = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);

  pinMode(11, OUTPUT); 
  pinMode(10, INPUT); 
  pinMode(9, OUTPUT); 
  pinMode(8, OUTPUT);

  digitalWrite(11, LOW);
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);
  
}

void loop() {  
  delayMicroseconds(60000);
  break_time = millis(); 
  digitalWrite(9, LOW);
  delayMicroseconds(4);
  digitalWrite(9, HIGH);
  delayMicroseconds(10);
  digitalWrite(9, LOW);
  if (!digitalRead(10)) { // Right when the pules is tiggered, echo pin should be low
  
    while (!digitalRead(10))  { // Once the pulse is sent, the echo pin should go high, wait till then
        if ((millis()-break_time) > 4000) { // TIMEOUT
          break;
        }
    }

    if (digitalRead(10)) { // The pulse has been sent
      send_time = micros();
      while (digitalRead(10))  { // Wait for the pulse to return
        if ((millis()-break_time) > 4000) { // TIMEOUT
          Serial.println("FUCK YOU!");
          break;
        }
      }

      if (!digitalRead(10)) { // The prodigal pulse has returned!
        Serial.print("    Distance (cm): ");
        Serial.println((micros()-send_time)/58.0);
      }
    }
  }
//  }

}
