#include <Arduino.h>
#include <Receiver.h>

// MOTOR LEFT PINS
const int ENA = 2;
const int IN1 = 3;
const int IN2 = 4;
// MOTOR RIGHT PINS
const int ENB = 5;
const int IN3 = 6;
const int IN4 = 7;

const int MINIMUM_MOTOR_SPEED = 65;
const int minThrottle = -50;
const int maxThrottle = 50;
const int leftSteering = -50;
const int rightSteering = 50;

bool carControlDebug = false;

// Configures the motor controller to stop the motors.
void motorBrake()
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  // Do not write the motor speeds on this function. It simply configures the motor controller.
}

// Configures the motor controller to have the robot move forward.
void motorSetForward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // Do not write the motor speeds on this function. It simply configures the motor controller.
}

// Configures the motor controller to have the robot move backwards.
void motorSetBackward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  // Do not write the motor speeds on this function. It simply configures the motor controller.
}

void setPins()
{
  // Set pins as input or output
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void controlDrive()
{
  // THROTTLE AND STEERING CONTROL
  // throttle values after subtracting 49:
  //     50 = max forward throttle
  //     0 = no throttole
  //     -50 = max reverse throttle
  // steering values after subtracting 49:
  //     50 = max right
  //     0 = straight
  //     -50 = max left

  int throttle = map(yAxis, minAxis, maxAxis, minThrottle, maxThrottle);
  int steering = map(xAxis, minAxis, maxAxis, leftSteering, rightSteering);

  throttle = (throttle >= -2 && throttle <= 2) ? 0 : throttle;
  steering = (steering >= -2 && steering <= 2) ? 0 : steering;

  if (carControlDebug)
  {
    Serial.print("throttle: ");
    Serial.print(throttle);
    Serial.print("\tsteering: ");
    Serial.println(steering);
  }

  if (throttle == 0)
  {
    // If throttle is zero, don't move.
    motorBrake();
    return;
  }

  // Determine forwards or backwards.
  if (throttle > 0)
  {
    // Forward
    motorSetForward();
  }
  else
  {
    // Backward
    motorSetBackward();
  }

  // Map throttle to PWM range.
  int mappedSpeed = map(abs(throttle), 0, 50, MINIMUM_MOTOR_SPEED, 255);
  // Map steering to PWM range.
  int reducedSpeed = map(abs(steering), 0, 50, mappedSpeed, MINIMUM_MOTOR_SPEED);

  int leftMotorSpeed, rightMotorSpeed;
  if (steering > 0)
  {
    // Turn Right: reduce right motor speed
    leftMotorSpeed = mappedSpeed;
    rightMotorSpeed = reducedSpeed;
  }
  else
  {
    // Turn Left: reduce left motor speed
    leftMotorSpeed = reducedSpeed;
    rightMotorSpeed = mappedSpeed;
  }

  // Set motor speeds
  analogWrite(ENA, leftMotorSpeed);
  analogWrite(ENB, rightMotorSpeed);

  if (carControlDebug)
  {
    Serial.print("mappedSpeed: ");
    Serial.print(mappedSpeed);
    Serial.print("\treducedSpeed: ");
    Serial.print(reducedSpeed);
    Serial.print("\tleftMotorSpeed: ");
    Serial.print(leftMotorSpeed);
    Serial.print("\trightMotorSpeed: ");
    Serial.println(rightMotorSpeed);
  }
}

void setupCarControl()
{
  receiverDebug = carControlDebug;
  setPins();
  setupReceiver();
}

void loopCarControl()
{
  loopReceiver();
  controlDrive();
}