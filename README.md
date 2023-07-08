# sunshade [WIP]
## Introduction
The project sunshade is a program for the [arduino](https://de.wikipedia.org/wiki/Arduino_(Plattform)) computing-platform.
The main purpose of this program is to open and close a big sunshade.

<img src="https://github.com/Aladim/sunshade/blob/main/doc/img/sunshade.jpg" height="200" title="sunshade">

## System Desciption
### Motor and Transmission
The required mechanical work to open and close the sunshade comes from a dc motor.
This dc motor is directly conected to a transmission.
Both devices are recycled from an old cordless screwdrive.

<img src="https://github.com/Aladim/sunshade/blob/main/doc/img/recycled-cordless-screwdrive.jpeg" height="200" title="recycled cordless screwdrive">

### Motor Driver
The h-bridge modul drives the motor.

<img src="https://github.com/Aladim/sunshade/blob/main/doc/img/h-bridge-modul.jpeg" height="200" title="h-bridge modul">
Datasheet: https://www.makershop.de/download/BTS7960-Motor-Driver.pdf

### Interface
For the controll interface a IR (infrared) modul is set up.

<img src="https://github.com/Aladim/sunshade/blob/main/doc/img/ir-modul.jpeg" height="200" title="ir-modul">

I still have a small doubt if it is working while the sunshade is closed, 
but I will figured it out later.
### Single Board Microcontroller
Like mention befor a arduino computing-platform is used for the program processing and I/O controlling job.
Currently the Mega 2560 is in charge. But for later on it could be change to a Nano variant.

<img src="https://github.com/Aladim/sunshade/blob/main/doc/img/mega-2560.jpeg" height="200" title="mega 2560">

### Housing and Mounting Frame
* For the electronic assembly a universal aluminum housing is being considered.
* How to mount the complete assembly to the sunshade is currently being explored.
#### Welding Work
But we are happy to announce that we were able to win an welding expert for this project.

<img src="https://github.com/Aladim/sunshade/blob/main/doc/img/welding-expert.png" title="welding expert">

## POC
To finde out if the approach, to recycle the devices of an old cordless screwdrive for I executed a simple POC :-).

![cordless-screwdrive_AdobeExpress](https://github.com/Aladim/sunshade/blob/main/doc/img/cordless-screwdrive.gif)

Note: I converted the video from .mp4 to .gif with https://www.adobe.com/express/feature/video/convert/mp4-to-gif

## Electrical Characteristics

### Motor

Motor values when no mechanical resistant is conected - no sunshade
Voltage 
11.28 V
11.27 V
11.24 V
Current
1.70 A
1.73 A
1.77 A

Motor "anfahren"
Voltage 5.00 V
Current 11.25 A

Motot with sunshade connected
Voltage
7.00 V - 8.00 V
Current
9.00 A max 9.00 - 10.00 A

Motor stops becouse oc mecanical blocade
Voltag
3.10 V
3.60 V
Current
13.00 A - 14.00 A


## Software Architecture
### Dependencies
#### Libraries
* [Arduino-IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote)
### Use Case Diagram

<img src="https://github.com/Aladim/sunshade/blob/main/doc/img/use-case-diagram.png" height="450" title="use case diagram">
