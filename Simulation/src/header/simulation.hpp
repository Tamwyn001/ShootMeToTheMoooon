/*
    The purpose of this header is to allow the other .hpp to access the LSng struct and other system variables
*/

#include <string>	


const double DELTA_ANGLE = 0.0000001; //angle in degree to add to the moon phase each time step


const int T = 10000000;			// Rechenzeitintervallbreite
const int n = 1000;			// Anzahl der Schüsse im Shooting-Verfahren

const double wdt = 10.0;	// Wunsch-Schrittweite

const int nt = (int) T / wdt;	// Rechenschritte
const double dt = T /((double)nt);		// Tatsächliche, auf das Intervall angepasste Schrittweite

const double tol = 0.001;	// Toleranz für die Abweichung am Ende des Rechenintervalls

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
R3 x1; 										//ziel

double moonPhase = 0.0;					//Anfangsphase der Mond um die Erde in rad

double moonRadA= MEd;
double moonRadB= 0.9 * moonRadA;

R3 moonSurface(0.0, 0.0, rM); //surface of the moon in to moon coord. system 

FILE* dof;
FILE* dof_earth;
FILE* dof_moon;

std::string gnuCommand="splot \"../earth.csv\" pointsize 2 title \"Earth\", \"../moon.csv\" pointsize 2 title \"Moon\"";

/*
	Definiere die Lösungsstruktur. Wir wollen gleichzeitig zwei Bahnen berechnen, um sie nachher im Newtonverfahren vergleichen zu können. Dazu brauchen wir zwei Wege q, p, dq, dp (auf denen gerechnet wird) und zwei Startwerte S1, S2.
*/
struct Lsng{
	R3 q1, q2;
	R3 p1, p2;
	R3 dq1, dq2;
	R3 dp1, dp2;
	R3 S1, S2; 	// Startwerte p(0) für die Schüsse


	void trsf_spherical()
	{
		this->q1 = to_spherical(this->q1);
		this->q2 = to_spherical(this->q2);
		this->p1 = to_spherical(this->p1);
		this->p2 = to_spherical(this->p2);
		this->dq1 = to_spherical(this->dq1);
		this->dp1 = to_spherical(this->dp1);
		this->dq2 = to_spherical(this->dq2);
		this->dp2 = to_spherical(this->dp2);
		this->S1 = to_spherical(this->S1);
		this->S2 = to_spherical(this->S2);
	};

	Lsng trsf_cartesian_copy()
	{
		return {to_cart(this->q1), to_cart(this->q2), to_cart(this->p1), to_cart(this->p2), to_cart(this->dq1), to_cart(this->dp1), to_cart(this->dq2), to_cart(this->dp2), to_cart(this->S1), to_cart(this->S2)};
	};

	//add an infinitesimal offset to avoid NaN values e.g. for 1/sin(0)
	void add_inf_offset()
	{
		double displacment = 0.01;
		this->q1.x += displacment;
		this->q1.y += displacment;
		this->q1.z += displacment;
		this->q2.x += displacment;
		this->q2.y += displacment;
		this->q2.z += displacment;
		this->p1.x += displacment;
		this->p1.y += displacment;
		this->p1.z += displacment;
		this->p2.x += displacment;
		this->p2.y += displacment;
		this->p2.z += displacment;
		this->dq1.x += displacment;
		this->dq1.y += displacment;
		this->dq1.z += displacment;
		this->dq2.x += displacment;
		this->dq2.y += displacment;
		this->dq2.z += displacment;
		this->dp1.x += displacment;
		this->dp1.y += displacment;
		this->dp1.z += displacment;
		this->dp2.x += displacment;
		this->dp2.y += displacment;
		this->dp2.z += displacment;
		this->S1.x += displacment;
		this->S1.y += displacment;
		this->S1.z += displacment;
		this->S2.x += displacment;
		this->S2.y += displacment;
		this->S2.z += displacment;
	};

	void apply_new_start_value()
	{
		this->q1 = R3(0.0, 0.0, rE);	// Startwert q1
		this->q2 = R3(0.0, 0.0, -rE); 	// Startwert q2
		this->p1 = this->S1;	// Startwert p1
		this->p2 = this->S2;	// Startwert p2
		this->dq1 = R3(0.0, 0.0, 0.0); 	// Startwert dq1
		this->dq2 = R3(0.0, 0.0, 0.0); 	// Startwert dq2
		this->dp1 = R3(0.0, 0.0, 0.0); 	// Startwert dp1
		this->dp2 = R3(0.0, 0.0, 0.0); 	// Startwert dp2
	};
};

void updateMoon()
{
    moonPhase += (DELTA_ANGLE)*180./M_PI; //degree

    locM.x = moonRadA*cos(moonPhase);
    locM.y = moonRadB*sin(moonPhase);
    locM.z = 0.0;
    return;
}
void update_target()
{
	x1 = locM - moonSurface;
}
