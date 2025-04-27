#include <LiquidCrystal.h>

// Include All Peripheral Libraries Used By LINX
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Servo.h>

// Include Device Specific Header From Sketch>>Import Library (In This Case LinxChipkitMax32.h)
// Also Include Desired LINX Listener From Sketch>>Import Library (In This Case LinxSerialListener.h)
#include <LinxArduinoUno.h>
#include <LinxSerialListener.h>

// Create A Pointer To The LINX Device Object We Instantiate In Setup()
LinxArduinoUno* LinxDevice;
LiquidCrystal lcd(9, 11, 5, 4, 3, 2);

int myCustomCommand();

// Initialize LINX Device And Listener
void setup()
{
  // Instantiate The LINX Device
  LinxDevice = new LinxArduinoUno();

  // The LINXT Listener Is Pre Instantiated, Call Start And Pass A Pointer To The LINX Device And The UART Channel To Listen On
  LinxSerialConnection.Start(LinxDevice, 0);
  LinxSerialConnection.AttachCustomCommand(0, myCustomCommand);

  // Set up the LCD dimensions (columns, rows)
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);

  // Print the initial message on the LCD
  lcd.print("Temperature : ");

  // Print a welcome message on the LCD
}

void loop()
{
  // Listen For New Packets From LabVIEW
  LinxSerialConnection.CheckForCommands();

  // Your Code Here, But It will Slow Down The Connection With LabVIEW
}


int myCustomCommand(unsigned char numInputBytes, unsigned char* input, unsigned char* numResponseBytes, unsigned char* response)
{
  // Clear the LCD and move the cursor to the desired position
  lcd.clear();
  lcd.setCursor(0, 0);

  // Print the message "Temperature : "
  lcd.print("Temp : ");

  // Set the cursor to the desired position for the temperature value
  lcd.setCursor(12, 0);

  // Print the temperature value received from the input byte
  lcd.print(input[0]);

  // Set the cursor to the position after the temperature value
  lcd.setCursor(14, 0);

  // Print the degree symbol and the "C" for Celsius
  lcd.write(223);  // ASCII code for degree symbol
  lcd.print("C");

  // Check if the temperature is greater than 34
  if (input[1] == 5)
  {
    // Set the cursor to the second line and print "Fire detected"
    lcd.setCursor(0, 1);
    lcd.print("Fire detected");
  }

  response[0] = input[0];
  *numResponseBytes = numInputBytes;

  return 0;
}
