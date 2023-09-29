double check(Lsng* L) {
    return pnorm(2, L->q - x1);
}

void correct(Lsng* L0) {
    // L0->p = // Wie genau korrigieren?
}

void eulerstep(double t, Lsng* L) {
    L->q = L->q + L->dq * dt;
    L->p = L->p + L->dp * dt;
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


void shooting(double t, Lsng* L, Lsng* L0, double* c) {
    // Berechne die Lösung des Anfangswertproblems
    for (int i = 0; i < nt; i++) {
        rk4step(i * dt, L, F);
    }

    // Berechne die Korrektheit des Endwertes
    *c = check(L);
}