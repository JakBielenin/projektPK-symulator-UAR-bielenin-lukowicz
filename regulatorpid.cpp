#include "RegulatorPID.h"

RegulatorPID::RegulatorPID(double tp, double tl, double td)
    : Tp(tp), Tl(tl), Td(td) {}

void RegulatorPID::SetP(double p) { Tp = p; }
void RegulatorPID::SetL(double l) { Tl = l; }
void RegulatorPID::SetD(double d) { Td = d; }

double RegulatorPID::GetP() { return up; }
double RegulatorPID::GetI() { return ul; }
double RegulatorPID::GetD() { return ud; }

double RegulatorPID::ObliczeniaRegulatora() {
    SumaWartosciUchybu += WartoscUchybu;

    up = Tp * WartoscUchybu;

    if (Tl != 0) { ul = 1.0 / Tl * SumaWartosciUchybu;}
    else {ul = 0.0;}

    ud = Td * (WartoscUchybu - PoprzedniaWartoscUchybu);

    PoprzedniaWartoscUchybu = WartoscUchybu;
    return up + ul + ud;
}

void RegulatorPID::ResetUl() { SumaWartosciUchybu = 0.0; }
void RegulatorPID::ResetUd() { PoprzedniaWartoscUchybu = 0.0; }

double RegulatorPID::symuluj(double uch) {
    WartoscUchybu = uch;
    return ObliczeniaRegulatora();
}
