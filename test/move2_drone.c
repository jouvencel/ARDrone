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
/*test mag ok*/
	ARDrone_move_mag(bob, 4, 0,0,0, 0, 0.67,0 ) ;
	sleep();
	
	ARDrone_land(bob);
	
	ARDrone_free( bob ) ;


	return 0 ;

}
