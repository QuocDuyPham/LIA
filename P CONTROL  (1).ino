// Proportional control ()
// By identifying the process variable (PV) using an analog sensor (LDR), proportional control is implemented in this code. 
// The error (SP - PV) and proportional gain (pGain) are used to calculate the control output (CO), which controls the LED's brightness.

// Four pushbuttons are also used, two of which are used as up and down arrows to change the setpoint and p Gain. 
// The LCD display's left and right pushbuttons are used to switch between its various screens. 
// Both the serial monitor and the LCD screen show the values for the process variable (PV), setpoint (SP), control output (CO), error, and p Gain.




// Include LiquidCrystal library for managing with LCD screen
#include <LiquidCrystal.h>
// Initialize the library by associating any needed LCD interfere pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(12,11,5,4,3,2);

// Declare Pins for Pushbuttons 
const int PBU = 10;
const int PBD = 9;
const int PBL = 8;
const int PBR = 7;

int sensor = A5; // Set the pin for the LDR sensor
int actuator = 6;  // Select the pin for the LED
int PV = 0;     // Process variable 
int setPoint = 0; // Setpoint variable value
int CO = 0;   // Control output value
float pGain = 0.01;  // Declare the Proportional Gain variable
int Error = 0;  // Declare a variable to store the Error


 


// Button states and debounce variables
bool PBLstate, lastButtonStateL, PBRstate, lastButtonStateR, PBUstate, lastButtonStateU, PBDstate, lastButtonStateD = false;
unsigned long lastButtonPressL, lastButtonPressR, lastButtonPressU, lastButtonPressD = 0;
const unsigned long debounceDelay = 50;


// LCD page variable
int Screen = 0;




void setup() {
pinMode(actuator, OUTPUT); // Declare Actuator as OUTPUT
 Serial.begin(9600); // Initialize Serial Monitor with baud rate of 9600
 lcd.begin(16, 2);  // Set up LCD's number of colums and rows   
 pinMode(PBL, INPUT_PULLUP); // Declare PB1 as an INPUT PULLUP
 pinMode(PBR, INPUT_PULLUP); // Declare PB2 as an INPUT PULLUP 
 pinMode(PBU, INPUT_PULLUP); // Declare PB3 as an INPUT PULLUP
 pinMode(PBD, INPUT_PULLUP); // Declare PB4 as an INPUT PULLUP
}


void loop() {
 // Read the sensor's value
  PV = analogRead(sensor);
  // Calculate the Error
     Error = setPoint - PV;
  // Calculate control output (CO) by multiplying the Erro by the p Gain
    CO = (pGain * Error); 


      if (CO >255)
   {
       CO = 255;  // the max value of CO to not exceed 255
     }
     if (CO<0)
     {
       CO = 0; // the min value of CO to not exceed 255
        }  
     if (Error < 0){
      Error = 0; // Make sure that the Error won't below 0
     }
 // Writing the CO to the LED
  analogWrite(actuator, CO); 
 // Read the values of four PB
 PBLstate = digitalRead(PBL);
 PBRstate = digitalRead(PBR);
 PBUstate = digitalRead(PBU);
 PBDstate = digitalRead(PBD);


//Serial Plotter
 /* Serial.print(setPoint);
  Serial.print(",");
  Serial.print(CO);
  Serial.print(",");
  Serial.print(PV);
  Serial.print(",");
  Serial.print(HYS);
  Serial.println();*/


//Serial Monitor 
Serial.print("SP = ");
Serial.print(setPoint);
//Serial.print("\t  CO = ");
//Serial.print(CO);
Serial.print("\t  PV = ");
Serial.println(PV);
//Serial.print("\t  CO = ");
//Serial.print(CO);
//Serial.print("\t  Error = ");
//Serial.println(Error);
//Serial.print("\t  pGain = ");
//Serial.println(pGain);
//Serial.print("\t  Screen: ");
//Serial.println(Screen);
 
 if (!PBLstate && lastButtonStateL && (millis() - lastButtonPressL) > debounceDelay) {
   Screen = 0;
   //if (Screen < 0) Screen= 1;
   lastButtonPressL = millis(); // Update the last time PBL press 
 }
 lastButtonStateL = PBLstate; // Store current PBL state


 if (!PBRstate && lastButtonStateR && (millis() - lastButtonPressR) > debounceDelay) {
   Screen = 1;
  // if (Screen > 1) Screen = 0;
   lastButtonPressR = millis(); // Update the last time PBR press 
 }
 lastButtonStateR = PBRstate; // Store current PBR state



   if (!PBUstate && lastButtonStateU && (millis() - lastButtonPressU) > debounceDelay) {
   if (Screen == 0) {
     setPoint+=50; // Increase SP by 50 if on the first(0) screen
   } else if (Screen == 1) {
     pGain+=0.01;  // Increase pGain by 0.01 if on the second(1) screen
   }
   lastButtonPressU = millis(); // Update the last time PBU press 
 }
 lastButtonStateU = PBUstate;  // Store current PBU state


 if (!PBDstate && lastButtonStateD && (millis() - lastButtonPressD) > debounceDelay) {
   if (Screen == 0) {
     setPoint-=50; // Decrease SP by 50 if on the first(0) screen
   } else if (Screen == 1) {
     pGain-=0.01;  // Decrease pGai by 0.01 if on the second(1) screen
   }
   lastButtonPressD = millis(); // Update the last time PBD press 
 }
 lastButtonStateD = PBDstate;  // Store current PBD state


 // Update the LCD display based on currentPage
 lcd.clear();
 switch (Screen) {
   case 0:
     lcd.setCursor(0, 0);
     lcd.print("PV=");
     lcd.print(PV);
     lcd.setCursor(8, 0);
     lcd.print("CO=");
     lcd.print(CO);
     lcd.setCursor(0, 1);
     lcd.print("SP = ");
     lcd.print(setPoint);
     break;
    case 1:
     lcd.setCursor(0, 0);
     lcd.print("PV=");
     lcd.print(PV);
     lcd.setCursor(9, 0);
     lcd.print("CO=");
     lcd.print(CO);
     lcd.setCursor(0, 1);
     lcd.print("pGain = ");
     lcd.print(pGain);
     break;
 }

 // Delay to avoid screen flicker
 delay(100);
}

