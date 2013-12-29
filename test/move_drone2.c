#include <stdio.h>
#include <RT_ARDrone/RT_ARDrone.h>
/* test contrôle déplacement yaw, x, y, z */

int main ( int argc, char** argv, char** envv ) {

	ARDrone* bob ;
	NavData  data ;
	int test, compt;
	float gaz,mag,magd,mage;
	int ok_gps , ok_move, res, flag;
	float lat_start, lon_start, elev_start ,longitude, elevation, hdop, latitude;
	float lat_current , lon_current, elev_current, psi;

	bob = ARDrone_new( "192.168.10.3" ) ;
	ARDrone_connect( bob , 1 ) ;		
	ARDrone_trim ( bob ) ;
	sleep(1);
	ARDrone_reset_defaults( bob ) ;
	sleep(5) ;
	printf("fin trim et reset attente gps \n");
// attente gps précision
	ok_gps = 1;
	while (ok_gps)  // c'est ok
	{	ARDrone_get_navdata( bob, &data ) ;
		if ((data.hdop !=0) & (data.hdop <4) )
		{
			ok_gps = 0;
			lat_start = data.lat;
			lon_start = data.lon;
			elev_start = data.elevation;
			printf("latitude %lf longitude %lf elevation %lf hdop %lf\n", data.lat, data.lon, data.elevation, data.hdop);
		}
	} // fin while ok_gps
	printf("décollage \n");
	ARDrone_takeoff(bob);
	sleep(4);
	printf("calibration \n");
	ARDrone_calib(bob);
	sleep(4);

// elevation 1.5m 
	ok_move = 0;	
	ARDrone_move(bob,1, 0, 0, 0, 0.2);
	while (!ok_move )  // OK
	{
	  ARDrone_get_navdata( bob, &data ) ;
	 // élévation
	 if (data.altitude > 2000)
	   {printf("hauteur %d \n", data.altitude);
	   ok_move = 1;
	   ARDrone_move(bob,1, 0, 0, 0, 0);
	   }
	 } // fin while ok_move
	
	ok_move = 0;	
	ARDrone_move(bob,1, 0, 0, 0, -0.2);
	while (!ok_move )  // OK
	{
	  ARDrone_get_navdata( bob, &data ) ;
	 // descente
	 if (data.altitude < 1000)
	   {printf("hauteur %d \n", data.altitude);
	   ok_move = 1;
	   ARDrone_move(bob,1, 0, 0, 0, 0);
	   }
	 } // fin while ok_move
	 
// controle cap ? par  yaw 
	ok_move = 0;	
	ARDrone_move(bob,1, 0, 0, 0.1, 0);
	while (!ok_move )  // OK
	{
	  ARDrone_get_navdata( bob, &data ) ;
	 // yaw
	 if (data.psi > 20)
	   {printf("psi %f \n", data.psi);
	   ok_move = 1;
	   ARDrone_move(bob,1, 0, 0, 0, 0);
	   }
	 } // fin while ok_move
	ok_move = 0;	
	ARDrone_move(bob,1, 0, 0, -0.1, 0);
	while (!ok_move )  // OK
	{
	  ARDrone_get_navdata( bob, &data ) ;
	 // yaw
	 if (data.psi < -20)
	   {printf("psi %f \n", data.psi);
	   ok_move = 1;
	   ARDrone_move(bob,1, 0, 0, 0, 0);
	   }
	 } // fin while ok_move
	 

	 
// fin test	
	//sleep(3);
	ARDrone_land(bob);
	sleep(5);
	ARDrone_free( bob ) ;
	return 0 ;

}
