#include<stdio.h>
#include<math.h>

const int T = 10;			// Rechenzeitintervallbreite
const double wdt = 0.001;	// Wunsch-Schrittweite

const int nt = (int) T / wdt;	// Rechenschritte
const double dt = T / nt		// Tatsächliche, auf das Intervall angepasste Schrittweite

/*
	Definiere die dreidimensionale Struktur des Problems. Führe hierzu R3 ein.
*/
#include "header/R3.hpp"


typedef struct {
	R3 q;
	R3 p;
	R3 dq;
	R3 dp;
} Lsng;


/*
 Initialisiere die Systemgleichungen.
*/
const double Gravk = 1;
const double MEd = 3 * pow(10,9);
const double mE = 1;
const double mM = 0.1;
const double mS = 0.01;
const R3 locE = R3(0, 0, 0);
const R3 locM = R3(0, 0, MEd);

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
