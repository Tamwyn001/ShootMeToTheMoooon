
double T(double t, Lsng* L) {
    return L->p * L->p / (2 * mS);
}


double V(double t, Lsng* L) {
    return Gravk * (mS * mE / pnorm(2, L->q - locE) + mS * mM / pnorm(2, L->q - locM));
}


void F(double t, Lsng* L) {
    L->dp = -L->p / mS;
    L->dq = // ......... d/dq V(t, q);
}