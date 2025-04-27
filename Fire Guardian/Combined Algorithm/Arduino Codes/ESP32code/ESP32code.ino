// GSM module connections
#define GSM_SERIAL Serial1

// Pin connected to the fire detection sensor
const int fireSensorPin = 25;

// Variable to store the count of fire detections
int fireCount = 0;
String phoneNumber = "+94766353061";
String message = "Fire detected!";
void setup() {
  // Initialize serial communication with Arduino
  Serial.begin(115200);
  
  // Initialize serial communication with GSM module
  GSM_SERIAL.begin(115200, SERIAL_8N1, 16, 17);

  // Configure the fire sensor pin as input
  pinMode(fireSensorPin, INPUT);

  // Wait for the GSM module to start
  delay(2000);

  // Start GSM communication
  sendATCommand("AT");
  delay(1000);

  // Set text mode for SMS
  sendATCommand("AT+CMGF=1");
  delay(1000);

  // Enable the SMS notification when a new SMS is received
  sendATCommand("AT+CNMI=2,2,0,0,0");
  delay(1000);
}

void loop() {
  // Read the state of the fire sensor
  int fireState = digitalRead(fireSensorPin);

  // If fire is detected, increment the fire count and send an SMS
  if (fireState == HIGH) {
    fireCount++;
    Serial.println("Fire Detected!");

    // If the fire is detected more than 3 times, send an SMS and stop making calls
    if (fireCount > 2) {
      // Replace <PHONE_NUMBER> with the recipient's phone number
      String phoneNumber = "+94766353061";

      // Replace <MESSAGE_CONTENT> with the message you want to send
      String message = "Fire detected!";
      
      // Send the SMS
      sendSMS(phoneNumber, message);
      delay(5000);
    }
    else {
      // Make a call
      sendSMS(phoneNumber, message);
      delay(5000);
      makeCall();
    }
    
    // Wait for 10 seconds to avoid multiple detections in a short period
    delay(1000);
  }
  
  // If no fire is detected, reset the fire count
  if (fireState == LOW) {
    Serial.println("No Fire..");
    fireCount = 0;
    
    // Wait for 10 seconds to avoid multiple detections in a short period
    delay(1000);
  }
}

void sendATCommand(String command) {
  // Send AT command to GSM module
  GSM_SERIAL.println(command);
  
  // Wait for response
  delay(1000);

  // Read and print the response from GSM module
  while (GSM_SERIAL.available()) {
    Serial.write(GSM_SERIAL.read());
  }
}

void sendSMS(String phoneNumber, String message) {
  // Set the phone number of the recipient
  sendATCommand("AT+CMGS=\"" + phoneNumber + "\"");

  // Wait for ">" prompt
  delay(1000);

  // Send the message content
  GSM_SERIAL.print(message);

  // Send the ASCII code of the Ctrl+Z character to end the SMS
  GSM_SERIAL.write(26);

  // Wait for the SMS to be sent
  delay(5000);

  // Read and print the response from GSM module
  while (GSM_SERIAL.available()) {
    Serial.write(GSM_SERIAL.read());
  }
}

void makeCall() {
  // Replace <PHONE_NUMBER> with the recipient's phone number
  String phoneNumber = "+94766353061";
  
  // Dial the phone number
  sendATCommand("ATD" + phoneNumber + ";");

// Wait for the call to be connected (adjust delay time according to your requirements)
delay(10000);

// Hang up the call
sendATCommand("ATH");

// Wait for the hang-up process to complete
delay(2000);
}
