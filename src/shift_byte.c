// ****************************************************************************
// ***
// ***
// *** RT_Ardrone - A basic library for interfacing the AR.Drone quadricopter
// ***
// *** Copyright (C)   Sebastien Druon ( sebastien.druon@univ-montp2.fr )
// ***
// *** This program is free software: you can redistribute it and/or modify
// *** it under the terms of the GNU General Public License as published by
// *** the Free Software Foundation, either version 3 of the License, or
// *** (at your option) any later version.
// ***
// *** This program is distributed in the hope that it will be useful,
// *** but WITHOUT ANY WARRANTY; without even the implied warranty of
// *** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// *** GNU General Public License for more details.
// *** 
// *** You should have received a copy of the GNU General Public License
// *** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// ***
// ***
// ***
// ****************************************************************************

#include "shift_byte.h"
#include <stdio.h>
#include <stdint.h>
#include"inttypes.h"


int32_t shift_byte(int32_t lsb, int32_t mlsb, int32_t mmsb, int32_t msb)
{
	int32_t tmp = 0;

	tmp = lsb;
	tmp |= mlsb << 8;
	tmp |= mmsb << 16;
	tmp |= msb << 24;

	return tmp ;
}
// modif BJ 8/12
int64_t shift_bytes(int64_t m1, int64_t m2, int64_t m3, int64_t m4, int64_t m5, int64_t m6, int64_t m7, int64_t m8) 
{	int64_t tmp = 0;
	 tmp |= m1 << (0);
	 tmp |= m2 << (8);
	  tmp |= m3 << (16);
	   tmp |= m4 << (24);
	    tmp |= m5 << (32);
	     tmp |= m6 << (40);
	      tmp |= m7 << (48);
	       tmp |= m8 << (56);
	return tmp ;
}



