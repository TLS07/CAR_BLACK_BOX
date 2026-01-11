# 🚗 Car Black Box

## ⭐Introduction
A Car Black Box System is an embedded data logging system used to monitor and record important vehicle parameters during operation. The stored data can be used later for analysis, diagnostics, and understanding vehicle behavior during critical events.

## 💠Project Overview
This project implements a car black box using a PIC microcontroller, developed and tested on the PICSimLab development board.

he system continuously monitors the vehicle and logs data whenever a gear change occurs. Each log contains the time, event (gear), and speed, which is stored in external EEPROM. The system provides a menu-driven interface with password protection and supports UART-based log download using Tera Term.

## 💠Key features
- Event-based data logging,logs created at every gear shift.

- Each logs consists of speed, gear position, Accurate time stamping using RTC(ds1307)

- logs stored in Non-volatile storage using external EEPROM and Password-protected access

- Menu-driven user interface

- UART-based log download to the system (TTL to USB converter)

## 💠Hardware 
- PIC 16f877A(picsimlab dev board)

- DS1307 Real-Time Clock

- External EEPROM (I²C)

- Character LCD (16X2)

- Digital Keypad

- UART Interface(TTL converter)
## 💠Technologies
- Embedded C (XC8 Compiler)

- I²C Communication

- UART Communication (9600 baurd rate RC6(TX),RC7(RX) )

- EEPROM Read/Write

- RTC Time Management

- Menu-based State Machine Design

## 📽️ Project Demo Video

Watch the complete project demonstration here:  
👉 https://drive.google.com/file/d/1D4ZH2SpMGprd1S3Qc4vGdCuPoyolc4SE/view?usp=sharing

