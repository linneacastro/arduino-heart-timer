// C++ code
//

#include <SPI.h> // Include library to use SPI (Serial Peripheral Interface) mode to interact with MAX7219

#define Max7219_pinCLK 13 // Clock pin - synchronizes data transmission
#define Max7219_pinCS 7 // Chip Select pin.  Controller uses this pin to communicate with LED grid, especially in Write_Max7219 method.
                        // Data is loaded while CS is LOW and latched on rising edge (when CS goes high).
#define Max7219_pinDIN 11 // Data In pin.  Data is loaded into a 16-bit shift register on the clock's rising edge.

int button; // Button variable, used in Start button

// WRITE TO 7219 METHOD  - This method was taken directly from the MAx 7219 Datasheet provided with Elegoo parts.
// Using digitalWrite to specify what pin will receive data and on what edge, together with SPI keyword, trasfer.
// This method uses the fact that the Max 7219's CS pin (7), loads data on LOW and latches it in on the rising edge, when 
// CS goes high.  This accomodates data transfer to the LED matrix and is the main method involved in telling the matrix exactly which 
// lights will be on, by specific address (row number), and value (0 means OFF and 1 means ON).
void Write_Max7219(uint8_t address, uint8_t value){ // uint8_t is data type unsigned int 8 bit length
  digitalWrite(Max7219_pinCS, LOW); // Low to receive data
  SPI.transfer(address); // Send address 1-8, row of LED matrix
  SPI.transfer(value); // Send value for row to display B######## with # being either a 0/OFF 1/ON for respective row's position
  digitalWrite(Max7219_pinCS, HIGH); // Finish data transfer
}

// INITIALIZE 7219 METHOD - This method was taken directly from the Max 7219 Datasheet provided with Elegoo parts.
// The 7219 is in sleep mode upon start up, so this initialization method is needed to reset registers prior to use.
void Init_Max7219(void){
  Write_Max7219(0x09, 0x00); // Decoding BCD, No-Op register
  Write_Max7219(0x0a, 0x03); // Brightness/Intensity register
  Write_Max7219(0x0b, 0x07); // Scan limit
  Write_Max7219(0x0c, 0x03); // Power down/shutdown mode
  Write_Max7219(0x0f, 0x00); // Display test
}

// SETUP METHOD - This method 
void setup(){
  pinMode(Max7219_pinCLK,OUTPUT); // Clock, CS, and DIN pins on MAX7219 all designated as outputs
  pinMode(Max7219_pinCS,OUTPUT);
  pinMode(Max7219_pinDIN,OUTPUT);
  pinMode(2, INPUT); // For Start button
  SPI.begin(); // Begin SPI mode 
  delay(1000);
  Init_Max7219(); // Run this method to initialize 7219
}

// RESET LED GRID METHOD
void reset(){
  Write_Max7219(1, B00000000); // Reset LED grid
  Write_Max7219(2, B00000000);
  Write_Max7219(3, B00000000);
  Write_Max7219(4, B00000000);
  Write_Max7219(5, B00000000);
  Write_Max7219(6, B00000000);
  Write_Max7219(7, B00000000);
  Write_Max7219(8, B00000000);
}

// DISPLAY FULL HEART METHOD
void fullHeart(){
  Write_Max7219(1, B01101110); // Flash full heart
  Write_Max7219(2, B11101111);
  Write_Max7219(3, B11111111);
  Write_Max7219(4, B11111111);
  Write_Max7219(5, B01111110);
  Write_Max7219(6, B01111110);
  Write_Max7219(7, B00111100);
  Write_Max7219(8, B00011000);
}

// ENTER TIMER LOOP WHEN START BUTTON IS PRESSED
void loop(){
   reset(); // Call reset method to start with empty grid

   button = digitalRead(2); // Button state (High/LOW) is determined by pin 2
   int flag; // Create a flag and initialize it to 0
   flag = 0;

   if (button == LOW){ // If button gets pressed, it goes to LOW
     flag = 1; // Set flag to 1 when button is pressed
   }

   while(flag == 1){ // Start button has been pressed, flag=1, when flag == 1, start the timer and do the following:

   Write_Max7219(1, B01000000); // TOP ROW, ROW 1
   delay(500);
   Write_Max7219(1, B01100000);
   delay(500);
   Write_Max7219(1, B01101000);
   delay(500);
   Write_Max7219(1, B01101100);
   delay(500);
   Write_Max7219(1, B01101110);
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B10000000); // ROW 2, beginning to build ROW 2
   delay(500);
   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11000000); // ROW 2
   delay(500);
   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11100000); // ROW 2
   delay(500);
   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101000); // ROW 2
   delay(500);
   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101100); // ROW 2
   delay(500);
   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101110); // ROW 2
   delay(500);
   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2 complete
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B10000000); // ROW 3, beginning to build ROW 3
   delay(500);
   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11000000); // ROW 3
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11100000); // ROW 3
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11110000); // ROW 3
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111000); // ROW 3
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111100); // ROW 3
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111110); // ROW 3
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 complete
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B10000000); // ROW 4, beginning to build ROW 4
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11000000); // ROW 4
   delay(500);
   
   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11100000); // ROW 4
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11110000); // ROW 4
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111000); // ROW 4
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111100); // ROW 4
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111110); // ROW 4
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 complete
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01000000); // ROW 5, beginning ROW 5
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01100000); // ROW 5
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01110000); // ROW 5
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01111000); // ROW 5
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01111100); // ROW 5
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01111110); // ROW 5 complete
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01111110); // ROW 5
   Write_Max7219(6, B01000000); // ROW 6, beginning ROW 6
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01111110); // ROW 5
   Write_Max7219(6, B01100000); // ROW 6
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01111110); // ROW 5
   Write_Max7219(6, B01110000); // ROW 6
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01111110); // ROW 5
   Write_Max7219(6, B01111000); // ROW 6
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01111110); // ROW 5
   Write_Max7219(6, B01111100); // ROW 6 
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01111110); // ROW 5
   Write_Max7219(6, B01111110); // ROW 6 complete
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01111110); // ROW 5
   Write_Max7219(6, B01111110); // ROW 6 
   Write_Max7219(7, B00100000); // ROW 7, beginning ROW 7
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01111110); // ROW 5
   Write_Max7219(6, B01111110); // ROW 6 
   Write_Max7219(7, B00110000); // ROW 7
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01111110); // ROW 5
   Write_Max7219(6, B01111110); // ROW 6 
   Write_Max7219(7, B00111000); // ROW 7
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01111110); // ROW 5
   Write_Max7219(6, B01111110); // ROW 6 
   Write_Max7219(7, B00111100); // ROW 7 complete
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01111110); // ROW 5
   Write_Max7219(6, B01111110); // ROW 6 
   Write_Max7219(7, B00111100); // ROW 7 
   Write_Max7219(8, B00010000); // ROW 8, beginning ROW 8 
   delay(500);

   Write_Max7219(1, B01101110); // ROW 1
   Write_Max7219(2, B11101111); // ROW 2
   Write_Max7219(3, B11111111); // ROW 3 
   Write_Max7219(4, B11111111); // ROW 4 
   Write_Max7219(5, B01111110); // ROW 5
   Write_Max7219(6, B01111110); // ROW 6 
   Write_Max7219(7, B00111100); // ROW 7 
   Write_Max7219(8, B00011000); // ROW 8 complete
   delay(500);

   // TIMER COMPLETE, FLASH UNTIL RESET 
   while(1==1){
     reset(); // Flash empty grid

     delay(1000);

     fullHeart(); // Flash full heart

     delay(1000);
   }

}

}

