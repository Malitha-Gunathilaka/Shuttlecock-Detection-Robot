#include <AFMotor.h>
#include <Servo.h>

// Motor and Servo Setup
AF_DCMotor motor1(1); // Motor 1
AF_DCMotor motor2(2); // Motor 2
AF_DCMotor motor3(3); // Motor 3
AF_DCMotor motor4(4); // Motor 4
Servo scanServo;

// Sensor Pins
#define TRIG_PIN 9
#define ECHO_PIN 10
#define IR_PIN 11

// Movement Functions
void moveForward() {
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveBackward() {
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void turnLeft() {
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void turnRight() {
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void stopMotors() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

// Sensor Function
long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

void setup() {
  Serial.begin(9600);

  // Motor Pins Setup
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_PIN, INPUT);

  // Servo Setup
  scanServo.attach(3); // Attach servo to pin 3
  scanServo.write(90); // Center position

  // Initial state
  stopMotors();
}

void loop() {
  // Get sensor readings
  long distance = getDistance();
  bool isIRDetected = digitalRead(IR_PIN);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, IR: ");
  Serial.println(isIRDetected);

  if (distance > 5 && distance < 20 && isIRDetected) {
    Serial.println("Shuttlecock Detected!");
    stopMotors();

    // Scoop mechanism (simulate or add actual servo movement)
    scanServo.write(45); // Lower scoop
    delay(1000);         // Wait for scoop
    scanServo.write(90); // Reset scoop position

    // Backward movement after collecting
    moveBackward();
    delay(1000);
    stopMotors();
    delay(2000); // Pause before resuming patrol
  } else {
    // Patrol area
    moveForward();
    delay(500);
    turnLeft();
    delay(300);
  }
}
