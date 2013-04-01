/*	
	Framing.h - Arduino Due data framing using flags, byte stuffing, and CRC 16
	Copyright (C) 2013 Graeme Wilson <gnw.wilson@gmail.com>
	
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
	
	Last Modified: 1 Apr 2013 07:55 GMT
*/

#include <Arduino.h>

#ifndef FRAMING_h
#define FRAMING_h

class Framing
{
  private:
    static const byte m_STX, m_ETX, m_DLE;
	double m_timeout;
  public:
    Framing();
    
    void setTimout(double timeout); //Set timeout for serial communication
    void sendFramedData(byte* data, int length); //Frame data with flag and byte stuffing
    void receiveFramedData(byte* data, int& length, int& crc_valid); //Receive framed data through serial and unframe it
};

#endif

