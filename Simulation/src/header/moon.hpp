#include "R3.hpp"


#define _USE_MATH_DEFINES //for M_PI
#include <math.h>
//cant find M_PI...
# define M_PI           3.14159265358979323846  /* pi */


#define DELTA_ANGLE = 0.001; //angle in degree to add to the moon phase each time step

double moonRadA= rM;
double moonRadB= 0.9 * rM;

void updateMoon(R3* moonLoc, double* moonPhase)
{
    *moonPhase += (*moonPhase)*180./M_PI; //degree

    moonLoc->x = moonRadA*cos(*moonPhase);
    moonLoc->y = moonRadB*sin(*moonPhase);
    moonLoc->z = 0;

    return;
}