double check(Lsng* L, int k) {
    switch (k) {
        case 1:
            return pnorm(2, L->q1 - x1);
        case 2:
            return pnorm(2, L->q2 - x1);
        default:
            return 0;
    }
}

/*
    Nullstellenverfahren für die Fixpunktiteration.
*/
void newtonstep(Lsng* L) {
    R3 x1 = L->S1;
    R3 x2 = L->S2;

    // Newton Methode um neuen Startwert S1 zu bestimmen (S2 wird zu altem S1)
    L->S1 = x1 - (x1 - x2) / (check(L, 1) - check(L, 2)) * check(L, 1);
    L->S2 = x1;
}


/*
    Definiere das Euler-Verfahren.
*/
void eulerstep(double t, Lsng* L, int k) {
    switch (k) {
        case 1:
            L->q1 = L->q1 + L->dq1 * dt;
            L->p1 = L->p1 + L->dp1 * dt;
            break;
        case 2:
            L->q2 = L->q2 + L->dq2 * dt;
            L->p2 = L->p2 + L->dp2 * dt;
            break;
        default:
            break;
    }
}

/*
    Definiere das RK4-Verfahren. Nutze dazu das Butcher Schema:
    0   |
    1/2 | 1/2
    1/2 | 0   1/2
    1   | 0   0   1
    -----------------
        | 1/6 1/3 1/3 1/6


    KÖNNTE NICHT SOFORT FUNKTIONIEREN, MÖGLICHERWEISE ANPASSUNGEN NÖTIG!!
*/
double RK4Koeff[4][4] = {
    {0, 0, 0, 0},
    {0.5, 0.5, 0, 0},
    {0.5, 0, 0.5, 0},
    {1, 0, 0, 1}
};
double RK4KoeffSum[4] = {0.16666667, 0.3333334, 0.3333334, 0.16666667};

void rk4step(double t, Lsng* L, void (*F)(double, Lsng*)) {
    // 
}


/*
    Definiere das Schießverfahren.
*/
void shooting(double t, Lsng* L, Lsng* L0, double* c) {
    // Berechne die Lösung des Anfangswertproblems
    for (int i = 0; i < nt; i++) {
        F(i * dt, L, 1);
        eulerstep(i * dt, L, 1);
        eulerstep(i * dt, L, 2);
    }

    // Berechne die Korrektheit des Endwertes
    *c = fmax(check(L, 1), check(L, 2));
}