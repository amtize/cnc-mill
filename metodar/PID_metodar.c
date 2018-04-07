//// Fil: PID_metodar.c
//// Datamaskinkonstruksjon Høst 2017 Gruppe A
//// Ove Nicolai Dalheim, Jonas Haldorsen, Trond Løvik, Martin Rygg
////---------------------------------------
//
//
////-------------------------------------------------------------//
//// Biblioteker						  						   //
//#include "math.h"
//#include "extern_dekl_globale_variablar.h"
//
////-------------------------------------------------------------//
//// Reguleringsalgoritme				  						   //
//void PID_reguler(void){
//	// AVVIK + GJENNOMSNITTLIG AVVIK AV SISTE 3 VERDIER
//	avvik_mm[2] = avvik_mm[1];
//	avvik_mm[1] = avvik_mm[0];
//	avvik_mm[0] = ref_mm - data0;
//	avvik_mm_gj = (avvik_mm[0] + avvik_mm[1] + avvik_mm[2]) / 3;
//	avvik_mm_gjk = 1000 * avvik_mm_gj;	// For grafisk visualisering i STMStudio
//
//	// FILTRER
//	avvik_filtert[1] = avvik_filtert[0];
//	avvik_filtert[0] = (iir_a*avvik_filtert[1] + (1024 - iir_a)*avvik_mm[0]) / 1024;
//
//    // DERIVASJON
//	if (derivator_begrensing > 0){
//		d_ledd = K_d * ((avvik_filtert[0] - avvik_filtert[1])*100);
//	} else {
//		d_ledd = K_d * ((avvik_mm[0] - avvik_mm[1])*100);
//	}
//
//	// INTEGRASJON
//	i_ledd[1] = i_ledd[0];
//	i_ledd[0] = i_ledd[1] + (10000*K_i * ((avvik_mm[0] + avvik_mm[1]))/200000);
//
//	if (i_ledd[0]<(-integrator_antiwindup_max)){i_ledd[0] = -integrator_antiwindup_max+1;}
//	if (i_ledd[0]>integrator_antiwindup_max){i_ledd[0] = integrator_antiwindup_max-1;}
//	if (integrator_antiwindup > 0){
//		if(i_ledd[0] > integrator_antiwindup_max){i_ledd[0] = integrator_antiwindup_max-1;}
//		if(i_ledd[0] < -integrator_antiwindup_max){i_ledd[0] = -integrator_antiwindup_max+1;}
//	}
//
//	// PROPORSJONALITET
//	p_ledd = K_p*avvik_mm_gj;
//
//	// PÅDRAG
//	if(((ref_mm-data0)>-dodtid)&&(dodtid>(ref_mm-data0))){ //DØDBÅND
//			paaaadrag=0;
//	} else {
//		paaaadrag = p_ledd + i_ledd[0] + d_ledd;
//	}
//	LinMot_paadrag(paaaadrag);
//}
//
