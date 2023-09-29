
double kinE(double t, Lsng* L) {
    return scpr(L->p,L->p) / (2 * mS);
}


double potE(double t, Lsng* L) {
    return Gravk * (mS * mE / pnorm(2, L->q - locE) + mS * mM / pnorm(2, L->q - locM));
}


void F(double t, Lsng* L) {
    L->dp = (L->p) * (-1) / mS;
    // L->dq = // ......... d/dq V(t, q);
}