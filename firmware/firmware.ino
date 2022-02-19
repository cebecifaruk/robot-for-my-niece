#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

// Pin Definitions


#define LEFT_ECHO       4
#define LEFT_TRIG       2
#define RIGHT_ECHO     A1
#define RIGHT_TRIG     A0
#define CENTER_TRIG      7
#define CENTER_ECHO      8


#define LCD_D7 A2
#define LCD_D6 A3
#define LCD_D5 A4
#define LCD_D4 A5
#define LCD_RS A6
#define LCD_EN A7

#define BUZZER 13

#define MOTOR_LEFT_FORWARD 5
#define MOTOR_LEFT_BACKWARD 3
#define MOTOR_RIGHT_FORWARD 6
#define MOTOR_RIGHT_BACKWARD 9

#define ESP_TX 10
#define ESP_RX 11

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);



void setup() {
  Serial.begin(9600);
  
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  
  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);
  pinMode(CENTER_TRIG, OUTPUT);
  pinMode(CENTER_ECHO, INPUT);
  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);
  
  pinMode(BUZZER, OUTPUT);
  
  playMelody(BUZZER);
}

void loop() {
  delay(25);
  int speedLeft = measureRightDist() > 50 ? 150 : -50;
  int speedRight = measureLeftDist() > 50 ? 150 : -50;
  
  if(measureCenterDist() < 10) {
    speedLeft = -150;
    speedRight = -40;
  }

  if(speedLeft > 0) {
    analogWrite(MOTOR_LEFT_FORWARD, speedLeft);
    analogWrite(MOTOR_LEFT_BACKWARD, 0);
  } else {    
    analogWrite(MOTOR_LEFT_FORWARD, 0);
    analogWrite(MOTOR_LEFT_BACKWARD, -1 * speedLeft);
  }
  if(speedRight > 0) {
    analogWrite(MOTOR_RIGHT_FORWARD, speedRight);
    analogWrite(MOTOR_RIGHT_BACKWARD, 0);
  } else {    
    analogWrite(MOTOR_RIGHT_FORWARD, 0);
    analogWrite(MOTOR_RIGHT_BACKWARD, -1 * speedRight);
  }
}



int measureLeftDist() {
  digitalWrite(LEFT_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(LEFT_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(LEFT_TRIG, LOW);
  long duration = pulseIn(LEFT_ECHO, HIGH, 100000);
  int distance = duration * 0.034 / 2;
  if(duration == 0) return 5000;
  return distance;
}


int measureRightDist() {
  digitalWrite(RIGHT_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(RIGHT_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(RIGHT_TRIG, LOW);
  long duration = pulseIn(RIGHT_ECHO, HIGH, 100000);
  int distance = duration * 0.034 / 2;
  if(duration == 0) return 5000;
  return distance;
}

int measureCenterDist() {
  digitalWrite(CENTER_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(CENTER_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(CENTER_TRIG, LOW);
  long duration = pulseIn(CENTER_ECHO, HIGH, 100000);
  int distance = duration * 0.034 / 2;
  if(duration == 0) return 5000;
  return distance;
}
