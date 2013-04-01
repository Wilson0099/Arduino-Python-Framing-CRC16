This is Arduino library for Framing version 1.0
================================================
Copyright (C) 2013 Graeme Wilson <gnw.wilson@gmail.com>


Files included in this release:
--------------------------------
-CRC_16.cpp
-CRC_16.h
-Framing.cpp
-Framing.h
-Timer.cpp
-Timer.h


Usage of library
-----------------
With the Arduino IDE:
To use this arduino library copy the contents of this folder into a subfolder
within the 'Sketchbook location' directory libraries folder. 

To determine the location of this libraries directory look under File>Preferences 
in the Arduino IDE to determine your current 'Sketchbook location'


Getting Started
----------------
The following is a quick guide of the basic commands used to operate this library:

To initialize the framing object call the following:

   Framing framing;

To set timeout for sending or receiving framed data send the following command:

   framing.setTimeout(timeout)
      *Note: timeout is the desired timeout time in seconds
      *Note: if timeout is not set, it defaults to 0.05 seconds

To send an array of data of type 'byte' send the following command:

   framing.sendFramedData(data,length);
      *Note: 'data' is a array of type 'byte'
      *Note: 'length' is an 'int' storing the # of elements to send from 'data' array

To receive an array of data of type 'byte' send the following command:

   framing.receiveFramedData(data, length, crc_valid);
      *Note: array 'data' of type 'byte' must exist before call
      *Note: 'int' length and 'int' crc_valid must exist before call
	  *Note: crc_valid returns -1 if CRC failed or timeout mid stream, 
	     0 if timeout before first byte, or 1 if success

Example Implementation
-----------------------

#include "framing.h"

Framing framing;

void setup() {
  Serial.begin(9600);
  framing.setTimout(0.1);
}

void loop() {
  byte input_buff[100]={0};
  byte output_buff[100]={0};
  int output_length, input_length, crc_valid;

  output_buff[0]=0;
  output_buff[1]=1;
  output_buff[2]=2;
  output_length=3;

  framing.sendFramedData(output_buff,3);
  //the values 1, 2, 3 have been sent through serial
  framing.receiveFramedData(input_buff, input_length, crc_valid);
  //the input buffer has been filled with incoming serial data
}

  
  


