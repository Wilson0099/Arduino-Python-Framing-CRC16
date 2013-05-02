/*	
	Timer.h - Arduino timer object for easy timing
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

#ifndef Timer_h
#define Timer_h

class Timer
{
  private:
    unsigned long m_start;
	double m_reading;
         
  public:
    //Constructor
    Timer();
    
    double start(); //Return start time of timer
    double read_s(); //Return current time of timer since last timer.start() was called in seconds
	double read_m(); //Return current time of timer since last timer.start() was called in micros
};

#endif
