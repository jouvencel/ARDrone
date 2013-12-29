#include <stdio.h>
#include <inttypes.h>
#include <RT_ARDrone/RT_ARDrone.h>


/*
version du 29/11/13 BJ
test de navdata.state
//00 |  FLY MASK : (0) ardrone is landed, (1) ardrone is flying
//01 |  VIDEO MASK : (0) video disable, (1) video enable
//02 |  VISION MASK : (0) vision disable, (1) vision enable
//03 |  CONTROL ALGO : (0) euler angles control, (1) angular speed control
//04 |  ALTITUDE CONTROL ALGO : (0) altitude control inactive (1) altitude control active
//05 |  USER feedback : Start button state
//06 |  Control command ACK : (0) None, (1) one received
//07 |  Trim command ACK : (0) None, (1) one received
//08 |  Trim running : (0) none, (1) running
//09 |  Trim result : (0) failed, (1) succeeded
//10 |  Navdata demo : (0) All navdata, (1) only navdata demo
//11 |  Navdata bootstrap : (0) options sent in all or demo mode, (1) no navdata options sent
//12 |  Motors status : (0) Ok, (1) Motors Com is down
//13 | 
//14 |  Bit means that there's an hardware problem with gyrometers
//15 |  VBat low : (1) too low, (0) Ok
//16 |  VBat high (US mad) : (1) too high, (0) Ok
//17 |  Timer elapsed : (1) elapsed, (0) not elapsed
//18 |  Power : (0) Ok, (1) not enough to fly
//19 |  Angles : (0) Ok, (1) out of range
//20 |  Wind : (0) Ok, (1) too much to fly
//21 |  Ultrasonic sensor : (0) Ok, (1) deaf
//22 |  Cutout system detection : (0) Not detected, (1) detected
//23 |  PIC Version number OK : (0) a bad version number, (1) version number is OK
//24 |   ATCodec thread ON : (0) thread OFF (1) thread ON
//25 |  Navdata thread ON : (0) thread OFF (1) thread ON
//26 |   Video thread ON : (0) thread OFF (1) thread ON
//27 |   Acquisition thread ON : (0) thread OFF (1) thread ON
//28 |   CTRL watchdog : (1) delay in control execution (> 5ms), (0) control is well scheduled // Check frequency of control loop
//29 |  ADC Watchdog : (1) delay in uart2 dsr (> 5ms), (0) uart2 is good // Check frequency of uart2 dsr (com with adc)
//30 | Communication Watchdog : (1) com problem, (0) Com is ok // Check if we have an active connection with a client
//31 Emergency landing : (0) no emergency, (1) emergency

*/
int main ( int argc, char** argv, char** envv ) {

	 float altitude , psi;
	int ok_move, compt;
/*	ARDrone* bob ;
	NavData  data ;*/
	printf("bonjour\n");
	printf("valeur de psi : ");
	 scanf("%f", &psi);
	printf("psi,taper %f\n",psi);
	altitude = 0.2	;
	compt = 0;
	ok_move =0;
	printf("Altitude  %d \n", *(int *) (&altitude));
	printf("bonjour pascal\n");
	while ((!ok_move) & (compt < 20))
	{
	printf("cde 0.2 psi %f \n",0.2);
	if ((100 <92) & (80 > 88))
	 {ok_move = 1;
	 //ARDrone_move_mag(bob, 4, 0,0,0, 0, 0,0 ) ;
	 printf("cap %f \n", 48.);
	 }
	 compt = compt + 1;
	}
	
/*	bob = ARDrone_new( "192.168.10.3" ) ;
	ARDrone_connect( bob ,0) ;
	ARDrone_trim ( bob ) ;

	ARDrone_takeoff(bob);	
	sleep(5);

 
 
	ARDrone_land(bob);

	ARDrone_free( bob ) ;*/


	return 0 ;

}
