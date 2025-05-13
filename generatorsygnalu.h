#pragma once
#include <vector>
#include <QDebug>
enum class TypSygnalu
{
    jednostkowy,
    prostokatny,
    sinusoidalny,
};


class GeneratorSygnalu
{
    TypSygnalu typ;
    double amplituda;
    double dlugosc;
    int wypelnienie;
    const double PI = 3.14159265358979323846;
    double krok;
    double tmp;
public:
    GeneratorSygnalu();
    double GenerujSygnal();
    void SetTypSygnalu(TypSygnalu nowy);
    void SetAmplituda(double nowa);
    void SetDlugosc(double nowa);
    void SetWypelnienie(int nowa);

};

