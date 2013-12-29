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
// *** 7 /12 BJ correction, option_size includes : tag + option_size 4 bytes so error not shift 4 
// *** MODIF BJ receive data in function of tag, included gps data
// ****************************************************************************

#include <stdio.h>
#include <stdlib.h>

#include <strings.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netdb.h>

#include <RT_ARDrone/navdata_stream.h>

#include "shift_byte.h"

void* navdata_threadfct( void* data ) ;


NavDataStream* NavDataStream_new( const char* ip_addr ) {

	int ret ;
	NavDataStream* tmp ;
	
	tmp = (NavDataStream*) malloc ( sizeof( NavDataStream ) ) ;

	tmp->socket = socket(AF_INET, SOCK_DGRAM, 0);

	if ( tmp->socket == -1) {
		fprintf(stderr, "[%s] Error creating Navdata socket\n", __FILE__ ) ;
		exit( EXIT_FAILURE ) ;
	}

	tmp->host = (struct hostent *) gethostbyname((char *) ip_addr ); 
	
	tmp->addr.sin_family = AF_INET;
	tmp->addr.sin_addr.s_addr = htonl( INADDR_ANY ) ;	
	tmp->addr.sin_port = htons( NAVDATA_PORT );	
	
	bzero(&(tmp->addr.sin_zero),8);	

	ret = bind( tmp->socket, (struct sockaddr *) &(tmp->addr), sizeof(tmp->addr) );

	pthread_mutex_init( &(tmp->mutex), NULL ) ;
	
	return tmp ;
}


void NavDataStream_free ( NavDataStream* stream ) {

	free( stream );
}

void NavDataStream_connect( NavDataStream* stream ) {

	printf("[ RT_ARDrone ] Starting NavData thread ... \n" ) ;

	stream->thread = pthread_create( &(stream->thread), NULL, navdata_threadfct, (void*) stream ) ;

}


