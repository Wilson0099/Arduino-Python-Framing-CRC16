This is Python library for Framing version 1.0
================================================
Copyright (C) 2013 Graeme Wilson <gnw.wilson@gmail.com>


Files included in this release:
--------------------------------
-CRC_16.py
-Framing.py


Usage of library
-----------------
To use this library with python import it into the module you need to use.


Getting Started
----------------
The following is a quick guide of the basic commands used to operate this library:

To initialize the framing object call the following:

   import Framing
   framing=Framing.Framing()

To set timeout for sending or receiving framed data send the following command:

   framing.setTimeout(timeout)
      *Note: timeout is the desired timeout time in seconds
      *Note: if timeout is not set, it defaults to 0.05 seconds

To send an array of data of type 'byte' send the following command:

   framing.sendFramedData(data,length,serial);
      *Note: 'data' is a array of type 'byte' (ie. array('B',[]))
      *Note: 'length' is the # of elements to send from 'data' array
      *Note: 'serial' is the serial object opened by pyserial module

To receive an array of data of type 'byte' send the following command:

   framing.receiveFramedData(serial);
      *Note: 'serial' is the serial object opened by pyserial module
      *Note: either returns data, the value -1 (CRC didn't match, or timeout mid stream) 
         or 0 (for timeout before first byte)


Example Implementation
-----------------------

import Framing
import serial
framing=Framing.Framing()

ser=serial.Serial("Com1",9600,timeout=0.1)
time.sleep(2)

framing.sendFramedData([1,2,3],3,ser)
#the values 1, 2, 3 have been sent through serial

data=framing.receiveFramedData(ser)
#the input buffer has been filled with incoming serial data


  
  


