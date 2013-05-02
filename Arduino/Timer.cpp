/*	
	Timer.cpp - Arduino timer object for easy timing
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

#include "Timer.h"

//Constructor Implementation
Timer::Timer() {
  m_start=0;
  m_reading=0;
}

//Public method for starting timer
double Timer::start() {
  m_start=micros();
  return double(m_start);
}

//Public method for taking reading since last timer.start() in seconds
double Timer::read_s() {
  m_reading=double(micros()-m_start)/1000000;
  return m_reading;
}

//Public method for taking reading since last timer.start() in micros
double Timer::read_m() {
  m_reading=double(micros()-m_start);
  return m_reading;
}