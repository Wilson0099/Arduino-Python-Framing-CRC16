/*	
	CRC_16.h - Arduino CRC 16 generator
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
	
	Last Modified: 1 Apr 2013 06:53 GMT
*/

#include <Arduino.h>

#ifndef CRC_16_h
#define CRC_16_h

class CRC_16
{
  private:
    //Create CRC_16 lookup table for 0x8005
    static const short m_CRC_16_lookuptable [256];
     
    short m_remainder;
    
  public:
    //Constructor
    CRC_16();
    
    void reset(); //Resets CRC class to ready mode
    void next_databyte(char databyte); //Calculates remainder after next databyte in stream
    short returnCRC_reset(); //Returns 16 bit CRC then resets CRC class to ready state
};

#endif
