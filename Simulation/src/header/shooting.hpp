double check(Lsng* L) {
    return pnorm(2, L->q - x1);
}

void correct(Lsng* L0) {
    L0->p = // Wie genau korrigieren?
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
    R3 k[4], sum_aij_kj;
    Lsng gL = *L;

    for (int pi = 0; pi < p; pi++) {
        for (int kj = 0; kj < 4; kj++) {
            F(t + RK4Koeff[kj][0] * h, &gL);
            k[kj] = gL.dq[pi];

            for (int skj = 0; skj < kj; skj++) {
                sum_aij_kj = k[skj] * RK4Koeff[kj][skj];
            }

            for (int spi = 0; spi < p; spi++) {
                gL.u[spi] = L->q[spi] + sum_aij_kj * h;
            }
        }

        for (int kj = 0; kj < 4; kj++) {
            L->q[pi] += k[kj] * h * RK4KoeffSum[kj];
        }
    }
}


void shooting(double t, Lsng* L, Lsng* L0, double* c) {
    // Berechne die Lösung des Anfangswertproblems
    for (int i = 0; i < nt; i++) {
        rk4step(i * dt, L, F);
    }

    // Berechne die Korrektheit des Endwertes
    *c = check(L);
}