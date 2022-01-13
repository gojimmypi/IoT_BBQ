Your final project is to design and build a simple system that solves a problem you find
interesting. The final project is intended to bring together the course topics in a form that can be
shared with prospective employers.

The project was described in the Final Project video (see Week 1 Lecture - Final Project
Overview. The slides have the essential information.

Keeping up with the course exercises will help you finish the project without undue effort at the
end of the course. That said, students are expected to spend 10-15 hours on this project in
addition to the exercises. That is not a lot of time so you’ll have to be efficient and focused.

While the lectures have talked about grandiose ideas, please keep your system simple,
explainable, and reuse code.


## Minimum Project Requirements
The project must:

(a) Use a Cortex-M processor
(b) Have a button that causes an interrupt
(c) Use at least three peripherals such as ADC, DAC, PWM LED, Smart LED, LCD,
sensor, BLE
(d) Have serial port output
(e) Implement an algorithmic piece that makes the system interesting
(f) Implement a state machine

You are not required to use a HAL but it is encouraged. In fact, write as little code as possible,
reusing whatever you can, while keeping in mind licensing.

### Cortex-M Processor
Any Cortex-M processor can be used. The STM32 and the Discovery boards were
recommended but any Cortex-M is good. Students may use a processor/board simulator
instead of physical hardware (please notify a mentor if you intend to use a simulator).

### Button
The system should have a button that causes an interrupt. What the interrupt does is up to you.
The goal here is to show a simple GPIO interrupt handler being used.

### Peripherals
The system should interact with at least three peripherals. The peripherals suggested include
ADC, DAC, PWM LED, Smart LED, LCD, SPI sensor, and BLE. However, any peripherals are
acceptable as long as they are not controlled by a simple GPIO. The peripherals may be
internal to the microcontroller (like an on-board ADC) or external (SPI Flash, I2C sensor, PWM
speaker). There should be three different peripherals used.

### Serial Port
In addition to the peripherals, the system should have a serial port configured for debugging.
This may be simple logging or it may include a command line interface.

### Algorithm
The system should have an application, it should do something. Exactly what it does is up to
you, hopefully it is something that interests you.
Many examples were given in the final project lecture (slides). You may use one of those or
develop your own idea.

### State Machine
The system should include a basic state machine with at least three states. This may be part of
your algorithmic element. Also, using a command line on the serial port fulfills this requirement.

## Deliverables

The final project will be delivered as:

(a) Video of the system working as intended (link to mp4 or youtube)
(b) Write up of the system (PDF or Google docs report).
(c) Link to the code

These will be submitted to assignment-submissions in Discord or emailed to Jeff Hurd
(jeff@classpert.com). Please submit links to all three deliverables as part of one message.
Bonus points are available by including one of these:

 * An analysis of the power used in the system (expected vs actual)
 * Implementation of firmware update with a description in the report of how it works
 * A description of profiling the system to make it run faster

Additional bonus points are available by having a version control history showing the
development process

### Video
A two to five minute video will be used to give an introduction and show the functionality of the
system. This does not need to have high production values, it is intended as a simple check of
the system. Talking about the system as you film is great.

### Report

The written part of the assignment is an introduction to the system for another programmer. The
write up should include:

 * Application description
 * Hardware description
 * Software description
	-  Describe the code in general
	-  Describe the parts you wrote in some detail (maybe 3-5 sentences per module)
	-  Describe code you re-used from other sources, including the licenses for those
 * Diagram(s) of the architecture
 * Build instructions
	-  How to build the system (including the toolchain(s))
		-  Hardware
		- Software
	-  How you debugged and tested the system
 * Future
	-  What would be needed to get this project ready for production?
	-  How would you extend this project to do something more? Are there other features you’d like? How would you go about adding them?

 * Grading
	-  Self assessment of the project: for each criteria, choose a score (1, 2, 3) and explain your reason for the score in 1-2 sentences.
	-  Have you gone beyond the base requirements? How so?

### Link to the Code
The code will be reviewed for clarity and that it meets the minimum project goals. Please make it
clear which files are written or significantly modified by you.