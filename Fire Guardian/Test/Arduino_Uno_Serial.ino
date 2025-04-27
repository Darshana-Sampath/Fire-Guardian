#include <dummy.h>

/****************************************************************************************	
**  This is example LINX firmware for use with the Arduino Uno with the serial 
**  interface enabled.
**
**  For more information see:           www.labviewmakerhub.com/linx
**  For support visit the forums at:    www.labviewmakerhub.com/forums/linx
**  
**  Written By Sam Kristoff
**
**  BSD2 License.
****************************************************************************************/

//Include All Peripheral Libraries Used By LINX
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Servo.h>

//Include Device Specific Header From Sketch>>Import Library (In This Case LinxChipkitMax32.h)
//Also Include Desired LINX Listener From Sketch>>Import Library (In This Case LinxSerialListener.h)
#include <LinxArduinoUno.h>
#include <LinxSerialListener.h>

#include <LiquidCrystal.h>
 
//Create A Pointer To The LINX Device Object We Instantiate In Setup()
LinxArduinoUno* LinxDevice;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int myCustomCommand();
//Initialize LINX Device And Listener
void setup()
{
  //Instantiate The LINX Device
  LinxDevice = new LinxArduinoUno();
  
  //The LINXT Listener Is Pre Instantiated, Call Start And Pass A Pointer To The LINX Device And The UART Channel To Listen On
  LinxSerialConnection.Start(LinxDevice, 0); 
  LinxSerialConnection.AttachCustomCommand(0, myCustomCommand); 

  // Set up the LCD dimensions (columns, rows)
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  
  // Print a new message on the LCD
  lcd.print("Temperature");

  // Print a welcome message on the LCD
}

void loop()
{
  //Listen For New Packets From LabVIEW
  LinxSerialConnection.CheckForCommands();
  
  //Your Code Here, But It will Slow Down The Connection With LabVIEW
}
int myCustomCommand(unsigned char numInputBytes, unsigned char* input, unsigned char* numResponseBytes, unsigned char* response)
{ 
  // Clear the LCD and move the cursor to the first position
  // Clear the LCD and move the cursor to the first position
  //lcd.clear();
  lcd.setCursor(0, 1);

  // Print another message on the LCD
  lcd.print(input[0]);

  //delay(2000);
  response[0]=input[0];
  *numResponseBytes = numInputBytes;
   
  return 0;
}


