#include <LiquidCrystal.h>  //include the LiquidCrystal library for LCD control


int sensor = A5;
int actuator = 6;
int PV = 0;
int setPoint = 0;
int CO = 0;
int HYS = 30;
int ST = 0;


// Pushbuttons
const int buttonPin1 = 10;
const int buttonPin2 = 9;
const int buttonPin3 = 8;
const int buttonPin4 = 7;


// Button states and debounce variables
bool buttonState1, lastButtonState1, buttonState2, lastButtonState2, buttonState3, lastButtonState3, buttonState4, lastButtonState4 = false;
unsigned long lastButtonPress1, lastButtonPress2, lastButtonPress3, lastButtonPress4 = 0;
const unsigned long debounceDelay = 50;


// LCD page variable
int currentPage = 0;


// LCD pin connections
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
 lcd.begin(16, 2);
 pinMode(actuator, OUTPUT);
 pinMode(buttonPin1, INPUT_PULLUP);
 pinMode(buttonPin2, INPUT_PULLUP);
 pinMode(buttonPin3, INPUT_PULLUP);
 pinMode(buttonPin4, INPUT_PULLUP);
 Serial.begin(9600);
}


void loop() {



 // Debounce and button actions
 buttonState1 = digitalRead(buttonPin1);
 buttonState2 = digitalRead(buttonPin2);
 buttonState3 = digitalRead(buttonPin3);
 buttonState4 = digitalRead(buttonPin4);


Serial.print(" \t SP = ");
Serial.print(setPoint);
Serial.print(" \t CO = ");
Serial.println (CO);
Serial.print("\t PV = ");
Serial.print(PV);
// Serial.print("\tHYS = ");
// Serial.print(HYS);
// Serial.print("\tPage = ");
// Serial.println(currentPage);


 if (!buttonState1 && lastButtonState1 && (millis() - lastButtonPress1) > debounceDelay) {
   currentPage--;
   if (currentPage < 0) currentPage = 3;
   lastButtonPress1 = millis();
 }
 lastButtonState1 = buttonState1;


 if (!buttonState2 && lastButtonState2 && (millis() - lastButtonPress2) > debounceDelay) {
   currentPage++;
   if (currentPage > 3) currentPage = 0;
   lastButtonPress2 = millis();
 }
 lastButtonState2 = buttonState2;


   if (!buttonState3 && lastButtonState3 && (millis() - lastButtonPress3) > debounceDelay) {
   if (currentPage == 0) {
     setPoint += 30;
   } else if (currentPage == 3) {
     HYS += 30;
   }
   lastButtonPress3 = millis();
 }
 lastButtonState3 = buttonState3;


 if (!buttonState4 && lastButtonState4 && (millis() - lastButtonPress4) > debounceDelay) {
   if (currentPage == 0) {
     setPoint -= 20 ;
   } else if (currentPage == 3) {
     HYS -= 20;
   }
   lastButtonPress4 = millis();
 }
 lastButtonState4 = buttonState4;


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
     lcd.print("PV:");
     lcd.print(PV);
     break;
   case 2:
      lcd.setCursor(0, 0);
     lcd.print("CO:");
     lcd.print(CO); 
     break;
    case 3:  
     lcd.setCursor(0, 0);
     lcd.print("HYS:");
     lcd.print(HYS);
     break;

 }
 delay(10);

  PV = analogRead(sensor);
if (PV <= (setPoint - HYS )) {
   CO = 255;
 } else if (PV >= (setPoint+ HYS )) {
   CO = 0;
 }
 analogWrite(actuator, CO);
}


