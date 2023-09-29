#include<stdio.h>
#include<math.h>

const int T = 10;			// Rechenzeitintervallbreite
const int n = 1000;			// Anzahl der Schüsse im Shooting-Verfahren

const double wdt = 0.001;	// Wunsch-Schrittweite

const int nt = (int) T / wdt;	// Rechenschritte
const double dt = T / nt;		// Tatsächliche, auf das Intervall angepasste Schrittweite

const double tol = 0.001;	// Toleranz für die Abweichung am Ende des Rechenintervalls

/*
	Definiere die dreidimensionale Struktur des Problems. Führe hierzu R3 ein.
*/
#include "header/R3.hpp"


typedef struct {
	R3 q;
	R3 p;
	R3 dq;
	R3 dp;
	R3 S1, S2; 	// Startwerte für die Schüsse
} Lsng;


/*
 Initialisiere die Systemgleichungen.
*/
const double Gravk = 1; 				// Gravitationskonstante
const double MEd = 3 * pow(10,9); 		// Abstand Erde-Mond
const double mE = 1; 					// Masse Erde
const double mM = 0.1; 					// Masse Mond
const double mS = 0.01; 				// Masse Schusskörper
const double rM = 0.1;					// Radius Mond
const double rE = 0.1;					// Radius Erde
const R3 locE = R3(0, 0, 0);			// Ort Erdezentrum
const R3 locM = R3(0, 0, MEd);			// Ort Mondzentrum
const R3 x1 = locM - R3(0, 0, rM);		// Ziel

#include "header/sysDGL.hpp"


/*
 Initialisiere das Lösungsverfahren.
*/
#include "header/shooting.hpp"


int main () {
	FILE* dof;
	dof = fopen("/tmp/data/moonshot.csv", "w");

	/*
		Verfahrensinitialisierung:
			L ist Lösung auf der gerechnet wird
			L0 ist der Startwert, wird immer am Ende korrigiert
			c ist Normabweichung vom Ziel
	*/
	Lsng L0 = {
		R3(0.0, 0.0, rE),
		R3(0.0, 0.0, 0.0),
		R3(0.0, 0.0, 0.0),
		R3(0.0, 0.0, 0.0),
	};
	Lsng L = L0;
	double cor = 1;


	for (int i = 0; i < n; i++) {
		shooting(i * dt, &L, &L0, &cor);
		fprintf(dof, "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g\n", i * dt, L.q.x, L.q.y, L.q.z, L.p.x, L.p.y, L.p.z, L.dq.x, L.dq.y, L.dq.z, L.dp.x, L.dp.y, L.dp.z);

		// check if solution is close
		if (cor < tol) {
    	    continue;
    	} else {
    	    correct(L0);
    	}
	}
	
	fclose(dof);
	return 0;
}
