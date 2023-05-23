// Manual Control (/*)
// The manual control system is implemented in this code using the analog sensor (LDR) and an actuator (LED). 
// A potentiometer (variable resistor) is used to change the input value in order to change the output. 

// Both the Serial Monitor and an LCD screen show the Input Value, Process Variable (PV), and Control Output (CO) readings.
// */
int sensor = A5;// Set the pin for the Sensor
int intputPin= A3; // Set the pin for the potentiometer which will be the SP
int actuator = 6; //  digital pin for the LED

int PV = 0; // The process variable which represents LDR value
int inputValue = 0; // Potentiometer value
int CO = 0; // Control output value
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(actuator, OUTPUT); // Make the actuator pin as an OUTPUT
  Serial.begin(9600);  // Initalize Serial Monitor with baud rate of 9600
   lcd.begin(16, 2); // Set up LCD's number of colums and rows

}

// the loop function runs over and over again forever
void loop() {
  PV = analogRead(sensor);
  // Read the input value ranges from 0 to 1023.
  inputValue= analogRead(intputPin);
    // Map the input value to the control output range of 0 to 255
  CO = map(inputValue, 0, 1023, 0, 255); 
  // Writing the  (CO) to the actuator (LED)
  analogWrite(actuator,CO);

  // Serial.print(" \t input = ");
  // Serial.print(inputValue);
  Serial.print(" \t CO = ");
  Serial.print(CO);
  Serial.print(" \t PV = ");
  Serial.print(PV);
  Serial.println();

lcd.setCursor(0,0); // set the postion on the lcd start from colunm 0 of the first row
lcd.print("CO = "); // lcd print the line: volatge = 
lcd.println(CO);
lcd.setCursor (0,1); // set the postion on the lcd start from colunm 0 of the second row
lcd.print (" PV = "); // lcd print the line: Bitvalue 
lcd.println(PV); // lcd print the Bit value
}

