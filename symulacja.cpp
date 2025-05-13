#include "symulacja.h"

Symulacja::Symulacja() {
    std::normal_distribution<double> gausDist_new(0.0, 0.01);
    gausDist = gausDist_new;
}

RegulatorPID& Symulacja::getRegulator() { return regulator; }
ModelARX& Symulacja::getModel() { return model; }
double Symulacja::GetWartoscRegulowana() {return loopback;}
double Symulacja::GetUchyb() {return GetWartoscZadana() - GetWartoscRegulowana();}
double Symulacja::GetSterowanie() {return regulator.symuluj(GetUchyb());}
double Symulacja::GetWartoscZadana() {return generator.GenerujSygnal();}

void Symulacja::SetSygnal(TypSygnalu s, double amplituda, double dlugosc, int wypelnienie) {
    generator.SetTypSygnalu(s);
    generator.SetAmplituda(amplituda);
    generator.SetDlugosc(dlugosc);
    generator.SetWypelnienie(wypelnienie);
}

void Symulacja::SetRegulatorPID(double tp, double tl, double td)
{
    regulator.SetP(tp);
    regulator.SetL(tl);
    regulator.SetD(td);
}
void Symulacja::SetModelARX(std::vector<double> WspA, std::vector<double> WspB, int k)
{
    model.SetWspWekA(WspA);
    model.SetWspWekB(WspB);
    model.SetOpoznienie(k);
}
void Symulacja::SetWartOdchStd(bool wos) {
    WartOdchStd = wos;
}
double Symulacja::KrokSymulacji() {
    if (WartOdchStd) zaklocenie = gausDist(gen);
    else zaklocenie = 0;

    sygnal = GetWartoscZadana();
    sygnal = sygnal - loopback;

    double sygnalPID = regulator.symuluj(sygnal);
    double sygnalARX = model.symuluj(sygnalPID, zaklocenie);
    double wynik = sygnalARX;

    loopback = sygnalARX;
    rejestr.AddWyniki(wynik);
    return wynik;
}

void Symulacja::ZapiszSymulacje(std::string plik) {
    rejestr.ExportDoPliku(plik);
}




