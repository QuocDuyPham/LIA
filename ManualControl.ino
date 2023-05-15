int sensor = A1;
int intputPin= A5;
int actuator = 7;
int PV = 0;
int inputValue = 0;
int CO = 0;
int PushButton = 13;
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(2, 3, 9, 10, 11, 12); 
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(actuator, OUTPUT);
  pinMode(PushButton  , INPUT_PULLUP);
  Serial.begin(9600);
   lcd.begin(16, 2);

}

// the loop function runs over and over again forever
void loop() {
  int BinValue = digitalRead(PushButton);
  Serial.print( "PB = ");
  Serial.print(BinValue);
  PV = analogRead(sensor);
  inputValue= analogRead(intputPin);
  CO = map(inputValue, 0, 1023, 0, 255); 
  analogWrite(actuator,CO);

  Serial.print(" \t input = ");
  Serial.print(inputValue);
  Serial.print(" \t CO = ");
  Serial.print(CO);
  Serial.print(" \t PV = ");
  Serial.print(PV);
  Serial.println();
if (BinValue == 1){
lcd.setCursor(0,0); // set the postion on the lcd start from colunm 0 of the first row
lcd.print("CO = "); // lcd print the line: volatge = 
lcd.println(CO); // lcd print the voltage value
lcd.setCursor (0,1);
lcd.print("Input = "); // lcd print the line: volatge = 
lcd.println(inputValue); // lcd print the voltage value
}
else {
lcd.setCursor(0,0); // set the postion on the lcd start from colunm 0 of the first row
lcd.print("CO = "); // lcd print the line: volatge = 
lcd.println(CO);
lcd.setCursor (0,1); // set the postion on the lcd start from colunm 0 of the second row
lcd.print (" PV = "); // lcd print the line: Bitvalue 
lcd.println(PV); // lcd print the Bit value
}

}
