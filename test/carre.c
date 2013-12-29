#include <stdio.h>
#include <RT_ARDrone/RT_ARDrone.h>



int main ( int argc, char** argv, char** envv ) {

	int ok_gps , ok_move;
	ARDrone* bob ;
	NavData  data ;
	float lat_start, lon_start, elev_start ,longitude, elevation, hdop, latitude;

	bob = ARDrone_new( "192.168.10.3" ) ;
	ARDrone_connect( bob, 1 ) ;
	ARDrone_trim ( bob ) 0;
// attente gps précision
	ok_gps = 0;
	while (!= ok_gps)
	(	ARDrone_get_navdata( bob, &data ) ;
		if (data.hdop <4)
		{
			ok_gps = 1;
			lat_start = data.lat;
			lon_start = data.lon;
			elev_start = data.elevation;	
		}
	} // fin while ok_gp
	ARdrone_takeoff(bob); 
	sleep(2);
	ARDrone_calib ( bob ) ;
	sleep(3);
// elevation 2m 
	ok_move = 0;	
	ARDrone_move(bob,1, 0, 0, 0, 0.3);
	while (!=ok_move )
	{
	  ARDrone_get_navdata( bob, &data ) ;
	 if (data.altitude > 2000)
	   {ok_move = 1;
	   ARDrone_move(bob,1, 0, 0, 0, 0);
	   }
	 } // fin while ok_move
	 
	 // orientation à l'est 
	 ok_move = 0;
	ARDrone_move_mag( bob, 4,0,0, 0, 0 , mag, 0);	 
	 while (!=ok_move )
	{
//	  ARDrone_move(bob,1, 0, 0, 0, 0);
	  ARDrone_get_navdata( bob, &data ) ;
	 if (data.psi > 5000)
	   {ok_move = 1;
	   ARDrone_move(bob,1, 0, 0, 0, 0);
	   }
	 } // fin while ok_move
	 
	i=1;
	while(i<4){
	ARDrone_get_navdata( bob, &data ) ;
 	printf("données gps latitude %lf longitude %lf elevation %lf \n",data.lat, data.lon, data.elevation);
 	printf("données gps hdop %lf vdop %lf \n", data.hdop, data.vdop);
 	sleep(2);
 	i=i+1;
 	
 	}
	ARDrone_free( bob ) ;

  
	return 0 ;

}
