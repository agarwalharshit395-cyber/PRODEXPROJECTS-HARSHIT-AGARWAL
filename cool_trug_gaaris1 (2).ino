
#include <Servo.h>

// Servo motors
Servo horizontalServo;
Servo verticalServo;

// LDR pins
const int topLeft = A0;
const int topRight = A1;
const int bottomLeft = A2;
const int bottomRight = A3;

// Servo pins
const int horizontalPin = 9;
const int verticalPin = 10;

// Initial servo positions
int horizontalAngle = 90;
int verticalAngle = 90;

// Tracking parameters
const int tolerance = 40;
const int stepSize = 1;

// Servo safety limits
const int minAngle = 10;
const int maxAngle = 170;

void setup() {
  Serial.begin(9600);

  horizontalServo.attach(horizontalPin);
  verticalServo.attach(verticalPin);

  horizontalServo.write(horizontalAngle);
  verticalServo.write(verticalAngle);

  Serial.println("DUAL AXIS SOLAR TRACKER");
  Serial.println("System Initialized");
}

void loop() {

  // Read four LDR sensors
  int TL = analogRead(topLeft);
  int TR = analogRead(topRight);
  int BL = analogRead(bottomLeft);
  int BR = analogRead(bottomRight);

  // Calculate average light intensity
  int topAverage = (TL + TR) / 2;
  int bottomAverage = (BL + BR) / 2;

  int leftAverage = (TL + BL) / 2;
  int rightAverage = (TR + BR) / 2;

  // Calculate differences
  int verticalDifference =
      topAverage - bottomAverage;

  int horizontalDifference =
      leftAverage - rightAverage;

  // Horizontal tracking
  if (abs(horizontalDifference) > tolerance) {

    if (horizontalDifference > 0) {
      horizontalAngle++;
    }
    else {
      horizontalAngle--;
    }
  }

  // Vertical tracking
  if (abs(verticalDifference) > tolerance) {

    if (verticalDifference > 0) {
      verticalAngle++;
    }
    else {
      verticalAngle--;
    }
  }

  // Limit servo movement
  horizontalAngle =
      constrain(horizontalAngle, minAngle, maxAngle);

  verticalAngle =
      constrain(verticalAngle, minAngle, maxAngle);

  // Move motors
  horizontalServo.write(horizontalAngle);
  verticalServo.write(verticalAngle);

  // Display sensor readings
  Serial.print("TL: ");
  Serial.print(TL);

  Serial.print(" TR: ");
  Serial.print(TR);

  Serial.print(" BL: ");
  Serial.print(BL);

  Serial.print(" BR: ");
  Serial.println(BR);

  Serial.print("Horizontal Angle: ");
  Serial.print(horizontalAngle);

  Serial.print(" | Vertical Angle: ");
  Serial.println(verticalAngle);

  Serial.println("----------------------");

  delay(100);
}
