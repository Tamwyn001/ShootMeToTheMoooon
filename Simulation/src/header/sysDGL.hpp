
/*
double kinE(double t, Lsng* L) {
    return scpr(L->p,L->p) / (2 * mS);
}


double potE(double t, Lsng* L) {
    return Gravk * (mS * mE / pnorm(2, L->q - locE) + mS * mM / pnorm(2, L->q - locM));
}
*/


void F(double t, Lsng* L, int k) {
    switch (k) {
        case 1:
            L->dp1 = (L->p1) * (-1) / mS;
            // L->dq1 = // ......... d/dq V(t, q);
            break;
        case 2:
            L->dp2 = (L->p2) * (-1) / mS;
            // L->dq2 = // ......... d/dq V(t, q);
            break;
        default:
            break;
    }
}