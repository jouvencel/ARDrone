#include <stdio.h>
#include <RT_ARDrone/RT_ARDrone.h>

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
	 // 
	 if (data.altitude > 1500)
	   {printf("hauteur %d \n", data.altitude);
	   ok_move = 1;
	   ARDrone_move(bob,1, 0, 0, 0, 0);
	   }
	 } // fin while ok_move
	 do {
	   ARDrone_get_navdata( bob, &data ) ;
	   printf("hauteur %d \n",data.altitude);
	   printf("on continue de mesurer la hauteur 1 arret 0");
	   scanf("%d",&res);
	   }while (res==1);
	 ARDrone_move(bob,1, 0, 0, 0, 0);
// orientation à l'est au 90 en attente
printf("Test contrôle de cap \n");
 	ARDrone_get_navdata( bob, &data ) ;
	lat_start = data.lat;
	lon_start = data.lon;
	elev_start = data.elevation;
	printf("latitude %lf longitude %lf elevation %lf hdop %lf\n", data.lat, data.lon, data.elevation, data.hdop);
	printf("psi %f phi %f theta %f \n",data.psi, data.phi, data.theta);
	printf("\n on continue  les tests magneto 1 sinon 0 : ");
	scanf("%d", &res);
	while (res==1) {
	printf("\n valeur de psi magneto  : ");
	 scanf("%f", &psi);
	printf("\n flag 4, 5 ou 7 : ?");
	scanf("%d", &flag);
	ARDrone_move_mag(bob,  flag, 0,0,0, 0, psi,0 ) ;
	sleep(2);
	ARDrone_get_navdata( bob, &data ) ;
	//ARDrone_move_mag(bob,  flag, 0,0,0, 0,0,0 ) ;	
	printf("\n valeur de psi obtenue: %f \n", data.psi);
	printf("\n on continue mag 1 sinon 0 : ");
	scanf("%d", &res);
	} ;
	ARDrone_move(bob,1,0,0,0,0);
	//déplacement en theta
	
	printf("\n on continue  les tests theta 1 sinon 0 : ");
	scanf("%d", &res);
	while (res==1) {
	printf("\n valeur de theta : ");
	 scanf("%f", &psi);
	printf("\n theta entré %f\n",psi);
	printf("\n flag 4, 5 ou 7 : ?");
	scanf("%d", &flag);
	ARDrone_move_mag(bob,  flag, 0,psi, 0, 0,0,0 ) ;
	sleep(2);
	ARDrone_get_navdata( bob, &data ) ;
	ARDrone_move_mag(bob,  flag, 0,0,0, 0,0,0 ) ;
	printf("latitude %lf longitude %lf elevation %lf hdop %lf\n", data.lat, data.lon, data.elevation, data.hdop);
	printf("psi %f phi %f theta %f \n",data.psi, data.phi, data.theta);
	printf("\n on continue theta 1 sinon 0 : ");
	scanf("%d", &res);
	} ;
	ARDrone_move(bob,1,0,0,0,0);

	printf("\n on continue  les tests  phi 1 sinon 0 : ");
	scanf("%d", &res);
	while (res==1) {
	printf("\n valeur de phi : ");
	 scanf("%f", &psi);
	printf("\n phi entré %f\n",psi);
	printf("\n flag 4, 5 ou 7 : ?");
	scanf("%d", &flag);
	ARDrone_move_mag(bob,  flag, psi,0,0, 0,0,0 ) ;
	sleep(2);
	ARDrone_get_navdata( bob, &data ) ;
	ARDrone_move_mag(bob,  flag, 0,0,0, 0,0,0 ) ;
	printf("latitude %lf longitude %lf elevation %lf hdop %lf\n", data.lat, data.lon, data.elevation, data.hdop);
	printf("psi %f phi %f theta %f \n",data.psi, data.phi, data.theta);
	printf("\n on continue phi 1 sinon 0 : ");
	scanf("%d", &res);
	};
	ARDrone_move(bob,1,0,0,0,0);

	printf("\n on continue  les tests psi 1 sinon 0 : ");
	scanf("%d", &res);
	while (res==1) {
	printf("\n valeur de psi : ");
	 scanf("%f", &psi);
	printf("\n phi entré %f\n",psi);
	printf("\n flag 4, 5 ou 7 : ?");
	scanf("%d", &flag);
	ARDrone_move_mag(bob,  flag, 0,psi,0, 0,0,0 ) ;
	sleep(2);
	ARDrone_get_navdata( bob, &data ) ;
	ARDrone_move_mag(bob,  flag, 0,0,0, 0,0,0 ) ;
	printf("latitude %lf longitude %lf elevation %lf hdop %lf\n", data.lat, data.lon, data.elevation, data.hdop);
	printf("psi %f phi %f theta %f \n",data.psi, data.phi, data.theta);
	printf("\n on continue psi 1 sinon 0 : ");
	scanf("%d", &res);
	} ;
	ARDrone_move(bob,1,0,0,0,0);

// fin test	
	//sleep(3);
	ARDrone_land(bob);
	sleep(5);
	ARDrone_free( bob ) ;
	return 0 ;

}
