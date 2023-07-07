# sunshade [WIP]
## Introduction
The project sunshade is a program for the [arduino](https://de.wikipedia.org/wiki/Arduino_(Plattform)) computing-platform.
The main purpose of this program is to open and close a big sunshade.

<img src="https://github.com/Aladim/sunshade/blob/main/doc/sunshade.jpg" height="200" title="sunshade">

## System Desciption
### Motor and Transmission
The required mechanical work to open and close the sunshade comes from a dc motor.
This dc motor is directly conected to a transmission.
Both devices are recycled from an old cordless screwdrive.

<img src="https://github.com/Aladim/sunshade/blob/main/doc/recycled-cordless-screwdrive.jpeg" height="200" title="recycled cordless screwdrive">

### Motor Driver
The h-bridge modul drives the motor.

<img src="https://github.com/Aladim/sunshade/blob/main/doc/h-bridge-modul.jpeg" height="200" title="h-bridge modul">

### Interface
For the controll interface a IR (infrared) modul is set up.

<img src="https://github.com/Aladim/sunshade/blob/main/doc/ir-modul.jpeg" height="200" title="ir-modul">

I still have a small doubt if it is working while the sunshade is closed, 
but I will figured it out later.
### Single-board microcontroller
Like mention befor a arduino computing-platform is used for the program processing and I/O controlling job.
Currently the Mega 2560 is in charge. But for later on it could be change to a Nano variant.

<img src="https://github.com/Aladim/sunshade/blob/main/doc/mega-2560.jpeg" height="200" title="mega 2560">

### Housing and Mounting Frame
* For the electronics a universal housing of aluminum is being considered.
* To mount the hole device to the sunshade some ideas were made up but currently is still an opne issue to solve.
#### Welding Work
But we are allready happy to announce that we were able to win an welding expert for this project.

<img src="https://github.com/Aladim/sunshade/blob/main/doc/welding-expert.png" title="welding expert">

## POC
To finde out if the approach, to recycle the devices of an old cordless screwdrive for I executed a simple POC :-).

![cordless-screwdrive_AdobeExpress](https://github.com/Aladim/sunshade/blob/main/doc/cordless-screwdrive.gif)

Note: I converted the video from .mp4 to .gif with https://www.adobe.com/express/feature/video/convert/mp4-to-gif

## Software Architecture
### Use Case Diagram

<img src="https://github.com/Aladim/sunshade/blob/main/doc/use-case-diagram.png" height="200" title="use case diagram">
