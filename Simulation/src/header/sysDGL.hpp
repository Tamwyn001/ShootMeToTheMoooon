#include "moon.hpp"
#include "R3.hpp"

R3 dVsum(int k, Lsng* L) {
    R3 sum = R3(0, 0, 0);
    switch (k) {
        case 1:
            sum += (locE - L->q1) * mE * 2 / (pow(pnorm(2, locE - L->q1), 3));
            sum += (locM - L->q1) * mM * 2 / (pow(pnorm(2, locM - L->q1), 3));
            break;
        case 2:
            sum += (locE - L->q2) * mE * 2 / (pow(pnorm(2, locE - L->q2), 3));
            sum += (locM - L->q2) * mM * 2 / (pow(pnorm(2, locM - L->q2), 3));
            break;
        default:
            break;
    }
}


//f_i are helpers for the function F
R3 f_s(R3* s, double phase){ //here are the s = (sq,s2,s3) the function defined in paper where s = q1
    R3 result = R3(0.,0.,0.);

    result.x = s->x*sin(s->y)*cos(s->z) - moonRadA*cos(phase);
    result.y = s->x*sin(s->y)*sin(s->z) - moonRadB*sin(phase);
    
    return result;
}

R3 f_1(R3* s, double phase)
{
    R3 result = R3(0.,0.,0.);

    result.x = sin(s->x)*cos(s->z);
    result.y = sin(s->x)*sin(s->z);

    return result;
}

R3 f_2(R3* s, double phase)
{
    R3 result = R3(0.,0.,0.);

    result.x = 
    result.y = 

    return result;
}
R3 f_3(R3* s, double phase)
{
    R3 result = R3(0.,0.,0.);

    result.x = 
    result.y = 

    return result;
}


//Die Funktion F besitzt zwei komeponenten. Die erste ist die Ortsbeschreibung und die zweite die Geschwindigkeit.
void F(double t, Lsng* L, double phase) { //(.. , int k) {
    Lsng Ls = *L;
    
    //   d/db H:
    L->dq1.x =  Ls.p1.x * 1/mS;
    L->dq1.y = Ls.p1.y/(mS*pow(Ls.q1.x, 2));
    L->dq1.z = Ls.p1.z/(mS*pow(Ls.q1.x, 2)*sin(Ls.q1.y));

    //   d/da H: 
    double dqelem = (-1.)*mM/pow(pnorm(2, f_s(&Ls.q1, phase)), 3);
    L->dp1.x = -mE/(pow(Ls.q1.x, 2)) - dqelem * scpr(f_s(&Ls.q1, phase), f_1(&Ls.q1, phase)); //TODO zwei komp nach 1 abblteien
    L->dp1.x = dqelem * scpr(f_s(&Ls.q1, phase), f_2(&Ls.q1, phase));//TODO zwei komp nach 2 abblteien
    L->dp1.z = dqelem * scpr(f_s(&Ls.q1, phase), f_3(&Ls.q1, phase));//TODO zwei komp nach 3 abblteien


    L->dp1 = Ls.dp1 *Gravk * mS ;

    L->dp1.x += 1/(2*mS) * (-2)/pow(Ls.p1.x, 3) * ( pow(Ls.p1.y, 2) + pow(Ls.p1.z, 2)/(sin(Ls.q1.y)));
    L->dp1.y += 1/(2*mS) * pow(Ls.p1.z, 2)/pow(Ls.q1.x, 2) * (-2*cos(Ls.q1.y))/pow(sin(Ls.q1.y), 3); // IST ES WRKL sin^3, unscharfe Bild vom Tafel??
    L->dp1.z += 0;


    

    return;


    // switch (k) {
    //     case 1:
    //         L->dp1 = (L->p1) * (-1) / mS;
    //         L->dq1 = dVsum(k, L) * Gravk * mS; // ......... d/dq V(t, q);
    //         break;
    //     case 2:
    //         L->dp2 = (L->p2) * (-1) / mS;
    //         L->dq2 = dVsum(k, L) * Gravk * mS; // ......... d/dq V(t, q);
    //         break;
    //     default:
    //         break;
    // }
}