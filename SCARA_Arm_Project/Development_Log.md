# SCARA Arm - Development Log

This document records the step-by-step development process, challenges, and key code snippets for the SCARA Arm project.

---

## 2025年8月2日: Milestone 1 - First Motor Movement Success!

### **Objective:**
To verify the basic hardware chain by driving a single NEMA 17 stepper motor using the Arduino Uno, CNC Shield V3, and a TMC2209 driver.

### **Process & Challenges:**

1.  **Initial Setup:** Connected the TMC2209 driver and a NEMA 17 motor to the X-axis port on the CNC Shield.
2.  **Initial Failure:** The motor did not respond, despite the Arduino code running correctly (confirmed via Serial Monitor output).
3.  **Troubleshooting:**
    *   Verified the 12V motor power supply and 5V logic power supply to the TMC2209 driver pins (`VM` & `VIO`) using a multimeter. Both were correct.
    *   Swapped the TMC2209 driver and the stepper motor with spares, but the issue persisted. This ruled out individual component failure.
    *   Moved the setup to the Y-axis and Z-axis ports, but the motor still did not move. This suggested a global issue rather than a single faulty axis channel.
4.  **Breakthrough:** After consulting the documentation for the specific CNC Shield, we identified the root cause: **The global Enable Pin (D8) was not being activated in the code.**

### **Key Finding:**

The CNC Shield V3 requires **Arduino Pin D8** to be pulled **LOW** to enable all stepper motor drivers. Without this, the drivers remain in a disabled state and will not respond to STEP pulses.

### **Final Working Code for X-Axis Test:**

This code successfully drives the X-axis motor and serves as the definitive hardware verification script for our setup.

```cpp
#include <Arduino.h>
#include "BasicStepperDriver.h"

// CNC Shield v3 Pin Definitions
#define ENABLE_PIN 8 // CRITICAL! This is the master switch for all drivers.

#define DIR_PIN    5 // X-Axis Direction Pin
#define STEP_PIN   2 // X-Axis Step Pin

// Motor Parameters
#define MOTOR_STEPS 200 // Steps per revolution for NEMA 17
#define RPM 60          // A stable, low RPM for testing
#define MICROSTEPS 8    // Default microstepping for TMC2209 with no jumpers

// Create a driver instance
BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN);

void setup() {
    Serial.begin(115200);
    Serial.println("Final X-AXIS Test with ENABLE pin activated.");

    // CRITICAL STEP: Enable all motor drivers on the CNC Shield
    pinMode(ENABLE_PIN, OUTPUT);
    digitalWrite(ENABLE_PIN, LOW); // Set to LOW to enable

    // Initialize the motor
    stepper.begin(RPM, MICROSTEPS);
}

void loop() {
    Serial.println("--> Rotating forward...");
    stepper.rotate(360); // Rotate 360 degrees forward
    delay(1000);

    Serial.println("<-- Rotating backward...");
    stepper.rotate(-360); // Rotate 360 degrees backward
    delay(2000);
}
```