void* navdata_threadfct( void* data ) {

	int ret ;
	int length ;
	NavDataStream* stream ;
	uint32_t option_id ;
	uint32_t option_size ;
	double latitude , longitude, elevation , hdop, vdop  ,latitudef,longitudef  ;
	uint32_t temp ;
	uint64_t tmp ;
	int fin; 
	uint32_t state , bat , altitude ;
	float theta, psi, phi, vx, vy, vz;
	
	
	
	stream = (NavDataStream*) data ;

	char buf[] = {0x01, 0x00, 0x00, 0x00};
	unsigned char nav_data[2048];

	stream->addr.sin_addr = *((struct in_addr *) stream->host->h_addr); 
		
	// Send one packet to enter bootstrap mode
	
	sendto(	stream->socket, 
		buf, strlen(buf), 
		0, 
		(struct sockaddr *) &(stream->addr), sizeof(stream->addr) );

	while(1) {
		
		// Zeros out the array
	
		bzero(&(nav_data), 2048);
	
		// Receives data from drone.  Hangs until received

		int len = sizeof( stream->addr ) ;

		ret = recvfrom( stream->socket, 
			      	nav_data, 2048, 
				0,
			        (struct sockaddr *) &(stream->addr), &len  );

		// Received navdata ... 

		// Stores the initial information from the drone
		
		uint32_t header   = shift_byte( nav_data[0], nav_data[1],  nav_data[2], nav_data[3]);
		uint32_t state    = shift_byte( nav_data[4], nav_data[5],  nav_data[6], nav_data[7]);
		uint32_t sequence = shift_byte( nav_data[8], nav_data[9],  nav_data[10], nav_data[11]);
		uint32_t vision	  = shift_byte( nav_data[12],nav_data[13], nav_data[14], nav_data[15]);

		// printf ( "%d --- header = %d, state = %d, sequence = %d, vision = %d\n", ret, header, state, sequence, vision ) ;

		int option_index = 16;		// Options start at byte 16

		do {
			option_id = nav_data[option_index];
			option_id |=  nav_data[option_index+1] << 8;

			option_size = nav_data[option_index+2];
			option_size |=  nav_data[option_index+3] << 8;

//			printf("Have option tag: %x with size: %d at index: %d \n", option_id, option_size, option_index);
//			if ( (option_id ==0) && (option_size>0) && (option_index==16) )  

			switch (option_id){
				case 0 : // BJ navdata_demo TAG =0
			 	{
				state   = shift_byte( nav_data[option_index+4], nav_data[option_index+5], nav_data[option_index+6], nav_data[option_index+7]);
				 bat     = shift_byte( nav_data[option_index+8], nav_data[option_index+9], nav_data[option_index+10], nav_data[option_index+11]);
				
				temp = shift_byte( nav_data[option_index+12], nav_data[option_index+13], nav_data[option_index+14], nav_data[option_index+15]);
				 theta = ( *(float*)(&temp) ) / 1000 ;

				temp = shift_byte( nav_data[option_index+16], nav_data[option_index+17], nav_data[option_index+18], nav_data[option_index+19]);
				 phi = ( *(float*)(&temp) ) / 1000 ;

				temp = shift_byte( nav_data[option_index+20], nav_data[option_index+21], nav_data[option_index+22], nav_data[option_index+23]);
				 psi = ( *(float*)(&temp) ) / 1000 ;
				
				 altitude = shift_byte( nav_data[option_index+24], nav_data[option_index+25], nav_data[option_index+26], nav_data[option_index+27]);
				
				temp = shift_byte( nav_data[option_index+28], nav_data[option_index+29], nav_data[option_index+30], nav_data[option_index+31]);
				 vx = ( *(float*)(&temp) ) / 1000 ;
				
				temp = shift_byte( nav_data[option_index+32], nav_data[option_index+33], nav_data[option_index+34], nav_data[option_index+35]);
				 vy = ( *(float*)(&temp) ) / 1000  ;


				temp = shift_byte( nav_data[option_index+36], nav_data[option_index+37], nav_data[option_index+38], nav_data[option_index+39]);
				 vz = ( *(float*)(&temp) ) / 1000 ;

				break;
				}
				
				case 10 :
				{
				printf("TAG %d \n", 10); break;
				}
				
				case 27 :  // 	BJ navdata_gps TAG =27	1b  c'est ok 8/12
				{
				 tmp  		= shift_bytes( nav_data[option_index+4],nav_data[option_index+5],nav_data[option_index+6],nav_data[option_index+7],nav_data[option_index+8],nav_data[option_index+9],nav_data[option_index+10],nav_data[option_index+11] );

				 latitude  	= (*(double*) (&tmp));
				 tmp 		= shift_bytes( nav_data[option_index+12],nav_data[option_index+13],nav_data[option_index+14],nav_data[option_index+15],nav_data[option_index+16],nav_data[option_index+17],nav_data[option_index+18],nav_data[option_index+19] ); 
				 longitude 	= (*(double*) (&tmp));
				 tmp 		= shift_bytes( nav_data[option_index+20],nav_data[option_index+21],nav_data[option_index+22],nav_data[option_index+23],nav_data[option_index+24],nav_data[option_index+25],nav_data[option_index+26],nav_data[option_index+27]); 
				 elevation 	= (*(double*) (& tmp));
				 tmp        	= shift_bytes( nav_data[option_index+28],nav_data[option_index+29],nav_data[option_index+30],nav_data[option_index+31],nav_data[option_index+32],nav_data[option_index+33],nav_data[option_index+34],nav_data[option_index+35]); 
				 hdop        	= (*(double*) (& tmp));
				 tmp        	= shift_bytes( nav_data[option_index+124],nav_data[option_index+125],nav_data[option_index+126],nav_data[option_index+126],nav_data[option_index+128],nav_data[option_index+129],nav_data[option_index+130],nav_data[option_index+131]); 
				 vdop        	= (*(double*) (& tmp));
				 
//				 tmp 		= shift_bytes( &nav_data[option_index+64], 8); //
//				 latitudef 	= (*(double*) (& tmp));
//				 tmp	   	= shift_bytes( &nav_data[option_index+72], 8); 
//				 longitudef   	= (*(double*) (& tmp));
				break;
				}
				case 65535 :   // BJ checksum 
				{fin = 1;
				 break;
				 }
				 default : break;	

			// error option_index += 4 + option_size ; 
			
			} //end switch
			option_index += option_size ; 
			
		} while ( fin !=1 ) ;
				fin=0;
				pthread_mutex_lock( &(stream->mutex)  );

				stream->current_navdata.altitude = altitude ;
				stream->current_navdata.bat = bat ;
				stream->current_navdata.phi = phi ;
				stream->current_navdata.psi = psi ;
				stream->current_navdata.state = state ;
				stream->current_navdata.theta = theta ;
				stream->current_navdata.vx = vx ;
				stream->current_navdata.vy = vy ;
				stream->current_navdata.vz = vz ;
				// modif BJ
				stream->current_navdata.lat = latitude ;
				stream->current_navdata.lon = longitude ;
				stream->current_navdata.elevation = elevation ;
				stream->current_navdata.hdop = hdop ;
				stream->current_navdata.vdop = vdop ;
			//	stream->current_navdata.lat_fuse = latitudef ;
				
				pthread_mutex_unlock( &(stream->mutex)  );
		
		// Wait for a while

		usleep(25000) ;

	}

}
/*************************************************************/



