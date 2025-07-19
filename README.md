Here’s the cleaned-up version of your **README.md** content for GitHub, without emojis:

---

# Real-Time Dual DC Motor Position Control with Encoder and PID – Arduino

## Overview

This project is a real-time control system using **two DC motors with encoders**, controlled via PID (Proportional–Integral–Derivative) loops using an **Arduino Uno**. The motor direction and speed are managed by an **L293D motor driver**, and encoder feedback is used to reach target positions accurately. A current sensor using a **shunt resistor and op-amp (LM741)** was also implemented for real-time current monitoring.

---

## Features

* Real-time **position tracking** with encoders
* PID control
* Speed and direction control through L293D motor driver
* Current sensing using **1Ω shunt resistor** and **LM741 op-amp**
* Serial output of motor position, speed, error, and (attempted) current readings

---

## Components Used

* 2x DC Motors with Encoders
* 1x L293D Motor Driver IC
* 1x Arduino Uno
* 1x 741 Op-Amp
* 1x 1Ω Shunt Resistor
* 9V Battery (motor supply)
* 10kΩ and 1kΩ resistors for op-amp circuit
* Breadboard and jumper wires

---

## Circuit Description

### Motor + Encoder Connection:

* **Motor A**: Connected to L293D output pins OUT1 and OUT2
* **Motor B**: Connected to OUT3 and OUT4
* **Encoders**:

  * Encoder A channels → Arduino pins 2 and 3
  * Encoder B channels → Arduino pins 18 and 19 (or any other interrupt-capable pins)

### L293D Motor Driver:

* **EN1, EN2** connected to 5V
* **IN1, IN2, IN3, IN4** → Arduino control pins (e.g., 6, 7, 8, 9)
* **Vcc1 (logic)** → 5V
* **Vcc2 (motor supply)** → 9V battery
* **GNDs** → Connected to a **common ground** shared with Arduino

### Current Sensing (741 operational amplifier + Shunt):

* **Shunt resistor (1Ω)** placed in series with motor driver **GND path**
* **One side** of shunt connects to **motor driver's ground output**
* **Other side** connects to **Arduino/battery ground** (system ground)
* **Op-Amp (LM741)** used in **non-inverting amplifier** configuration:

  * **In+** → across shunt (closer to motor driver GND)
  * **In−** → voltage divider between op-amp output and ground (10kΩ–1kΩ for gain control)
  * **OUT** → Arduino analog input A0
  * **Vcc+** → 9V
  * **Vcc−** → GND

---

## Arduino Code Summary

* Reads encoder ticks from both motors
* Calculates position, speed, and error
* Implements a basic PID controller to reach target position
* Generates PWM output based on control signal `u`
* Optionally reads current via analog input (A0/A1) from op-amp

---

## Current Not Showing Up – Possible Reason

Despite correct circuit connections, the current reading remains **0V**. This may be due to:

* **Improper ground referencing**: The shunt resistor must be placed between the **motor driver GND** and **system ground**, not between battery negative and system ground.
* **Low voltage drop across the shunt**: If the current is low (e.g., 100mA), the voltage drop across a 1Ω resistor is only 0.1V — often too small for 741 OPERATIONAL AMPLIFIER to amplify effectively without proper gain.
* **Op-Amp configuration issue**: 741 AMPLIFIER requires proper biasing and might not be suitable for single-supply low-side current sensing. A better choice would be a **rail-to-rail op-amp** or dedicated current sensor like **INA219**.

---

## To-Do / Improvements

* Replace 741 OPERATIONAL AMPLIFIER with a dedicated current sensor (INA219 or ACS712)
* Fine-tune PID gains using tuning techniques
* Add Bluetooth or button-based control for setting target positions
* Visual display using LCD or serial plotter
* --
  
## CURCUIT DIAGRAM
<img width="1038" height="812" alt="image" src="https://github.com/user-attachments/assets/79b0b84a-9aec-4d7f-b401-32927f1a5275" />


