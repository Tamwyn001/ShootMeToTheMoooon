double dVsum(Lsng* L) {
    double sum = 0;
    sum += mE * 2 / (pow(pnorm(2, locE - L->q1), 3)) * pnorm(1, locE - L->q1);
    sum += mM * 2 / (pow(pnorm(2, locM - L->q1), 3)) * pnorm(1, locM - L->q1);
}


void F(double t, Lsng* L, int k) {
    switch (k) {
        case 1:
            L->dp1 = (L->p1) * (-1) / mS;
            L->dq1 = dVsum(L) * Gravk * mS; // ......... d/dq V(t, q);
            break;
        case 2:
            L->dp2 = (L->p2) * (-1) / mS;
            L->dq2 = dVsum(L) * Gravk * mS; // ......... d/dq V(t, q);
            break;
        default:
            break;
    }
}