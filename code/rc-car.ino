#include<SoftwareSerial.h>
#include<Servo.h>
#include<LiquidCrystal.h>
#include<Wire.h>

char str[2], i;               // Data from bluetooth
int IR_SENSOR = 0;            // IR sensor connected to the analog A0
int SensorResult = 0;         // Sensor result
float fltSensorCalc = 0;      // Calculated value
int motorA1 = 2;              // PIN 2 for controlling motor A1
int motorA2 = 3;              // PIN 3 for controlling motor A2
int motorB1 = 4;              // PIN 4 for controlling motor B1
int motorB2 = 5;              // PIN 4 for controlling motor B1
const int irsensor = A0;      // PIN A0 to receive data from sensor
const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2;       // lcd pins connected to Arduino
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);            // lcd function from LiquidCrystal
SoftwareSerial mySerial(0, 1);
Servo myservo;

void setup() 
{
  // Setup the communication
  Serial.begin(9600);
  myservo.attach(12);
  
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(irsensor, INPUT);
  
  // Initialize LCD
  lcd.clear();
  lcd.begin (16,2);
}

void loop()
{
  // Read the value from the IR laser sensor
  int SensorResult = analogRead(IR_SENSOR);
  
  // Calculate distance in cm
  fltSensorCalc = (6787.0 / (SensorResult - 3.0)) - 4.0;

  // Print distance
  lcd.setCursor(0,0);
  lcd.print("Distance: ");
  lcd.setCursor(4,1);
  lcd.print(fltSensorCalc);
  lcd.print(" cm");
  delay(100);

  while(Serial.available())
  {
    char ch = Serial.read();
    str[i++] = ch;
    if(str[i-1] == '1'){
      forward();
      i = 0;
    }
    else if(str[i-1] == '2'){
      right();
      i = 0;
    }
    else if(str[i-1] == '3'){
      left();
      i = 0;
    }
    else if(str[i-1] == '4'){
      reverse();
      i = 0;
    }
    else if(str[i-1] == '5'){
      Stop();
      i = 0;
    }
  }
}

void forward(){
  digitalWrite(motorA1,HIGH);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, HIGH);
}

void reverse(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void left(){
  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void right(){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void Stop(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
