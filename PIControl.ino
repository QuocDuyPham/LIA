// Proportional Integral Control
// This code implements a proportional integral control system that measures the process variable (PV) with an analog sensor (LDR). 
// The control output (CO), which regulates the LED's brightness, is calculated using the error (SP - PV), proportional (pGain), and integral (iGain) gains.
// Four pushbuttons are also used, two of which, p Gain and i Gain, are used as up and down arrows to change the setpoint. 
// The LCD display's left and right pushbuttons are used to switch between its various screens. 
// Both the Serial Monitor and the LCD screen show the values of the process variable (PV), setpoint (SP), control output (CO), error, p Gain, and i Gain.

#include <LiquidCrystal.h> 
int sensor = A5;  // Declare pin for the LDR sensor
int actuator = 6;  // Declare the pin for the LED
int PV =0;        // Process variable 
int setPoint = 0; // Setpoint variable value
int CO = 0;    // Control output 
int Error = 0;  // Declare a variable to store the Error
float pGain = 0.01;   // Declare the Proportional Gain variable
float iGain = 0.01;  // Declare the Integral Gain variable
int integralAction; // Declare Integral Action value    
unsigned long previousMillis = 0; 
const long interval = 100;
unsigned long currentMillis; 
// Declare the PinS for Pushbuttons
const int buttonPin1 = 10;
const int buttonPin2 = 9;
const int buttonPin3 = 8;
const int buttonPin4 = 7;


// Button states and debounce variables
bool buttonState1, lastButtonState1, buttonState2, lastButtonState2, buttonState3, lastButtonState3, buttonState4, lastButtonState4 = false;
unsigned long lastButtonPress1, lastButtonPress2, lastButtonPress3, lastButtonPress4 = 0;
const unsigned long debounceDelay = 50;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// LCD page variable
int currentPage = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2); // Set up LCD's number of colums and  rows 
pinMode(actuator, OUTPUT); // Declare actuator pin as an OUTPUT
Serial.begin(9600); // Initialize Serial Monitor with baud rate of 9600
 pinMode(buttonPin1, INPUT_PULLUP);  // Declare PB1 as an INPUT PULLUP
 pinMode(buttonPin2, INPUT_PULLUP);  // Declare PB2 as an INPUT PULLUP
 pinMode(buttonPin3, INPUT_PULLUP);  // Declare PB3 as an INPUT PULLUP
 pinMode(buttonPin4, INPUT_PULLUP);  // Declare PB4 as an INPUT PULLUP
}

void loop() {
 // Read value of all four PB
 buttonState1 = digitalRead(buttonPin1);
 buttonState2 = digitalRead(buttonPin2);
 buttonState3 = digitalRead(buttonPin3);
 buttonState4 = digitalRead(buttonPin4);

   // Debounce and button actions 
PV = analogRead(sensor);
currentMillis = millis();

if (currentMillis - previousMillis >= interval){
  previousMillis = currentMillis;
  Error = setPoint-PV;  // Error is SP - PV
  // Ierror = iGain*intergralAction
  int Ierror= (iGain*integralAction);
   // The Integral is the Accumulation of the Error
  integralAction = (integralAction + Error);  
  CO = ((pGain *Error)+(Ierror));  // The controller output is P control + I control

if ( Ierror >=255){
  Ierror = 255; // put a maximum value of 255 on Ierror.
}
  if (CO > 255) {
  CO = 255; // If CO is greater than 255, set it to 255
} if (CO < 0) {
  CO = 0; // If CO is less than 0, set it to 0
}
}
analogWrite(actuator, CO);
  if (!buttonState1 && lastButtonState1 && (millis() - lastButtonPress1) > debounceDelay) {
   currentPage--;
   if (currentPage < 0) currentPage = 3;
   lastButtonPress1 = millis();  // Update the last time PB1 press 
 }
 lastButtonState1 = buttonState1; // Store current PB1 state


 if (!buttonState2 && lastButtonState2 && (millis() - lastButtonPress2) > debounceDelay) {
   currentPage++;
   if (currentPage > 3) currentPage = 0;
   lastButtonPress2 = millis();  // Update the last time PB2 press
 }
 lastButtonState2 = buttonState2; // Store current PB2 state


   if (!buttonState3 && lastButtonState3 && (millis() - lastButtonPress3) > debounceDelay) {
   if (currentPage == 0) {
     setPoint += 30; // increase setPoint by 30 if on the screen 0
   } else if (currentPage == 2) {
     pGain += 0.01; // increase pGain by 0.01 if on the screen 2
   }
   else if (currentPage == 3) { 
     iGain += 0.01; // increase iGain by 0.01 if on the screen 3
   }
   lastButtonPress3 = millis(); // Update the last time PB3 press 
 }
 lastButtonState3 = buttonState3;  // Store current PB3 state


 if (!buttonState4 && lastButtonState4 && (millis() - lastButtonPress4) > debounceDelay) {
   if (currentPage == 0) {
     setPoint -= 30 ; // degrease setPoint by 30 if on the screen 0
   } else if (currentPage == 2) {
     pGain -= 0.01; // degrease pGain by 0.01 if on the screen 2
   }
   else if (currentPage == 3) {
     iGain -= 0.01; // degrease iGain by 0.01 if on the screen 3
   }
   lastButtonPress4 = millis(); // Update the last time PB4 press 
 }
 lastButtonState4 = buttonState4; // Update the last time PB4 press 


 // Update the LCD display based on currentPage
 lcd.clear();
 switch (currentPage) {
   case 0:
     lcd.setCursor(0, 0);
     lcd.print("SP:");
     lcd.print(setPoint);
     break;
   case 1:
    lcd.setCursor(0, 0);
     lcd.print("Error:");
    lcd.print(Error);  
    lcd.setCursor(0, 1);
     lcd.print("CO:");
     lcd.print(CO); 
     break;
    case 2:
    lcd.setCursor(0, 0);
     lcd.print("pGain:");
     lcd.print(pGain); 
     break;  
    case 3:  
     lcd.setCursor(0, 0);
     lcd.print("iGain:");
     lcd.print(iGain);
     break;

 }
 delay(10);
 

  
  Serial.print("SP = ");
  Serial.print(setPoint);
//  Serial.print("\t CO = ");
//  Serial.print(CO);
  Serial.print("\t PV = ");
  Serial.print(PV);
  //Serial.print("\t P Gain = ");
  //Serial.print(pGain);
 // Serial.print("\t I Gain = ");
  //Serial.print(iGain);
//  Serial.print("\t Error :");
//Serial.print(Error);
Serial.println();
}
