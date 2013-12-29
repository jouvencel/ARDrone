#ifndef NAVDATA_H
#define NAVDATA_H

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
// *** Modif BJ 
// ***
// ****************************************************************************

#include <stdint.h>

typedef struct {

	uint32_t state ; /*cf.  forum*/
	uint32_t bat ;   

	float theta ;
	float phi ;
	float psi ;
				
	int32_t altitude ; 				
				
	float vx ; /* estimation du ardrone */
	float vy ;
	float vz ;
	/* modif 1 BJ décriptage state*/
	 unsigned int fly ; /*0 drone landed   1 drone flying*/
	 unsigned int ctrl_nav ; /*0 ctrl euler 1 ctrl angular speed*/
	 unsigned int ctrl_alt ; /* 0 inactive 1 active*/
	 unsigned int trim ;     /* 0 failed 1 succeeded*/
	 unsigned int check_US ; /* 0 ok 1 deaf*/
	 unsigned int check_pwd ; /* 1 too low 0 ok*/
	 unsigned int check_angle; /* 0 OK 1 out of range*/
	 unsigned int check_wind ; /* 0 ok 1 too much*/
	 unsigned int emergency ; /* emergency landing O no 1 yes*/ 
	 /* modif 2 BJ trame gps proprement il faudrait créer une structure à part*/
	 

	  uint16_t      tag;                    /*!< Navdata block ('option') identifier */
	  uint16_t      size;                   /*!< set this to the size of this structure */
	  double     lat;                    /*!< Latitude */
	  double     lon;                    /*!< Longitude */
	  double     elevation;              /*!< Elevation */
	  double     hdop;                   /*!< hdop */
	  int32_t       data_available;         /*!< When there is data available */
	  uint8_t       unk_0[8];
	  double     lat0;                   /*!< Latitude ??? */
	  double     lon0;                   /*!< Longitude ??? */
	  double     lat_fuse;               /*!< Latitude fused */
	  double     lon_fuse;               /*!< Longitude fused */
	  uint32_t      gps_state;              /*!< State of the GPS, still need to figure out */
	  uint8_t       unk_1[40];
	  double     vdop;                   /*!< vdop */
	  double     pdop;                   /*!< pdop */
	  float     speed;                  /*!< speed */
	  uint32_t      last_frame_timestamp;   /*!< Timestamp from the last frame */
	  float     degree;                 /*!< Degree */
	  float     degree_mag;             /*!< Degree of the magnetic */
	  uint8_t       unk_2[16];
	  struct{
	    uint8_t     sat;
	    uint8_t     cn0;
	  }channels[12];
	  int32_t       gps_plugged;            /*!< When the gps is plugged */
	  uint8_t       unk_3[108];
	  double     gps_time;               /*!< The gps time of week */
	  uint16_t      week;                   /*!< The gps week */
	  uint8_t       gps_fix;                /*!< The gps fix */
	  uint8_t       num_sattelites;         /*!< Number of sattelites */
	  uint8_t       unk_4[24];
	  double     ned_vel_c0;             /*!< NED velocity */
	  double     ned_vel_c1;             /*!< NED velocity */
	  double     ned_vel_c2;             /*!< NED velocity */
	  double     pos_accur_c0;           /*!< Position accuracy */
	  double     pos_accur_c1;           /*!< Position accuracy */
	  double     pos_accur_c2;           /*!< Position accuracy */
	  float     speed_acur;             /*!< Speed accuracy */
	  float     time_acur;              /*!< Time accuracy */
	  uint8_t       unk_5[72];
	  float     temprature;
	  float     pressure;
	 
} NavData ;


#endif
