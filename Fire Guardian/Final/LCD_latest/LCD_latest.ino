/*********
**  This is example LINX firmware for use with the Arduino Uno with the serial 
**  interface enabled.
**
**  For more information see:           www.labviewmakerhub.com/linx
**  For support visit the forums at:    www.labviewmakerhub.com/forums/linx
**  
**  Written By Sam Kristoff
**
**  BSD2 License.
******************************/

//Include All Peripheral Libraries Used By LINX
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Servo.h>

//Include Device Specific Header From Sketch>>Import Library (In This Case LinxChipkitMax32.h)
//Also Include Desired LINX Listener From Sketch>>Import Library (In This Case LinxSerialListener.h)
#include <LinxArduinoUno.h>
#include <LinxSerialListener.h>
 
//Create A Pointer To The LINX Device Object We Instantiate In Setup()
LinxArduinoUno* LinxDevice;
int clp();
//Initialize LINX Device And Listener
void setup()
{
  //Instantiate The LINX Device
  LinxDevice = new LinxArduinoUno();
  
  //The LINXT Listener Is Pre Instantiated, Call Start And Pass A Pointer To The LINX Device And The UART Channel To Listen On
  LinxSerialConnection.Start(LinxDevice, 0);  
  LinxSerialConnection.AttachCustomCommand(0, clp);
}

void loop()
{
  //Listen For New Packets From LabVIEW
  LinxSerialConnection.CheckForCommands();
  
  //Your Code Here, But It will Slow Down The Connection With LabVIEW
}

