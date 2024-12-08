#include <AFMotor.h>      // For motor control
#include <NewPing.h>      // For ultrasonic sensor
#include <Wire.h>         // For gyroscope
#include <MPU6050.h>      // Gyroscope library

// Motor definitions
AF_DCMotor motor1(1); // Front-left motor
AF_DCMotor motor2(2); // Front-right motor
AF_DCMotor motor3(3); // Back-left motor
AF_DCMotor motor4(4); // Back-right motor

// Ultrasonic sensor definitions
#define TRIG_PIN 7
#define ECHO_PIN 6
#define MAX_DISTANCE 200
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// Gyroscope definitions
MPU6050 gyro;

// Court and robot dimensions (in cm)
float courtLength = 1340.0; // Court length (13.4 m)
float courtWidth = 610.0;   // Court width (6.1 m)
float robotWidth = 30.0;    // Robot width (30 cm)
float speedCmPerSecond = 10.0; // Approximate forward speed (adjust as needed)
float turnSpeedDegreesPerSecond = 90.0; // Approximate turn speed (adjust as needed)

void setup() {
  Serial.begin(9600);
  initializeMotors();
  setupGyro();
}

void loop() {
  while (courtLength > robotWidth && courtWidth > robotWidth) {
    // Clean one boundary lap
    cleanBoundary(courtLength, courtWidth);

    // Move inward
    moveInward(robotWidth);

    // Reduce the court dimensions
    courtLength -= 2 * robotWidth;
    courtWidth -= 2 * robotWidth;
  }

  stopMotors(); // Stop motors when done
}

void initializeMotors() {
  motor1.setSpeed(200); // Adjust speeds (0-255) as needed
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);
}

void setupGyro() {
  Wire.begin();
  gyro.initialize();
  if (!gyro.testConnection()) {
    Serial.println("Gyro connection failed!");
  }
}

float getAngle() {
  int16_t ax, ay, az, gx, gy, gz;
  gyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  return gx / 131.0; // Convert raw gyro value to angle
}

float getDistance() {
  return sonar.ping_cm(); // Return distance from ultrasonic sensor in cm
}

void cleanBoundary(float length, float width) {
  // Clean along the longer edge
  driveMotorsForward(length);
  turnRight();

  // Clean along the shorter edge
  driveMotorsForward(width);
  turnRight();

  // Clean along the other longer edge
  driveMotorsForward(length);
  turnRight();

  // Clean along the other shorter edge
  driveMotorsForward(width);
  turnRight();
}

void moveInward(float step) {
  driveMotorsForward(step);
}

void driveMotorsForward(float distanceCm) {
  float timeToRun = distanceCm / speedCmPerSecond; // Calculate run time
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(timeToRun * 1000); // Run motors for the calculated time
  haltMotors();
}

void rotateMotors(float angle) {
  float timeToTurn = angle / turnSpeedDegreesPerSecond; // Calculate turn time
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
  delay(timeToTurn * 1000); // Rotate motors for the calculated time
  haltMotors();
}

void turnRight() {
  rotateMotors(90); // Turn 90° right
}

void turnLeft() {
  rotateMotors(-90); // Turn 90° left
}

void haltMotors() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
