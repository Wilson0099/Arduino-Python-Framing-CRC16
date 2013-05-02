This is Framing version 1.1
============================
Copyright (C) 2013 Graeme Wilson <gnw.wilson@gmail.com>


License information
--------------------
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


Contents of Project
--------------------
This project contains three parts:
-Arduino framing library
-Python Framing modules


Usage of Project
-----------------
This project is designed to be used to provide a protocol for communication
between an Arduino and python. The included source files
provide the necessary objects that can be used in your projects to send
data packets with flag bytes, data stuffing, and CRC 16 error checking.

For further details on usage of either the Arduino libraries or python 
modules see README files inside subfolders.

Additional Details
-------------------
If memory is a concern then the framed data output buffer should be customized. 
It is currently set to be 'framed_data[100]' in "void Framing::sendFramedData(byte* data, int length)". 
This can conservatively be set to a value which is equal to (2*length_outbound_data + 8 ). 
The value (2*length_outbound_data + 8 ) is chosen for the worst case where all data to be sent equals 
DLE and both CRC values equal DLE.

The packet is structured as follows: [DLE] [STX] [Stuffed Data] [Stuffed CRC16] [DLE] [ETX]

Stuffing refers to adding an additional DLE character before any DLE that appears in the data to be 
sent or in the calculated CRC.

The CRC is calculated before byte stuffing occurs, or on the receiving end it is calculated after 
the data has been unstuffed.