/************************************************************/
void NavDataStream_get_navdata( NavDataStream* stream, NavData* data ) {

	pthread_mutex_lock( &(stream->mutex)  );

	data->altitude 	= stream->current_navdata.altitude ;
	data->bat	= stream->current_navdata.bat ;
	data->phi	= stream->current_navdata.phi ;
	data->psi 	= stream->current_navdata.psi ;
	data->state 	= stream->current_navdata.state ;
	data->theta 	= stream->current_navdata.theta ;
	data->vx 	= stream->current_navdata.vx ;
	data->vy 	= stream->current_navdata.vy ;
	data->vz 	= stream->current_navdata.vz ;
/*partie BJ*/
					
	data->fly 	= (stream->current_navdata.state & 0x1) ;
	data->ctrl_nav 	= (stream->current_navdata.state & 0x8 ) >> 3 ;
	data->ctrl_alt 	= (stream->current_navdata.state & 0x10) >>4 ;  /* 0 inactive 1 active*/
	data->trim 	= (stream->current_navdata.state & 0x100 ) >>9 ;/* 0 failed 1 succeeded*/
	data->check_US  = (stream->current_navdata.state & 0x200000 ) >>21 ; /* 0 ok 1 deaf*/
	data->check_pwd = (stream->current_navdata.state & 0x40000 ) >>18; /* 1 too low 0 ok*/
	data->check_angle =(stream->current_navdata.state & 0x80000) >>19; /* 0 OK 1 out of range*/
	data->check_wind =(stream->current_navdata.state & 0x100000 )>> 20; /* 0 ok 1 too much*/
	data->emergency  = (stream->current_navdata.state  & 0x80000000 )>> 31; /* emergency landing O no 1 yes*/ 
	
	data->lat 	=  stream->current_navdata.lat ;
	data->lon 	=  stream->current_navdata.lon ;
	data->elevation =  stream->current_navdata.elevation ;
	data->hdop 	=  stream->current_navdata.hdop ;
	data->vdop 	=  stream->current_navdata.vdop ;//	data->lat_fuse 	=  stream->current_navdata.lat_fuse ;
//	data->lon_fuse 	=  stream->current_navdata.lon_fuse ;
//	printf("lat %lf \n",data->lat);
/*fin bj*/
	pthread_mutex_unlock( &(stream->mutex)  );

}


