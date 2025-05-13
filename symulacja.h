#ifndef SYMULACJA_H
#define SYMULACJA_H

#include <random>
#include <vector>
#include <QDebug>
#include "ModelARX.h"
#include "regulatorPID.h"
#include "RejestrWynikow.h"
#include "GeneratorSygnalu.h"

class Symulacja
{
private:
    ModelARX model;
    RegulatorPID regulator;
    RejestrWynikow rejestr;
    int Czaskroku;
    GeneratorSygnalu generator;
    double loopback = 0.0 ;
    double sygnal;
    std::mt19937 gen;
    std::normal_distribution<double> gausDist;
    bool WartOdchStd = false;
    double zaklocenie;
public:
    Symulacja();
    void SetSygnal(TypSygnalu s, double amplituda, double dlugosc, int wypelnienie);
    void SetRegulatorPID(double tp, double tl, double td);
    void SetModelARX(std::vector<double> WspA, std::vector<double> WspB, int k);
    void SetWartOdchStd(bool wos);
    double KrokSymulacji();
    //double GeneratorZaklocenia();
    void ZapiszSymulacje(std::string plik);
    double GetWartoscZadana();
    double GetWartoscRegulowana();
    double GetUchyb();
    double GetSterowanie();
    RegulatorPID& getRegulator();
    ModelARX& getModel();
};
#endif // SYMULACJA_H

