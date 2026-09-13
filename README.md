# Arduino IR-Controlled Catapult Robot

Arduino Nano Every-based mobile robot featuring PWM motor control, custom infrared communication circuitry, and a servo-actuated catapult controlled through a finite-state architecture.

## Overview

This project was developed as part of an embedded systems course. I constructed and programmed the mobile robotic platform and later integrated an IR-controlled catapult system.

The final robot uses an Arduino Nano Every to control two DC motors and a servo-actuated catapult. Commands are received through a custom IR transmitter and receiver circuit, and the robot progresses through multiple operating states for movement, aiming, firing, and resetting the catapult.

The project combined embedded programming, motor control, analog circuit design, IR communication, servo control, and mechanical prototyping.

## Key Features

- Arduino Nano Every
- PWM DC motor control
- Custom IR transmitter and receiver circuitry
- Analog IR signal detection
- Active band-pass filtering to reduce ambient-light interference
- Servo-actuated catapult
- Finite-state robot control
- 3D-printed mechanical components
- Rubber-band catapult tensioning system

## Control Architecture

The final catapult controller uses four operating states:

1. **Idle** - Motors are stopped while the robot waits for an IR command.
2. **Sentry / Rotation** - The robot rotates until another IR command is received.
3. **Aim / Pause** - The robot stops to allow the catapult to be aimed.
4. **Fire / Reset** - The servo releases the catapult and can then be reset before returning to the idle state.

IR commands are detected by reading the analog receiver voltage and comparing it against a calibrated threshold.

## IR System

The transmitter and receiver circuits were developed and tested as part of the project.

The IR system achieved approximately **15 ft of triggering range in dark-room conditions**. Bright ambient lighting reduced the usable range, so active band-pass filtering was incorporated into the receiver circuitry to reduce interference.

## Mechanical Design

The catapult was based on an existing 3D-printable design that I modified to incorporate a rubber-band tensioning system and integrate with the robotic platform.

A servo motor controls the firing and reset mechanism.

## Earlier Position-Control Development

Earlier development of the robotic platform included replacing time-based motion control with encoder pulse feedback and hardware interrupts.

In testing, the interrupt-driven position-control approach allowed the robot to return within **1 inch of its starting position across 10 trials** after driving forward, rotating 180 degrees, and returning.

## Repository Structure

```text
arduino-ir-catapult-robot/
├── README.md
├── src/
│   └── main.ino
├── hardware/
│   └── project images / circuit documentation
