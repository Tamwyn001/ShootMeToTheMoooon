#include<stdio.h>
#include<math.h>
#include<iostream>

const int T = 100;	
const double sim_size = pow(10,1);	// Gird Definitionsbereich
const double lenght = 5 * sim_size;	// Gird Definitionsbereich
const double step = lenght / float(T);	// Gird Definitionsbereich
/*
	Definiere die dreidimensionale Struktur des Problems. Führe hierzu R3 ein.
*/
#include "../../Simulation/src/header/R3.hpp"

/*
	Definiere die Lösungsstruktur. Wir wollen gleichzeitig zwei Bahnen berechnen, um sie nachher im Newtonverfahren vergleichen zu können. Dazu brauchen wir zwei Wege q, p, dq, dp (auf denen gerechnet wird) und zwei Startwerte S1, S2.
*/
typedef struct {
	double q1, q2; // Ort
	double V;	//Potential
} Lsng;


/*
 Initialisiere die Systemgleichungen.
*/
const double Gravk = 1; 				// Gravitationskonstante
const double MEd = 2 * sim_size; 		// Abstand Erde-Mond
const double mE = 1; 					// Masse Erde
const double mM = 0.1; 					// Masse Mond
const double rM = 0.1;					// Radius Mond
const double rE = 0.1;					// Radius Erde
const R3 locE = R3(0, 0, 0);			// Ort Erdezentrum
const R3 locM = R3(MEd, 0, 0);			// Ort Mondzentrum

void compute_potential(Lsng*L)
{
	L->V = Gravk * (mE / pnorm(2, R3(L->q1, L->q2, 0) - locE) + mM / pnorm(2, R3(L->q1, L->q2, 0) - locM));
}

int main () {
	FILE* dof;
	dof = fopen("../tmp/potential.csv", "w");

	// Initialisierung

	Lsng L;

	for (int i = 0; i<T; i++) 
	{
		for (int j = 0; j<T; j++) 
		{
			L.q1 = (double(i)- double(T)/2)*step;
			L.q2 = (double(j)- double(T)/2)*step;
			compute_potential(&L);
			fprintf(dof, "%f, %f, %f \n",L.q1, L.q2, L.V);
		}
		fprintf(dof, "\n");
		
	}
	std::cout<<"splot \"PotentialGird/tmp/potential.csv\" using 1:2:3 with lines \n";
	fclose(dof);
	return 0;
}
