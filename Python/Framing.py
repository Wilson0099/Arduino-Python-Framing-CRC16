"""	
	Framing.py - Python data framing using flags, byte stuffing, and CRC 16
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
	
	Last Modified: 1 Apr 2013 07:21 GMT
"""

import array as arr
import CRC_16
import struct
import time

class Framing(object):
    __STX=0x02
    __ETX=0x03
    __DLE=0x10
    __timeout=0.05
    
    def __init__(self):
        pass
    
    def setTimeout(self, timeout):
        self.__timeout=timeout
    
    def sendFramedData(self, data, length, serial):
        buf_index=0
        framed_data=arr.array('B',[])
        
        #Send start flag
        framed_data.append(self.__DLE)
        buf_index+=1
        framed_data.append(self.__STX)
        buf_index+=1
        
        #Send data with byte stuffing - Also calcualte CRC(ignoring stuffing)
        createCRC=CRC_16.CRC_16()
        for i in range(0,length,1):
            if (data[i]==self.__DLE):
                framed_data.append(self.__DLE)
                buf_index+=1
                
                framed_data.append(data[i])
                buf_index+=1
                createCRC.next_databyte(data[i])
            else:
                framed_data.append(data[i])
                buf_index+=1
                
                createCRC.next_databyte(data[i])
                
        #Return CRC
        CRC=createCRC.returnCRC_reset()
        
        #Send CRC with byte stuffing
        framed_data.append((CRC>>8)&0xff)
        buf_index+=1
        
        if(framed_data[buf_index-1]==self.__DLE):
            framed_data.append(self.__DLE)
            buf_index+=1
        
        framed_data.append(CRC&0xff)
        buf_index+=1
        
        if(framed_data[buf_index-1]==self.__DLE):
            framed_data.append(self.__DLE)
            buf_index+=1;

        #Send end flag
        framed_data.append(self.__DLE)
        buf_index+=1
        framed_data.append(self.__ETX)
        buf_index+=1
        
        #Send data
        for i in range(0,buf_index,1):
            serial.write(chr(framed_data[i]))
    
    def receiveFramedData(self, serial):
        data=arr.array('B',[])
        
        checkCRC=CRC_16.CRC_16()

        t_start=time.time()
        while((time.time()-t_start)<self.__timeout):
            if(serial.inWaiting()>0):
                newByte=struct.unpack('B',serial.read(1))[0]
                while((time.time()-t_start)<self.__timeout):
                    if(serial.inWaiting()>0):
                        oldByte=newByte
                        newByte=struct.unpack('B',serial.read(1))[0]
                        if((oldByte==self.__DLE) and (newByte==self.__STX)):
                            while(((time.time()-t_start)<self.__timeout) and (not((oldByte==self.__DLE) and (newByte==self.__ETX)))):                     
                                if(serial.inWaiting()>0):
                                    oldByte=newByte
                                    newByte=struct.unpack('B',serial.read(1))[0]
                                    if(newByte==self.__DLE):
                                        if(oldByte==self.__DLE):
                                            data.append(newByte)
                                            newByte=0
                                        else:
                                            pass
                                    else:
                                        data.append(newByte)
                            data.pop()
                            for i in range(0,len(data),1):
                                checkCRC.next_databyte(data[i])
                            data.pop()
                            data.pop()
                            if(checkCRC.returnCRC_reset()==0):
                                return data
                            else:
                                return -1
        return 0
            
            
                
                
                    
                        