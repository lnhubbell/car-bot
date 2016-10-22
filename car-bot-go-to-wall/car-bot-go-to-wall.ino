// GLOBAL VARIABLES
    unsigned long send_time = 0;        // the number of uS since system start until the pulse was sent
    unsigned long receive_time = 0;     // number of uS since system start until the pulse was received
    unsigned long distance = 0; 
    
// INCLUDES AND DEFINES
#define TRIGGER_PIN 2
#define ECHO_PIN 3
#define MOTOR1_PIN 10
#define MOTOR2_PIN 11

void setup() {
    Serial.begin(115200);               // start cereal communication
    // Setup inputs and outputs
    pinMode(TRIGGER_PIN, OUTPUT);       // trigger pin as output
    pinMode(ECHO_PIN, INPUT);           // echo pin as input
    digitalWrite(TRIGGER_PIN, LOW);     // Set trigger pin low so no accidents happen
    pinMode(MOTOR1_PIN, OUTPUT);        // Set pin controlling motor 1 as output
    pinMode(MOTOR2_PIN, OUTPUT);        // Set pin controlling motor 2 as output

    // Set up Interrupt 1 - INT1 is Pin 3 on the Arduino, PORT D pin 3
    EICRA = 0x04;       // Set type of interrupt, 01 is logical change, 3:2 are ISC1, 1:0 are ISC0 - 17.2.1 Page 89
    EIMSK = 0x02;       // Enable external interrupt request bit 1 is ISC1, bit 0 is ISC0 
}

void loop() {
    int pwrM1 = 0; int pwrM2 = 0;
    // If the pulse has been received more than 60ms ago, send out another pulse
    if(micros()>(receive_time+60000)){
        // Prepare for pulse
        send_time = 0; receive_time = 0;    // reset send/receive times
        // Send the pulse
        digitalWrite(TRIGGER_PIN, LOW); // make sure output pin is low
        delayMicroseconds(4);
        digitalWrite(TRIGGER_PIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIGGER_PIN, LOW);
        }// if

    // Calculate new distance
    if(receive_time>0){
        distance = (receive_time-send_time)/58; // distance in centimeters
        } //if
    
    // Control the motor power based on distance
    //pwrM1 = max(255,
    analogWrite(MOTOR1_PIN, pwrM1);
    analogWrite(MOTOR2_PIN, pwrM2);
    
}

ISR(INT1_vect) { // Interrupt vectors on page 92, this is pin 3
    send_time = max(send_time,(digitalRead(ECHO_PIN))*micros());         // if pin 3 goes from lo to hi, then it's the send time
    receive_time = max(receive_time,(!digitalRead(ECHO_PIN))*micros());  // if pin 3 goes from hi to lo then its the receive time
} // INT1 ISR
