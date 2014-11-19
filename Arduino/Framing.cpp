/*	
	Framing.cpp - Arduino Due data framing using flags, byte stuffing, and CRC 16
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
*/

#include <Arduino.h>
#include "Framing.h"
#include "CRC_16.h"
#include "Timer.h"

//Define static constants
const byte Framing::m_STX=0x02;
const byte Framing::m_ETX=0x03;
const byte Framing::m_DLE=0x10;

//Constructor for Framing
Framing::Framing() {
	m_timeout=0.05;
}

//Public method for setting communication timout
void Framing::setTimout(double timeout) {
	m_timeout=timeout;
}

//Public method for framing data
void Framing::sendFramedData(byte* data, int length) {
  int buf_index=0;
  byte framed_data[100];
  
  CRC_16 createCRC;
  
  //Send start flag
  framed_data[buf_index]=m_DLE;
  buf_index++;
  framed_data[buf_index]=m_STX;
  buf_index++;
  
  //Send data with byte stuffing - Also calculate CRC (ignore stuffing)
  for (int i=0; i<length; i++) {
    if(data[i]==m_DLE) {
	
      framed_data[buf_index]=m_DLE;
      buf_index++;
      
      framed_data[buf_index]=data[i];
      buf_index++;
      createCRC.next_databyte(data[i]);
    }
    else {
      framed_data[buf_index]=data[i];
      buf_index++;
      createCRC.next_databyte(data[i]);
    }
  }
  
  //Return CRC
  short CRC=createCRC.returnCRC_reset();
  
  //Send CRC with byte stuffing
  framed_data[buf_index]=byte((CRC>>8)&0xff);
  buf_index++;
  if(framed_data[buf_index-1]==m_DLE) {
	framed_data[buf_index]=m_DLE;
	buf_index++;
  }
  framed_data[buf_index]=byte(CRC&0xff);
  buf_index++;
  if(framed_data[buf_index-1]==m_DLE) {
	framed_data[buf_index]=m_DLE;
	buf_index++;
  }
  
  //Send end flag
  framed_data[buf_index]=m_DLE;
  buf_index++;
  framed_data[buf_index]=m_ETX;
  buf_index++;
  
  Serial.write(framed_data, buf_index);
}

void Framing::sendFramedDataSerial1(byte* data, int length) {
    int buf_index=0;
    byte framed_data[100];

    CRC_16 createCRC;

    //Send start flag
    framed_data[buf_index]=m_DLE;
    buf_index++;
    framed_data[buf_index]=m_STX;
    buf_index++;

    //Send data with byte stuffing - Also calculate CRC (ignore stuffing)
    for (int i=0; i<length; i++) {
        if(data[i]==m_DLE) {

            framed_data[buf_index]=m_DLE;
            buf_index++;

            framed_data[buf_index]=data[i];
            buf_index++;
            createCRC.next_databyte(data[i]);
        }
        else {
            framed_data[buf_index]=data[i];
            buf_index++;
            createCRC.next_databyte(data[i]);
        }
    }

    //Return CRC
    short CRC=createCRC.returnCRC_reset();

    //Send CRC with byte stuffing
    framed_data[buf_index]=byte((CRC>>8)&0xff);
    buf_index++;
    if(framed_data[buf_index-1]==m_DLE) {
        framed_data[buf_index]=m_DLE;
        buf_index++;
    }
    framed_data[buf_index]=byte(CRC&0xff);
    buf_index++;
    if(framed_data[buf_index-1]==m_DLE) {
        framed_data[buf_index]=m_DLE;
        buf_index++;
    }

    //Send end flag
    framed_data[buf_index]=m_DLE;
    buf_index++;
    framed_data[buf_index]=m_ETX;
    buf_index++;

    Serial1.write(framed_data, buf_index);
}

//Public method for unframing and returning data
//Returns 1 if CRC valid, 0 if no data was found, and -1 if invalid CRC was calculated
void Framing::receiveFramedData(byte* data, int& length, int& crc_valid) {
	byte newByte, oldByte;
	crc_valid=0;
	
	CRC_16 checkCRC;
	Timer timeout;
	
	timeout.start();
	while(timeout.read_s()<m_timeout) {
		if(Serial.available()>0) {
			newByte=Serial.read();
			while(timeout.read_s()<m_timeout) {
				if(Serial.available()>0) {
					oldByte=newByte;
					newByte=Serial.read();
					if((oldByte==m_DLE) & (newByte==m_STX)) {
						int data_index=0;
						while((timeout.read_s()<m_timeout) & ~((oldByte==m_DLE) & (newByte==m_ETX))) {
							if(Serial.available()>0) {
								oldByte=newByte;
								newByte=Serial.read();
								if(newByte==m_DLE) {
									if(oldByte==m_DLE) {
										data[data_index]=newByte;
										data_index++;
										newByte=0;
									}
								}
								else {
									data[data_index]=newByte;
									data_index++;
								}
						   }
						}
						length=data_index-3;
						for(int i=0; i<length+2; i++) {
							checkCRC.next_databyte(data[i]);
						}
						if(checkCRC.returnCRC_reset()==0x00) {
                			crc_valid=1;
							return;
						}
						else {
							crc_valid=-1;
							return;
						}
					}
				}
			}
		}
	}		
}

void Framing::receiveFramedDataSerial1(byte* data, int& length, int& crc_valid) {
    byte newByte, oldByte;
    crc_valid=0;

    CRC_16 checkCRC;
    Timer timeout;

    timeout.start();
    while(timeout.read_s()<m_timeout) {
        if(Serial1.available()>0) {
            newByte=Serial.read();
            while(timeout.read_s()<m_timeout) {
                if(Serial1.available()>0) {
                    oldByte=newByte;
                    newByte=Serial1.read();
                    if((oldByte==m_DLE) & (newByte==m_STX)) {
                        int data_index=0;
                        while((timeout.read_s()<m_timeout) & ~((oldByte==m_DLE) & (newByte==m_ETX))) {
                            if(Serial1.available()>0) {
                                oldByte=newByte;
                                newByte=Serial1.read();
                                if(newByte==m_DLE) {
                                    if(oldByte==m_DLE) {
                                        data[data_index]=newByte;
                                        data_index++;
                                        newByte=0;
                                    }
                                }
                                else {
                                    data[data_index]=newByte;
                                    data_index++;
                                }
                            }
                        }
                        length=data_index-3;
                        for(int i=0; i<length+2; i++) {
                            checkCRC.next_databyte(data[i]);
                        }
                        if(checkCRC.returnCRC_reset()==0x00) {
                            crc_valid=1;
                            return;
                        }
                        else {
                            crc_valid=-1;
                            return;
                        }
                    }
                }
            }
        }
    }
}
