// Include LiquidCrystal library for managing with LCD screen
#include <LiquidCrystal.h>
// Initialize the library by associating any needed LCD interfere pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(12,11,5,4,3,2);

// Pushbuttons
const int PBU = 10;
const int PBD = 9;
const int PBL = 8;
const int PBR = 7;

int sensor = A5;
int actuator = 6;
int PV = 0;
int setPoint = 0;
int CO = 0;
float pGain = 0.1;
int Error = 0;


 


// Button states and debounce variables
bool PBLstate, lastButtonStateL, PBRstate, lastButtonStateR, PBUstate, lastButtonStateU, PBDstate, lastButtonStateD = false;
unsigned long lastButtonPressL, lastButtonPressR, lastButtonPressU, lastButtonPressD = 0;
const unsigned long debounceDelay = 50;


// LCD page variable
int Screen = 0;




void setup() {
pinMode(actuator, OUTPUT);
 Serial.begin(9600);
 lcd.begin(16, 2);
 pinMode(PBL, INPUT_PULLUP);
 pinMode(PBR, INPUT_PULLUP);
 pinMode(PBU, INPUT_PULLUP);
 pinMode(PBD, INPUT_PULLUP);
}


void loop() {
  PV = analogRead(sensor);
     Error = setPoint - PV;
    CO = (pGain * Error); 


      if (CO >255)
   {
       CO = 255;
     }
     if (CO<0)
     {
       CO = 0;
        }  
  analogWrite(actuator, CO); 
 // Debounce and button actions
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
Serial.print(PV);
Serial.print("\t  CO = ");
Serial.print(CO);
Serial.print("\t  Error = ");
Serial.print(Error);
Serial.print("\t  pGain = ");
Serial.println(pGain);
//Serial.print("\t  Screen: ");
//Serial.println(Screen);
 
 if (!PBLstate && lastButtonStateL && (millis() - lastButtonPressL) > debounceDelay) {
   Screen = 0;
   //if (Screen < 0) Screen= 1;
   lastButtonPressL = millis();
 }
 lastButtonStateL = PBLstate;


 if (!PBRstate && lastButtonStateR && (millis() - lastButtonPressR) > debounceDelay) {
   Screen = 1;
  // if (Screen > 1) Screen = 0;
   lastButtonPressR = millis();
 }
 lastButtonStateR = PBRstate;


   if (!PBUstate && lastButtonStateU && (millis() - lastButtonPressU) > debounceDelay) {
   if (Screen == 0) {
     setPoint+=50;
   } else if (Screen == 1) {
     pGain+=0.1;
   }
   lastButtonPressU = millis();
 }
 lastButtonStateU = PBUstate;


 if (!PBDstate && lastButtonStateD && (millis() - lastButtonPressD) > debounceDelay) {
   if (Screen == 0) {
     setPoint-=50;
   } else if (Screen == 1) {
     pGain-=0.1;
   }
   lastButtonPressD = millis();
 }
 lastButtonStateD = PBDstate;


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

