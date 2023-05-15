#include <LiquidCrystal.h> 
int sensor = A5;
int actuator = 6;
int PV =0;
int setPoint = 0;
int CO = 0;
int Error = 0;
float pGain = 0.01;
float iGain = 0.01;
int integralAction;
unsigned long previousMillis = 0; 
const long interval = 100;
unsigned long currentMillis; 
// Pushbuttons
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
  lcd.begin(16, 2);
pinMode(actuator, OUTPUT);
Serial.begin(9600);
 pinMode(buttonPin1, INPUT_PULLUP);
 pinMode(buttonPin2, INPUT_PULLUP);
 pinMode(buttonPin3, INPUT_PULLUP);
 pinMode(buttonPin4, INPUT_PULLUP);
}

void loop() {
   // Debounce and button actions
 buttonState1 = digitalRead(buttonPin1);
 buttonState2 = digitalRead(buttonPin2);
 buttonState3 = digitalRead(buttonPin3);
 buttonState4 = digitalRead(buttonPin4);

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
   } else if (currentPage == 2) {
     pGain += 0.1;
   }
   else if (currentPage == 3) {
     iGain += 0.1;
   }
   lastButtonPress3 = millis();
 }
 lastButtonState3 = buttonState3;


 if (!buttonState4 && lastButtonState4 && (millis() - lastButtonPress4) > debounceDelay) {
   if (currentPage == 0) {
     setPoint -= 20 ;
   } else if (currentPage == 2) {
     pGain -= 0.1;
   }
   else if (currentPage == 3) {
     iGain -= 0.1;
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
 
 
 
  // put your main code here, to run repeatedly:
PV = analogRead(sensor);
currentMillis = millis();

if (currentMillis - previousMillis >= interval){
  previousMillis = currentMillis;
  Error = setPoint-PV;
  integralAction = (integralAction + Error);
  CO = ((pGain *Error)+(iGain*integralAction)/20);

  if (CO > 255) {
  CO = 255; // If CO is greater than 255, set it to 255
} if (CO < 0) {
  CO = 0; // If CO is less than 0, set it to 0
}
analogWrite(actuator, CO);
  
  Serial.print("SP = ");
  Serial.print(setPoint);
  Serial.print("\t CO = ");
  Serial.print(CO);
  Serial.print("\t PV = ");
  Serial.print(PV);
  //Serial.print("\t P Gain = ");
  //Serial.print(pGain);
 // Serial.print("\t I Gain = ");
  //Serial.print(iGain);
  Serial.print("\t Error :");
Serial.print(Error);
Serial.println();
}
}
