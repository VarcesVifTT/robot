/*
 */

int pinMotorTopspin = 9;    // PWM on PB 1
int pinMotorBackspin = 10;  // PWM on PB 2

int pinPotSpeed = 1;        // PC 1
int pinPotRatio = 0;        // PC 0

int pinGreenLed= 17;        // PC 3
int pinRedLed = 19;         // PC 5
int pinOrangeLed = 18;      // PC 4


int potSpeedValue = 0;
int potRatioValue = 0;
int n = 0;



// the setup routine runs once when you press reset:
void setup() {
  pinMode(pinMotorTopspin, OUTPUT);
  pinMode(pinMotorBackspin, OUTPUT);
  pinMode(pinGreenLed, OUTPUT);
  pinMode(pinRedLed, OUTPUT);
  pinMode(pinOrangeLed, OUTPUT);
 

  digitalWrite(pinRedLed, HIGH);
  delay(200);
  digitalWrite(pinRedLed, LOW);
  digitalWrite(pinOrangeLed, HIGH);
  delay(200);
  digitalWrite(pinOrangeLed, LOW);
  digitalWrite(pinGreenLed, HIGH);
  delay(200);
  digitalWrite(pinGreenLed, LOW);
  analogWrite(pinMotorTopspin, 0);
  analogWrite(pinMotorBackspin, 0);
  
  digitalWrite(pinRedLed, HIGH);
  digitalWrite(pinOrangeLed, HIGH);
  digitalWrite(pinGreenLed, HIGH);
  delay(5000);
  digitalWrite(pinRedLed, LOW);
  digitalWrite(pinOrangeLed, LOW);
  digitalWrite(pinGreenLed, LOW);
}


// the loop routine runs over and over again forever:
void loop() {
  // analog values are [0, 1023] while PWM outputs are [0, 255] 
  potSpeedValue = analogRead(pinPotSpeed) / 4;
  potRatioValue = analogRead(pinPotRatio) / 4;

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

  potRatioValue -= 127;

  potSpeedValue -= potRatioValue;
  if (potSpeedValue < 0)
    potSpeedValue = 0;
  if (potSpeedValue > 255)
    potSpeedValue = 255;
  analogWrite(pinMotorTopspin, potSpeedValue);

  potSpeedValue += potRatioValue;
  if (potSpeedValue < 0)
    potSpeedValue = 0;
  if (potSpeedValue > 255)
    potSpeedValue = 255;
  analogWrite(pinMotorBackspin, potSpeedValue);
      
//  delay(200);
}

