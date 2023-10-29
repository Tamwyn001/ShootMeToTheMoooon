R3 dVsum(int k, Lsng* L) {
    R3 sum = R3(0.0, 0.0, 0.0);
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

    return sum;
}


//f_i are helpers for the function F
R3 f_s(R3* s){ //here are the s = (sq,s2,s3) the function defined in paper where s = q1
    R3 result = R3(0.0,0.0,0.0);

    result.x = s->x*sin(s->y)*cos(s->z) - moonRadA*cos(moonPhase);
    result.y = s->x*sin(s->y)*sin(s->z) - moonRadB*sin(moonPhase);
    
    return result;
}

R3 f_1(R3* s)
{
    R3 result = R3(0.0,0.0,0.0);

    result.x = sin(s->x)*cos(s->z);
    result.y = sin(s->x)*sin(s->z);

    return result;
}

R3 f_2(R3* s)
{
    R3 result = R3(0.0,0.0,0.0);

    result.x = s->x*cos(s->y)*cos(s->z);
    result.y = s->x*cos(s->y)*sin(s->z);

    return result;
}
R3 f_3(R3* s)
{
    R3 result = R3(0.0,0.0,0.0);

    result.x = -s->x*sin(s->y)*sin(s->z);
    result.y = s->x*sin(s->y)*cos(s->z);

    return result;
}


//Die Funktion F besitzt zwei komeponenten. Die erste ist die Ortsbeschreibung und die zweite die Geschwindigkeit.
void F(double t, Lsng* L, int k)
 {
    Lsng Ls = *L;
    switch (k)
    {
        case 1:
        {
                //   d/db H:
            L->dq1.x = Ls.p1.x * 1/mS;
            L->dq1.y = Ls.p1.y/(mS*pow(Ls.q1.x, 2));
            L->dq1.z = Ls.p1.z/(mS*pow(Ls.q1.x, 2)*sin(Ls.q1.y));
            std::cout<<"dq1: "<<L->dq1.x<<", "<<L->dq1.y<<", "<<L->dq1.z<<std::endl;

            //   d/da H: 
            const double dqelem1 = (-1.)*mM/pow(pnorm(2, f_s(&Ls.q1)), 3);
            L->dp1.x = -mE/(pow(Ls.q1.x, 2)) - dqelem1 * scpr(f_s(&Ls.q1), f_1(&Ls.q1)); 
            L->dp1.x = dqelem1 * scpr(f_s(&Ls.q1), f_2(&Ls.q1));
            L->dp1.z = dqelem1 * scpr(f_s(&Ls.q1), f_3(&Ls.q1));


            L->dp1 = Ls.dp1 *Gravk * mS ;

            L->dp1.x += 1/(2*mS) * (-2)/pow(Ls.p1.x, 3) * ( pow(Ls.p1.y, 2) + pow(Ls.p1.z, 2)/(sin(Ls.q1.y)));
            L->dp1.y += 1/(2*mS) * pow(Ls.p1.z, 2)/pow(Ls.q1.x, 2) * (-2*cos(Ls.q1.y))/pow(sin(Ls.q1.y), 3); // IST ES WRKL sin^3, unscharfe Bild vom Tafel??
            L->dp1.z += 0;
        }
            break;
        case 2:
        {
                //   d/db H:
            L->dq2.x =  Ls.p2.x * 1/mS;
            L->dq2.y = Ls.p2.y/(mS*pow(Ls.q2.x, 2));
            L->dq2.z = Ls.p2.z/(mS*pow(Ls.q2.x, 2)*sin(Ls.q2.y));

            //   d/da H: 
            const double dqelem2 = (-1.)*mM/pow(pnorm(2, f_s(&Ls.q2)), 3);
            L->dp2.x = -mE/(pow(Ls.q2.x, 2)) - dqelem2 * scpr(f_s(&Ls.q2), f_1(&Ls.q2));
            L->dp2.x = dqelem2 * scpr(f_s(&Ls.q2), f_2(&Ls.q2));
            L->dp2.z = dqelem2 * scpr(f_s(&Ls.q2), f_3(&Ls.q2));


            L->dp2 = Ls.dp2 *Gravk * mS ;

            L->dp2.x += 1/(2*mS) * (-2)/pow(Ls.p2.x, 3) * ( pow(Ls.p2.y, 2) + pow(Ls.p2.z, 2)/(sin(Ls.q2.y)));
            L->dp2.y += 1/(2*mS) * pow(Ls.p2.z, 2)/pow(Ls.q2.x, 2) * (-2*cos(Ls.q2.y))/pow(sin(Ls.q2.y), 3); // IST ES WRKL sin^3, unscharfe Bild vom Tafel??
            L->dp2.z += 0;
            break;
        }
        default:
            break;
    }
    
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