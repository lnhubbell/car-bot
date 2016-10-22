// Global Variables
    long t; // time in centi-seconds

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

DDRB = 0x00;
PCICR = 0x01; // Enable pin change interrupt 1 - page 92 in manual
                // ^ is connected to digital pin 8, or PORT B, 0
//PCINT0 = 0x01; // Pin change mask register 0 - page 96 in manual

// Set Up Timer 1 for blink thing
    TCCR1A = 0x00; // Want bits 1:0 to be 00, they're WGM3 1:0, and everything else too
    TCCR1B = 0x0C; // Bits 7:6 have to do with input capture, 5 is reserved, 4:3 are waveform generation
    // Bits 4:3 are WGM3 3:2, so we want them to be 0b01, b/c WGMn3:0 = 0b0100, table 20-6 page 171,
    //   because this is CTC mode which clears the counter once it gets to OCR3A
    // Bits 2:0 are the prescalar, p 173 table 20-7
    // I set it to 256 with 0b0100
    OCR1A = 0x0271; // Want the output compare register to be 625 to get 100Hz
    // 16 MHz, 16e6/256 = 62500
    TIMSK1 = 0b0010; // bits 3:1 enable the output compare C:A respectively match interrupt, 0 is overflow
}

void loop() {
//Serial.println(PCIFR,BIN);
//Serial.println(PCINT0,BIN);

Serial.print("Time = ");
Serial.println(t/100);

}

ISR(PCINT0_vect) {
  Serial.println("HO MY GAWD");
}

ISR(TIMER1_COMPA_vect){
    t = t + 1;
}

