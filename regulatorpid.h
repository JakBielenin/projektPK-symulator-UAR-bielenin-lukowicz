#pragma once
#include <QDebug>
class RegulatorPID
{
private:
    double Tp, Tl, Td;
    double up, ul, ud;
    double SumaPID = 0.0;
    double WartoscUchybu = 0.0;
    double SumaWartosciUchybu = 0.0;
    double PoprzedniaWartoscUchybu = 0.0;
public:
    RegulatorPID(double tp = 0.0, double tl = 0.0, double td = 0.0);
    void SetP(double p);
    void SetL(double l);
    void SetD(double d);

    double GetP();
    double GetI();
    double GetD();

    void ResetUl();
    void ResetUd();

    double ObliczeniaRegulatora();
    double symuluj(double uch);

};
