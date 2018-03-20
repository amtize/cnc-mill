// Fil: regning.c
// Datamaskinkonstruksjon Høst 2017 Gruppe A
// Ove Nicolai Dalheim, Jonas Haldorsen, Trond Løvik, Martin Rygg
//---------------------------------------

// Tabell for "linearisering" av sensorverdi.

#include <stm32f30x.h>
#include <math.h>

void Lag_Tabell(void);
float f_tabell[3000];


void Lag_Tabell(void){

      float a1 =   4.739*pow(10,16);//  (-1.27e+20, 1.271e+20)
      float b1 =   -1.96*pow(10,04);//  (-1.738e+06, 1.699e+06)
      float c1 =        3553;//  (-1.515e+05, 1.586e+05)
      float a2 =       431.9;//  (-1053, 1917)
      float b2 =       566.9;//  (-5696, 6829)
      float c2 =        1912;//  (-1332, 5156)

	    for (int i=0;i<3000;i++) {
	       f_tabell[i] =  a1*expf( - ( ( (i-b1) / c1 ) * ( (i-b1) / c1 ) ) )
	       + a2*expf(-( ( (i-b2) /c2) *( (i-b2) / c2 ) ) );

	    }

}





