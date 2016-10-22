// Global Variables
    long t; // time in centi-seconds
    unsigned int nTrips = 0; // this will increment 1 each time the interrupt is executed
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

DDRB = 0x00;
DDRD = 0x00; //Set whether or not PORT D pins are input / output
//PCICR = 0x01; // Enable pin change interrupt 1 - page 92 in manual
                // ^ is connected to digital pin 8, or PORT B, 0
//PCINT0 = 0x01; // Pin change mask register 0 - page 96 in manual

// Set up Interrupt 1 - INT1 is Pin 3 on the arduino, D3
    //MCUCR |= 0x01; // Write interrupt vector change enable (IVCE) bit to 1 - 16.2.2 Page 85 in manual
    //MCUCR // Within 4 clock cycles write what you want to IVSEl and write 0 to IVCE

    EICRA = 0x0C;       // Set type of interrupt, 11 is Rising edge, 3:2 are ISC1, 1:0 are ISC0 - 17.2.1 Page 89
    EIMSK = 0x02;       // Enable external interrupt request bit 1 is ISC1, bit 0 is ISC0
    
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
//Serial.println((0x100 + MCUCR),BIN);
//Serial.println(PCINT0,BIN);

//Serial.print("Time = ");
//Serial.println(t/100);
Serial.println(nTrips);
Serial.print(t/100);
Serial.print("-----------");
delay(500);
}

ISR(INT1_vect) { // Interrupt vectors on page 92
  nTrips++;
  for (int x = 0; x < 10000; x ++){}
  //delay(100);
}

ISR(TIMER1_COMPA_vect){
    t++;
}

