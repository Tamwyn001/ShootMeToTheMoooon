#include<stdio.h>
#include<math.h>

const int T = 10;			// Rechenzeitintervallbreite
const double wdt = 0.001;	// Wunsch-Schrittweite

const int nt = (int) T / wdt;	// Rechenschritte
const double dt = T / nt		// Tatsächliche, auf das Intervall angepasste Schrittweite

typedef struct {
	double u
	double du
} Lsng;


/*
 Initialisiere die Systemgleichungen.
*/
const double Gravk = 1;
const double MEd = 3 * pow(10,9);
const double mE = 1;
const double mM = 0.1;

#include "header/sysDGL.hpp"


/*
 Initialisiere das Lösungsverfahren.
*/
#include "header/shooting.hpp"


int main () {
	FILE* dof;
	fopen("/tmp/data/moonshot.csv")

	
	fclose(dof);
	return 0;
}
