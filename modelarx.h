#pragma once

#include <vector>
#include <deque>
#include <QDebug>
#include <cmath>

class ModelARX
{
    std::vector<double> WspWektA = {};
    std::vector<double> WspWektB = {};
    int OpoznienieTransportowe = 0;
    std::deque<double> SygnalWe = {};
    std::deque<double> SygnalWy = {};
    double WspBObl;
    double WspAObl;
    double zaklocenie = 0.0;
    int krokA, krokB;
    double AktualnySygnal = 0.0;
    double wynik;
    double PoprzedniSygWy = 0.0;
public:
    ModelARX(const std::vector<double>& WspA = {0.0}, const std::vector<double>& WspB = {0.0}, int k = 0, double z = 0);
    void SetWspWekA(const std::vector<double>& WspA);
    void SetWspWekB(const std::vector<double>& WspB);
    void SetOpoznienie(int k);
    double ObliczeniaARX(double zaklocenie);
    double symuluj(double SygWe_, double zaklocenie_);

};

//#endif // MODELARX_H

