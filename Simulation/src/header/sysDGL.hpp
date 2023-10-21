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


void F(double t, Lsng* L, int k) {
    switch (k) {
        case 1:
            L->dp1 = (L->p1) * (-1) / mS;
            L->dq1 = dVsum(k, L) * Gravk * mS; // ......... d/dq V(t, q);
            break;
        case 2:
            L->dp2 = (L->p2) * (-1) / mS;
            L->dq2 = dVsum(k, L) * Gravk * mS; // ......... d/dq V(t, q);
            break;
        default:
            break;
    }
}