#include <stdio.h>
#include <iostream>

#define _USE_MATH_DEFINES //for M_PI
#include <math.h>
//cant find M_PI...
# define M_PI           3.14159265358979323846  /* pi */

#include "header/R3.hpp"
#include "header/coordinate.hpp"
#include "header/simulation.hpp"
#include "header/sysDGL.hpp"
#include "header/shooting.hpp"



int main () {

	dof = fopen("../tmp/end.csv", "w");
	dof_earth = fopen("../tmp/earth.csv", "w");
	dof_moon = fopen("../tmp/moon.csv", "w");
	/*
		Verfahrensinitialisierung:
			L ist Lösung auf der gerechnet wird
			L0 ist der Startwert, wird immer am Ende korrigiert
			cor ist Normabweichung vom Ziel
	*/
	Lsng L0 = {
		R3(0.0, 0.0, rE),	// Startwert q1
		R3(0.0, 0.0, -rE), 	// Startwert q2
		R3(0.0, 0.0, 1.0),	// Startwert p1
		R3(0.0, 1.0, 1.0),	// Startwert p2
		R3(0.0, 0.0, 0.0), 	// Startwert dq1
		R3(0.0, 0.0, 0.0), 	// Startwert dq2
		R3(0.0, 0.0, 0.0), 	// Startwert dp1
		R3(0.0, 0.0, 0.0), 	// Startwert dp2
		R3(2.0, 0.0, 0.0), 	// Startwert S1
		R3(1.0, 1.0, 1.0) 	// Startwert S2
	};
	Lsng L = L0;
	double cor = 1.0;

	//transform to spherical coordinates to solve the problem in sperhcial coord
	L.add_inf_offset();
	L.trsf_spherical();
	//std::cout<<"L.q1: "<<L.q1.x<<", "<<L.q1.y<<", "<<L.q1.z<<std::endl;

	fprintf(dof_earth, "%f, %f, %f", locE.x, locE.y, locE.z);


	for (int i = 0; i < 1; i++) {
		//std::cout<<"Shooting "<<i<<std::endl;
		//updqte target on the moon
		update_target();

		shooting(i, &L, &L0, &cor);
		fprintf(dof, "%f, %f, %f, %f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", (double)(i * dt), L.q1.x, L.q1.y, L.q1.z, L.q2.x, L.q2.y, L.q2.z, L.p1.x, L.p1.y, L.p1.z, L.p2.x, L.p2.y, L.p2.z, cor);
		
		//update moon location
		
		

		// check if solution is close
		if (cor < tol) {
    	    continue;
    	} else {
    	    newtonstep(&L0);
    	}
	}
	
	fclose(dof);
	fclose(dof_earth);
	fclose(dof_moon);
	return 0;
}
