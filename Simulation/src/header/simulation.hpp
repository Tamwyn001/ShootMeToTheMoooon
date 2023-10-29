/*
    The purpose of this header is to allow the other .hpp to access the LSng struct and other system variables
*/



#define DELTA_ANGLE = 0.001; //angle in degree to add to the moon phase each time step

/*
	Definiere die Lösungsstruktur. Wir wollen gleichzeitig zwei Bahnen berechnen, um sie nachher im Newtonverfahren vergleichen zu können. Dazu brauchen wir zwei Wege q, p, dq, dp (auf denen gerechnet wird) und zwei Startwerte S1, S2.
*/
struct Lsng{
	R3 q1, q2;
	R3 p1, p2;
	R3 dq1, dq2;
	R3 dp1, dp2;
	R3 S1, S2; 	// Startwerte p(0) für die Schüsse
};

const int T = 10;			// Rechenzeitintervallbreite
const int n = 1000;			// Anzahl der Schüsse im Shooting-Verfahren

const double wdt = 0.001;	// Wunsch-Schrittweite

const int nt = (int) T / wdt;	// Rechenschritte
const double dt = T /((double)nt);		// Tatsächliche, auf das Intervall angepasste Schrittweite

const double tol = 0.001;	// Toleranz für die Abweichung am Ende des Rechenintervalls

/*
 Initialisiere die Systemgleichungen.
*/
const double Gravk = 1.0; 				// Gravitationskonstante
const double MEd = 3.0 * pow(10,9); 		// Abstand Erde-Mond
const double mE = 1.0; 					// Masse Erde
const double mM = 0.1; 					// Masse Mond
const double mS = 0.01; 				// Masse Schusskörper
const double rM = 0.1;					// Radius Mond
const double rE = 0.1;					// Radius Erde
const R3 locE(0.0, 0.0, 0.0);			// Ort Erdezentrum
R3 locM(0.0, 0.0, MEd);				// Ort Mondzentrum
R3 x1; 									//ziel

double moonPhase = 0.0;					//Anfangsphase der Mond um die Erde in rad

double moonRadA= rM;
double moonRadB= 0.9 * rM;

R3 moonSurface(0.0, 0.0, rM); //surface of the moon in to moon coord. system 

void updateMoon()
{
    moonPhase += (moonPhase)*180./M_PI; //degree

    locM.x = moonRadA*cos(moonPhase);
    locM.y = moonRadB*sin(moonPhase);
    locM.z = 0.0;

    return;
}
void update_target()
{
	x1 = locM - moonSurface;
}
