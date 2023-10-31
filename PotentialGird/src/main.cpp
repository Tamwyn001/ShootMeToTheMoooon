#include<stdio.h>
#include<math.h>
#include<iostream>

const int T = 100;	
const double sim_size = pow(10,9);	// Gird Definitionsbereich
const double lenght = 10 * sim_size;	// Gird Definitionsbereich
const double step = lenght / float(T);	// Gird Definitionsbereich
/*
	Definiere die dreidimensionale Struktur des Problems. Führe hierzu R3 ein.
*/
#include "../../Simulation/src/header/R3.hpp"

/*
	Definiere die Lösungsstruktur. Wir wollen gleichzeitig zwei Bahnen berechnen, um sie nachher im Newtonverfahren vergleichen zu können. Dazu brauchen wir zwei Wege q, p, dq, dp (auf denen gerechnet wird) und zwei Startwerte S1, S2.
*/
struct Lsng{
	double q1, q2; // Ort
	double V;	//Potential

	Lsng() {
		this->q1 = 0.;
		this->q2 = 0.;
		this->V = 0.;
	};
	Lsng( double q1, double q2, double V) {
		this->q1 = q1;
		this->q2 = q2;
		this->V = V;
	};
};


/*
 Initialisiere die Systemgleichungen.
*/
const double Gravk = 6.674 * pow(10,-11); 	// Gravitationskonstante
const double MEd = 3.0 * pow(10,9); 		// Abstand Erde-Mond
const double mE = 1.0 * pow(10,24); 		// Masse Erde
const double mM = 0.012 * mE; 				// Masse Mond
const double mS = 1000.0; 					// Masse Schusskörper
const double rM = 1700.0;					// Radius Mond
const double rE = 6400.0;					// Radius Erde
const R3 locE(0.0, 0.0, 0.0);				// Ort Erdezentrum
R3 locM(MEd, 0.0, 0.0);						// Ort Mondzentrum

double a= MEd;
double b= 0.9 * a;

Lsng cart_to_spherical(R3 *location)
{
	double r = pnorm(2, *location);
	double phi = atan2(location->y, location->x);
	return Lsng(r, phi, .0);
}


void spher_to_cart(Lsng *location)
{
	Lsng tmp = Lsng(location->q1*cos(location->q2), location->q1*sin(location->q2), location->V);
	*location = tmp;
	return;
}

void compute_potential(Lsng*L, const int i) //i = 0: Cartesisch, i = 1: Spherisch
{
	switch (i)
	{
		case 0:
			L->V = -Gravk * (mE / pnorm(2, R3(L->q1+0.001, L->q2+0.001, 0) - locE) 
			+ mM / pnorm(2, R3(L->q1+0.001, L->q2+0.001, 0) - locM));
			break;

		case 1:
			L->V = -Gravk * (mE /pnorm(2, R3(L->q1, 0, 0) - locE)) 
			+ mM / pnorm(2, R3(L->q1 * sin(L->q2)*1. - a * 1., 0., 0.));
			break;

		default:
			break;
	}
	return;
}

int main () {
	FILE* dof;

	dof = fopen("../tmp/potential.csv", "w");

	// Initialisierung

	Lsng L_cart;
	Lsng L_sph;

	for (int i = 0; i<T; i++) 
	{
		for (int j = 0; j<T; j++) 
		{
			L_cart.q1 = (double(i)- double(T)/2)*step;
			L_cart.q2 = (double(j)- double(T)/2)*step;

			

			R3 coord = R3(L_cart.q1, L_cart.q2, 0);
			L_sph = cart_to_spherical(&coord);

			compute_potential(&L_sph, 1);
			compute_potential(&L_cart, 00);
			spher_to_cart(&L_sph);
			fprintf(dof, "%f, %f, %f, %f, %f, %f \n", L_cart.q1, L_cart.q2, L_cart.V, L_sph.q1, L_sph.q2, L_sph.V);
		}
		fprintf(dof, "\n");
		
	}
	std::cout<<"splot \"PotentialGird/tmp/potential.csv\" using 1:2:3 with lines \n";
	fclose(dof);
	return 0;
}
