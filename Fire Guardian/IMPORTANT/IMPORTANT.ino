const int LCD_RS = 12;   // Register Select pin
const int LCD_EN = 11;   // Enable pin
const int LCD_D4 = 5;    // Data pin 4
const int LCD_D5 = 4;    // Data pin 5
const int LCD_D6 = 3;    // Data pin 6
const int LCD_D7 = 2;    // Data pin 7

void lcdCommand(byte command) {
  digitalWrite(LCD_RS, LOW);    // Set RS to command mode
  digitalWrite(LCD_EN, LOW);    // Set EN to low
  delayMicroseconds(100);       // Wait for stability
  
  // Send higher nibble
  digitalWrite(LCD_D4, (command >> 4) & 0x01);
  digitalWrite(LCD_D5, (command >> 5) & 0x01);
  digitalWrite(LCD_D6, (command >> 6) & 0x01);
  digitalWrite(LCD_D7, (command >> 7) & 0x01);
  
  digitalWrite(LCD_EN, HIGH);   // Set EN to high
  delayMicroseconds(100);       // EN pulse width
  digitalWrite(LCD_EN, LOW);    // Set EN to low
  delayMicroseconds(100);       // Wait for stability
  
  // Send lower nibble
  digitalWrite(LCD_D4, (command >> 0) & 0x01);
  digitalWrite(LCD_D5, (command >> 1) & 0x01);
  digitalWrite(LCD_D6, (command >> 2) & 0x01);
  digitalWrite(LCD_D7, (command >> 3) & 0x01);
  
  digitalWrite(LCD_EN, HIGH);   // Set EN to high
  delayMicroseconds(100);       // EN pulse width
  digitalWrite(LCD_EN, LOW);    // Set EN to low
  delayMicroseconds(100);       // Wait for stability
}

void lcdInit() {
  // Initialize the LCD in 4-bit mode
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_EN, OUTPUT);
  pinMode(LCD_D4, OUTPUT);
  pinMode(LCD_D5, OUTPUT);
  pinMode(LCD_D6, OUTPUT);
  pinMode(LCD_D7, OUTPUT);

  delay(50);   // Wait for the LCD to power up

  // Initialization sequence
  lcdCommand(0x28);   // 4-bit mode, 2 lines, 5x8 font
  lcdCommand(0x0C);   // Display on, cursor off
  lcdCommand(0x06);   // Entry mode: increment cursor
  lcdCommand(0x01);   // Clear display
  delay(2);          // Wait for the command to complete
}
void lcdWrite(byte value) {
  digitalWrite(LCD_RS, HIGH);    // Set RS to data mode
  digitalWrite(LCD_EN, LOW);     // Set EN to low
  delayMicroseconds(100);        // Wait for stability
  
  // Send higher nibble
  digitalWrite(LCD_D4, (value >> 4) & 0x01);
  digitalWrite(LCD_D5, (value >> 5) & 0x01);
  digitalWrite(LCD_D6, (value >> 6) & 0x01);
  digitalWrite(LCD_D7, (value >> 7) & 0x01);
  
  digitalWrite(LCD_EN, HIGH);    // Set EN to high
  delayMicroseconds(100);        // EN pulse width
  digitalWrite(LCD_EN, LOW);     // Set EN to low
  delayMicroseconds(100);        // Wait for stability
  
  // Send lower nibble
  digitalWrite(LCD_D4, (value >> 0) & 0x01);
  digitalWrite(LCD_D5, (value >> 1) & 0x01);
  digitalWrite(LCD_D6, (value >> 2) & 0x01);
  digitalWrite(LCD_D7, (value >> 3) & 0x01);
  
  digitalWrite(LCD_EN, HIGH);    // Set EN to high
  delayMicroseconds(100);        // EN pulse width
  digitalWrite(LCD_EN, LOW);     // Set EN to low
  delayMicroseconds(100);        // Wait for stability
}

void lcdPrint(const char* str) {
  while (*str) {
    lcdWrite(*str++);
  }
}
void setup() {
  lcdInit();    // Initialize the LCD
}

void loop() {
  lcdCommand(0x80);                 // Set cursor to the beginning of the first line
  lcdPrint("Hello, World!");       // Print a string

  lcdCommand(0xC0);                 // Set cursor to the beginning of the second line
  lcdPrint("Arduino LCD Demo");     // Print a string

  delay(2000);                      // Wait for 2 seconds

  lcdCommand(0x01);                 // Clear the display
  delay(2);                         // Wait for the command to complete

  delay(1000);                      // Wait for 1 second before repeating the loop
}