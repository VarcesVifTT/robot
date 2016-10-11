/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 The analogWrite() function uses PWM, so if
 you want to change the pin you're using, be
 sure to use another PWM capable pin. On most
 Arduino, the PWM pins are identified with 
 a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

 This example code is in the public domain.
 */

#include "LiquidCrystal.h"  

int pinMotorTopspin = 10;           // PWM on PB 2
int pinMotorBackspin = 9;           // PWM on PB 1
int pinMotorDistribution = 11;      // PWM on PB 3

int pinPotSpeed = 1;                // PC 1
int pinPotRatio = 0;                // PC 0

int pinGreenLed= 17;                // PC 3
int pinRedLed = 19;                 // PC 5
int pinOrangeLed = 18;              // PC 4

int pinButtonFaster = 12;           // PB 4
int pinButtonSlower = 13;           // PB 5


int potSpeedValue = 0;
int potRatioValue = 0;
int top = 0;
int back = 0;

int speedDistributionValue = 130;
int state;

int mode = 0;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


// the setup routine runs once when you press reset:
void setup() {
  lcd.begin(16, 2);
  delay(1000);
  lcd.print("tcho !");
  
  pinMode(pinMotorTopspin, OUTPUT);
  pinMode(pinMotorBackspin, OUTPUT);
  pinMode(pinMotorDistribution, OUTPUT);
  
// stop motors  
  analogWrite(pinMotorDistribution, 255);   
  analogWrite(pinMotorTopspin, 255);
  analogWrite(pinMotorBackspin, 255);

  pinMode(pinGreenLed, OUTPUT);
  pinMode(pinRedLed, OUTPUT);
  pinMode(pinOrangeLed, OUTPUT);

  pinMode(pinButtonFaster, INPUT_PULLUP);
  pinMode(pinButtonSlower, INPUT_PULLUP);
 
  digitalWrite(pinRedLed, HIGH);
  delay(500);
  digitalWrite(pinRedLed, LOW);
  digitalWrite(pinOrangeLed, HIGH);
  delay(500);
  digitalWrite(pinOrangeLed, LOW);
  digitalWrite(pinGreenLed, HIGH);
  delay(500);
  digitalWrite(pinGreenLed, LOW);
  
  digitalWrite(pinRedLed, HIGH);
  digitalWrite(pinOrangeLed, HIGH);
  digitalWrite(pinGreenLed, HIGH);
  delay(5000);
  digitalWrite(pinRedLed, LOW);
  digitalWrite(pinOrangeLed, LOW);
  digitalWrite(pinGreenLed, LOW);

  
  if (digitalRead(pinButtonFaster) == LOW || digitalRead(pinButtonSlower) == LOW) 
    mode = 1;
    
  delay(5000);
  analogWrite(pinMotorDistribution, speedDistributionValue);   
//  analogWrite(pinMotorTopspin, 0);
//  analogWrite(pinMotorBackspin, 0);
}


// the loop routine runs over and over again forever:
void loop() {
  state = digitalRead(pinButtonFaster);
  if (state == LOW) {
    speedDistributionValue -= 5;
    if (speedDistributionValue < 0)
      speedDistributionValue = 0;
    analogWrite(pinMotorDistribution, speedDistributionValue);
  }

  state = digitalRead(pinButtonSlower);
  if (state == LOW) {
    speedDistributionValue += 5;
    if (speedDistributionValue > 255)
      speedDistributionValue = 255;
    analogWrite(pinMotorDistribution, speedDistributionValue);
  }
  
  // analog values are [0, 1023] while PWM outputs are [0, 255] 
  potSpeedValue = 255 - analogRead(pinPotSpeed) / 4;              // reverse fader direction
  potRatioValue = analogRead(pinPotRatio) / 4;

  if (mode == 0)
    digitalWrite(pinGreenLed, HIGH);
  else
    digitalWrite(pinRedLed, HIGH);
/*
  if (potSpeedValue < 50)
    digitalWrite(pinRedLed, HIGH);
  else
    digitalWrite(pinRedLed, LOW);

  if (potSpeedValue > 200)
    digitalWrite(pinOrangeLed, HIGH);
  else
    digitalWrite(pinOrangeLed, LOW);

  if (potRatioValue > 120 && potRatioValue < 134)
    digitalWrite(pinGreenLed, HIGH);
  else
    digitalWrite(pinGreenLed, LOW);
*/    

  digitalWrite(pinOrangeLed, LOW);
  if (mode == 0) {
    top = potSpeedValue - potRatioValue;
    back = potSpeedValue;

    if (top < 0) {
      top = 0;
      digitalWrite(pinOrangeLed, HIGH);
    }
  } else {
    back = potSpeedValue - potRatioValue;
    top = potSpeedValue;

    if (back < 0) {
      back = 0;
      digitalWrite(pinOrangeLed, HIGH);
    }
  }
    
  analogWrite(pinMotorTopspin, top);
  analogWrite(pinMotorBackspin, back);


//  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print(speedDistributionValue);
  lcd.setCursor(3, 0);
  if (mode == 0)
    lcd.print(" S R TOP back");
  else 
    lcd.print(" S R top BACK");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(potSpeedValue);
  lcd.setCursor(4, 1);
  lcd.print(potRatioValue);
  lcd.setCursor(8, 1);
  lcd.print(top);
  lcd.setCursor(12, 1);
  lcd.print(back);
//  delay(200);
}