int clp(unsigned char numInputBytes, unsigned char* input, unsigned char* numResponseBytes, unsigned char* response)
{
  #define RS 12
  #define RW 9
  #define E 11
  #define DB4 5
  #define DB5 4
  #define DB6 3
  #define DB7 2
  
  pinMode(RS, OUTPUT);
  pinMode(RW, OUTPUT); // We didn't define this pin, because it is alwayes keep at LOW.
  pinMode(E, OUTPUT);
  pinMode(DB4, OUTPUT);
  pinMode(DB5, OUTPUT);
  pinMode(DB6, OUTPUT);
  pinMode(DB7, OUTPUT);
   
  int Channels[4] = {5, 4, 3, 2}; // Data bus pins from DB4 to DB7.
 
  int variable[4]; // Dummy array for bit shifting each input byte
 
  //-----------------------------------------------------------------
  // FUNCTION SET (4-bit mode)
  delay(30);
  digitalWrite(E, LOW);
  digitalWrite(RS, LOW);
  delayMicroseconds(100);       // Wait for stability
  // Send higher nibble
  digitalWrite(DB7, LOW);
  digitalWrite(DB6, LOW);
  digitalWrite(DB5, HIGH);
  digitalWrite(DB4, LOW);  // Set to 4-bit mode

  digitalWrite(E, HIGH);   // Set EN to high
  delayMicroseconds(100);       // EN pulse width
  digitalWrite(E, LOW);    // Set EN to low
  delayMicroseconds(100);       // Wait for stability
  // Send lower nibble
  digitalWrite(DB7, HIGH);
  digitalWrite(DB6, LOW);
  digitalWrite(DB5, LOW);
  digitalWrite(DB4, LOW);  // Set to 4-bit mode

  digitalWrite(E, HIGH);   // Set EN to high
  delayMicroseconds(100);       // EN pulse width
  digitalWrite(E, LOW);    // Set EN to low
  delayMicroseconds(100);       // Wait for stability
  //-----------------------------------------------------------------------
  // DISPLAY ON/OFF CONTROL
  digitalWrite(E, LOW);
  digitalWrite(RS, LOW);
  delayMicroseconds(100);       // Wait for stability
  // Send higher nibble
  digitalWrite(DB7, LOW);
  digitalWrite(DB6, LOW);
  digitalWrite(DB5, LOW);
  digitalWrite(DB4, LOW);  // Set to 4-bit mode

  digitalWrite(E, HIGH);   // Set EN to high
  delayMicroseconds(100);       // EN pulse width
  digitalWrite(E, LOW);    // Set EN to low
  delayMicroseconds(100);       // Wait for stability
  // Send lower nibble
  digitalWrite(DB7, HIGH);
  digitalWrite(DB6, HIGH);
  digitalWrite(DB5, LOW);
  digitalWrite(DB4, LOW);  // Set to 4-bit mode

  digitalWrite(E, HIGH);   // Set EN to high
  delayMicroseconds(100);       // EN pulse width
  digitalWrite(E, LOW);    // Set EN to low
  delayMicroseconds(100);       // Wait for stability
  //-----------------------------------------------------------------------

  // ENTRY MODE SET
  digitalWrite(E, LOW);
  digitalWrite(RS, LOW);
  delayMicroseconds(100);       // Wait for stability
  // Send higher nibble
  digitalWrite(DB7, LOW);
  digitalWrite(DB6, LOW);
  digitalWrite(DB5, LOW);
  digitalWrite(DB4, LOW);  // Set to 4-bit mode

  digitalWrite(E, HIGH);   // Set EN to high
  delayMicroseconds(100);       // EN pulse width
  digitalWrite(E, LOW);    // Set EN to low
  delayMicroseconds(100);       // Wait for stability
  // Send lower nibble
  digitalWrite(DB7, LOW);
  digitalWrite(DB6, HIGH);
  digitalWrite(DB5, HIGH);
  digitalWrite(DB4, LOW);  // Set to 4-bit mode

  digitalWrite(E, HIGH);   // Set EN to high
  delayMicroseconds(100);       // EN pulse width
  digitalWrite(E, LOW);    // Set EN to low
  delayMicroseconds(100);       // Wait for stability
  //-----------------------------------------------------------------------

  // DISPLAY CLEAR
  digitalWrite(E, LOW);
  digitalWrite(RS, LOW);
  delayMicroseconds(100);       // Wait for stability
  // Send higher nibble
  digitalWrite(DB7, LOW);
  digitalWrite(DB6, LOW);
  digitalWrite(DB5, LOW);
  digitalWrite(DB4, LOW);  // Set to 4-bit mode

  digitalWrite(E, HIGH);   // Set EN to high
  delayMicroseconds(100);       // EN pulse width
  digitalWrite(E, LOW);    // Set EN to low
  delayMicroseconds(100);       // Wait for stability
  // Send lower nibble
  digitalWrite(DB7, LOW);
  digitalWrite(DB6, LOW);
  digitalWrite(DB5, LOW);
  digitalWrite(DB4, HIGH);  // Set to 4-bit mode

  digitalWrite(E, HIGH);   // Set EN to high
  delayMicroseconds(100);       // EN pulse width
  digitalWrite(E, LOW);    // Set EN to low
  delayMicroseconds(100);       // Wait for stability
  //-----------------------------------------------------------------------
 
  delay(2);
 
  // End initialization!
 
  // Convert input to bytes
  for (int i = 0; i < numInputBytes; i++)
  {
    input[i] = byte(input[i]);
  }
   
  // Read each byte from the input array and write each channel high or low for each bit position in the data bus.
  for (int j = 0; j < numInputBytes; j++)
  {
    digitalWrite(E, LOW); // Prepare for a new letter or number by writing E HIGH and the following RS, RW values
    digitalWrite(RS, HIGH);
    //digitalWrite(RW, LOW);
    for (int i = 0; i < 4; i++)
    {
      variable[i] = input[j] & 1;
      if (variable[i] == 1)
      {
        digitalWrite(Channels[i], HIGH);
      }
      else
      {
        digitalWrite(Channels[i], LOW);
      }
      input[j] = input[j] >> 1;
    }
    digitalWrite(E, HIGH);    // Set EN to high
    delayMicroseconds(100);        // EN pulse width
    digitalWrite(E, LOW);     // Set EN to low
    delayMicroseconds(100);        // Wait for stability

    for (int i = 4; i < 8; i++)
    {
      variable[i] = input[j] & 1;
      if (variable[i] == 1)
      {
        digitalWrite(Channels[i], HIGH);
      }
      else
      {
        digitalWrite(Channels[i], LOW);
      }
      input[j] = input[j] >> 1;
    }

    digitalWrite(E, HIGH);    // Set EN to high
    delayMicroseconds(100);        // EN pulse width
    digitalWrite(E, LOW);     // Set EN to low
    delayMicroseconds(100);        // Wait for stability

  }
  
  response[0] = 0;
  *numResponseBytes = 1;
  return 0;
}