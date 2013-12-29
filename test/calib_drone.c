#include <stdio.h>
#include <RT_ARDrone/RT_ARDrone.h>

int main ( int argc, char** argv, char** envv ) {

	int i , BAT;
	ARDrone* bob ;
	NavData  data ;

	bob = ARDrone_new( "192.168.10.3" ) ;

	ARDrone_connect( bob , 0 ) ;
		
	ARDrone_trim ( bob ) ;
	
	sleep(5) ;
	ARDrone_reset_defaults( bob ) ;
	sleep(3);
	ARDrone_takeoff(bob);
	sleep(5);
	ARDrone_calib ( bob ) ;
	sleep(3); /* suffisant pour faire un tour attention */
	
	ARDrone_move(bob, 1, 0,0,0, 0 ) ;
	for (i=1;i<5;i++)
	{ARDrone_get_navdata( bob, &data ) ;
	printf( "state %d - bat %d altitude %d \n", data.state, data.bat , data.altitude) ;
	}
	BAT = data.state & 32768 ;
 	 if (BAT ==0)
 	 printf("batterie OK\n");
 	 else printf("Batterie trop bas\n");
	printf("atterrissage bob \n");

	ARDrone_land(bob);
	for (i=1;i<5;i++)
	{ARDrone_get_navdata( bob, &data ) ;
	printf( "state %d - bat %d altitude %d \n", data.state, data.bat , data.altitude) ;
	}
	sleep(2);
	for (i=1;i<5;i++)
	{ARDrone_get_navdata( bob, &data ) ;
	printf( "state %d - bat %d altitude %d \n", data.state, data.bat , data.altitude) ;
	}
	ARDrone_free( bob ) ;


	return 0 ;

}
