#include <Servo.h>

// --------------------------------------------------
// Motor pins
// --------------------------------------------------

// Right motor
const int rightForwardPin = 7;
const int rightBackwardPin = 8;
const int rightSpeedPin = 9;

// Left motor
const int leftForwardPin = 11;
const int leftBackwardPin = 12;
const int leftSpeedPin = 10;

// --------------------------------------------------
// IR receiver and catapult servo
// --------------------------------------------------

const int irReceiverPin = A5;
const int servoPin = 5;

// Approximately 1.5 V with a 5 V ADC reference
const int irThreshold = 307;

const int spinSpeed = 150;

const int servoResetAngle = 0;
const int servoFireAngle = 45;

Servo catapultServo;

// --------------------------------------------------
// Robot states
// --------------------------------------------------

enum RobotState {
  IDLE,
  SENTRY_ROTATION,
  AIMING,
  FIRING
};

RobotState robotState = IDLE;

// Used to detect a new IR command rather than
// repeatedly responding to a continuously held signal.
bool previousIrDetected = false;


// --------------------------------------------------
// Setup
// --------------------------------------------------

void setup() {
  Serial.begin(9600);

  pinMode(rightForwardPin, OUTPUT);
  pinMode(rightBackwardPin, OUTPUT);
  pinMode(rightSpeedPin, OUTPUT);

  pinMode(leftForwardPin, OUTPUT);
  pinMode(leftBackwardPin, OUTPUT);
  pinMode(leftSpeedPin, OUTPUT);

  // Set the desired position before attaching the servo
  // to reduce unintended movement during startup.
  catapultServo.write(servoResetAngle);
  catapultServo.attach(servoPin);

  stopMotors();

  Serial.println("Catapult robot initialized.");
}


// --------------------------------------------------
// Main loop
// --------------------------------------------------

void loop() {
  int irValue = analogRead(irReceiverPin);

  bool irDetected = (irValue > irThreshold);

  // Rising-edge detection:
  // true only when the IR signal changes from
  // not detected to detected.
  bool newIrCommand = irDetected && !previousIrDetected;

  previousIrDetected = irDetected;

  switch (robotState) {

    // ------------------------------------------------
    // IDLE
    // ------------------------------------------------
    case IDLE:
      stopMotors();

      if (newIrCommand) {
        robotState = SENTRY_ROTATION;
        Serial.println("State: SENTRY_ROTATION");
      }

      break;


    // ------------------------------------------------
    // SENTRY / ROTATION
    // ------------------------------------------------
    case SENTRY_ROTATION:
      rotateClockwise();

      if (newIrCommand) {
        stopMotors();
        robotState = AIMING;
        Serial.println("State: AIMING");
      }

      break;


    // ------------------------------------------------
    // AIMING
    // ------------------------------------------------
    case AIMING:
      stopMotors();

      if (newIrCommand) {
        robotState = FIRING;
        Serial.println("State: FIRING");
      }

      break;


    // ------------------------------------------------
    // FIRE / RESET
    // ------------------------------------------------
    case FIRING:
      stopMotors();

      // Release the catapult.
      catapultServo.write(servoFireAngle);

      // A second IR command resets the catapult
      // and returns the robot to its idle state.
      if (newIrCommand) {
        catapultServo.write(servoResetAngle);
        robotState = IDLE;
        Serial.println("State: IDLE");
      }

      break;
  }
}


// --------------------------------------------------
// Motor-control functions
// --------------------------------------------------

void rotateClockwise() {
  // Left motor forward
  digitalWrite(leftForwardPin, HIGH);
  digitalWrite(leftBackwardPin, LOW);
  analogWrite(leftSpeedPin, spinSpeed);

  // Right motor backward
  digitalWrite(rightForwardPin, LOW);
  digitalWrite(rightBackwardPin, HIGH);
  analogWrite(rightSpeedPin, spinSpeed);
}


void stopMotors() {
  digitalWrite(rightForwardPin, LOW);
  digitalWrite(rightBackwardPin, LOW);
  analogWrite(rightSpeedPin, 0);

  digitalWrite(leftForwardPin, LOW);
  digitalWrite(leftBackwardPin, LOW);
  analogWrite(leftSpeedPin, 0);
}
