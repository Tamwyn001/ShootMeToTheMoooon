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

/*
	Definiere die Lösungsstruktur. Wir wollen gleichzeitig zwei Bahnen berechnen, um sie nachher im Newtonverfahren vergleichen zu können. Dazu brauchen wir zwei Wege q, p, dq, dp (auf denen gerechnet wird) und zwei Startwerte S1, S2.
*/
typedef struct {
	R3 q1, q2;
	R3 p1, p2;
	R3 dq1, dq2;
	R3 dp1, dp2;
	R3 S1, S2; 	// Startwerte p(0) für die Schüsse
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
			cor ist Normabweichung vom Ziel
	*/
	Lsng L0 = {
		R3(0.0, 0.0, rE),	// Startwert q1
		R3(0.0, 0.0, rE), 	// Startwert q2
		R3(0.0, 0.0, 0.0),	// Startwert p1
		R3(0.0, 0.0, 0.0),	// Startwert p2
		R3(0.0, 0.0, 0.0), 	// Startwert dq1
		R3(0.0, 0.0, 0.0), 	// Startwert dq2
		R3(0.0, 0.0, 0.0), 	// Startwert dp1
		R3(0.0, 0.0, 0.0), 	// Startwert dp2
		R3(2.0, 0.0, 0.0), 	// Startwert S1
		R3(1.0, 1.0, 1.0) 	// Startwert S2
	};
	Lsng L = L0;
	double cor = 1;


	for (int i = 0; i < n; i++) {
		shooting(i * dt, &L, &L0, &cor);
		fprintf(dof, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", i * dt, L.q1.x, L.q1.y, L.q1.z, L.q2.x, L.q2.y, L.q2.z, L.p1.x, L.p1.y, L.p1.z, L.p2.x, L.p2.y, L.p2.z, cor);

		// check if solution is close
		if (cor < tol) {
    	    continue;
    	} else {
    	    newtonstep(&L0);
    	}
	}
	
	fclose(dof);
	return 0;
}
