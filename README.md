# Shuttlecock Collecting Rover

## Overview
The **Shuttlecock Collecting Rover** is an autonomous robot designed to patrol a badminton court, detect shuttlecocks using sensors, and collect them using a servo-operated scoop mechanism. It demonstrates robotics concepts, sensor integration, and autonomous navigation using an Arduino-based platform.

---

## Features
- **Autonomous Navigation**: Patrols an area and adjusts movement based on sensor inputs.
- **Shuttlecock Detection**:
  - Ultrasonic sensor for distance measurement.
  - IR sensor for object confirmation.
- **Scoop Mechanism**: Collects shuttlecocks using a servo motor.
- **4x4 Chassis**: Controlled by an L293D motor driver.

---

## Components
### Hardware
- **Arduino Uno/Mega 2560**
- **L293D Motor Shield**
- **4x4 Rover Chassis with DC Motors**
- **HC-SR04 Ultrasonic Sensor**
- **IR Sensor**
- **Servo Motor** (for scoop mechanism)
- **External Power Source** (for motors)
- **Wires and Connectors**

### Software
- Arduino IDE
- AFMotor Library (for motor control)
- Servo Library (for servo control)

---


## How It Works
1. **Patrolling**: The rover moves in a predefined pattern (e.g., forward for 1m, then turns).
2. **Detection**:
   - The ultrasonic sensor measures distance.
   - If an object is detected within a specific range, the IR sensor confirms if it is a shuttlecock.
3. **Collection**:
   - The rover stops, activates the scoop mechanism, and collects the shuttlecock.
   - Resumes patrolling after collection.

---

## Code
### Main Functionality
The Arduino code enables:
- Sensor-based navigation and object detection.
- Autonomous movement using the L293D motor shield.
- Shuttlecock collection with a servo-operated mechanism.

You can find the full code in the `src` directory:
- [`shuttlecock_collecting_rover.ino`](src/Shuttlecock Collecting Rover.ino)

---

## Getting Started
### Hardware Setup
1. **Assemble the Chassis**: Attach the motors to the rover chassis and connect them to the L293D motor shield.
2. **Connect Sensors**:
   - Ultrasonic sensor to Arduino pins: `TRIG_PIN = 9`, `ECHO_PIN = 10`.
   - IR sensor to Arduino pin: `IR_PIN = 7`.
3. **Attach Scoop Mechanism**:
   - Mount a servo motor and connect it to Arduino pin: `SERVO_PIN = 3`.

### Software Setup
1. Install the Arduino IDE.
2. Install required libraries:
   - [AFMotor](https://github.com/adafruit/Adafruit-Motor-Shield-library)
   - Servo (pre-installed with Arduino IDE)
3. Upload the code to your Arduino board.

---

## Usage
1. Power on the rover.
2. It will start patrolling the area automatically.
3. Upon detecting a shuttlecock, the rover will stop, collect it, and resume patrolling.

---


## Future Improvements
- Add a camera for better object detection.
- Implement a more advanced navigation algorithm (e.g., GPS-based or line-following).
- Integrate wireless control for manual operation.

---

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Author
- **Malitha Gunathilaka**  
  - [GitHub](https://github.com/Malitha-Gunathilaka)  
  - [LinkedIn](https://linkedin.com/in/malithavisada)

---

