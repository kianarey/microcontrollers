# Microcontrollers

This repository includes all lab experiments completed by me during summer 2019 for course EE 2361 Microcontrollers offered by the University of Minnesota-Twin Cities. In this course, the device used is Microchip's PIC24FJ64GA002. 

I also was a peer Teaching Assistant for this course in Fall 2020. 

### Lab 1 - Initial Software and Hardware Set Up + Forever Bouncing LED
The purpose of this lab is to get the intial software and hardware set up for the remainder of the course. MPLAB X IDE as well as the XC16 Compiler are installed. Basics of soldering, I/O and bitwise operations are practiced. Bitshifting and bitmasking operations are used to produce an indefinitely bouncing LED. 

### Lab 2 - RGB LED in Assembly + Mixed ASM/C Program
This lab has two parts: a) RGB LED in Assembly and b) Mixed Assembly + C Programming.

The purpose of Lab 2a is to become familiar with the basic assembly instructions for changing the state of the general purpose I/O (GPIO) pins on the PIC24 microcontroller. The timing implications of various instructions and their impact on the resulting output waveform are explored. These skills are combined to change the color of an individually addressable RGB LED (iLED).

In Lab 2b, the assembly instructions are packaged into a C-library, so that a created sparkly light shows quickly and easily. This library is used to reimplement a function from the Adafruit NeoPixel Library on PIC24.

### Lab 3 - Multiplexing
In this lab, multiplexing is used to overcome the inherent pin shortage on the PIC24 microcontroller. It explores both input and output multiplexing. This lab utilizes a keypad (for input) and a double seven-segment display (for output).

The completed program does the following:

1. Start with all segments off.
2. Every <30ms, scan the keypad for input. 
3. For every key press, shift the right most displayed value to the left seven-segment digit (most significant), then display the key pressed on the right most digit (least significant).
4. The display should be multiplexed and show both digits simultaneously (at least to the human eye).

Additionally, the program functions continuously, always displaying the last two digits pressed. There are no noticeable flicker, even when shaking the display.
All display and keypad functions are self-contained in a separate library (.h and .c files).

### Lab 4 - Input and Output Capture Peripherals
The purpose of this lab is to understand and explore the basics of input capture and output compare. A double-click and triple-click detector is built using a push button and a servo mounted flag, measuring the speed at which the button is being pressed.

### Lab 5 - Inter-Integrated Circuit (I2C) Interfacing with an LCD
The goal of this lab is to connect the PIC24 to a LCD and display the message “Hello World!” A software library (also known as Application Programmable Interface (API)) is implemented to set up and communicate with the serial LCD display quickly and easily. The code developed utilizes the serial interface I2C.

Serial interfaces are commonly used in industry today. They allow for low pin count communication between integrated circuits (ICs), like the PIC24 and an LCD.  Without a serial interface, LCDs typically require 10+ pins to operate. 

### Lab 6 - Analog to Digital Converter (ADC) Interfacing with LCD
In this lab, a digital voltmeter is developed, reading the voltage of an analog source over time, placing the values in a circular buffer, and showing the most recent value on an LCD. Input is read from a potentiometer as an analog source.
