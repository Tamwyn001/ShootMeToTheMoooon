double check(Lsng* L) {
    return pnorm(2, L->q - x1);
}

void correct(Lsng* L0) {
    L0->p = // Wie genau korrigieren?
}

void euler(double t, Lsng* L) {
    L->q = L->q + L->dq * dt;
    L->p = L->p + L->dp * dt;
}

void shooting(double t, Lsng* L, Lsng* L0, double* c) {
    // Berechne die Lösung des Anfangswertproblems
    for (int i = 0; i < nt; i++) {
        euler(i * dt, L);
    }

    // Berechne die Korrektheit des Endwertes
    *c = check(L);
}