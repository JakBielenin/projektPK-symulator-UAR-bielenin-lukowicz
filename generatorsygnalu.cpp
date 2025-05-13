#include "GeneratorSygnalu.h"
#include <math.h>
GeneratorSygnalu::GeneratorSygnalu() {
}
double GeneratorSygnalu::GenerujSygnal() {

    switch (typ)
    {
    case TypSygnalu::jednostkowy:
        return amplituda;
        break;
    case TypSygnalu::prostokatny:{
        double krok_ = krok;
        double modValue = fmod(krok_, dlugosc*100);
        double wypelnieniee = (wypelnienie) * dlugosc;

        if (modValue < wypelnieniee) {
            tmp = amplituda;
        }
        else {
            tmp = 0;
        }
    }
        break;
    case TypSygnalu::sinusoidalny:
        tmp = sin(krok/dlugosc*4 * PI/180)*amplituda;

        break;
    default:
        return 0;
        break;
    }
    krok++;
    return tmp;
}
void GeneratorSygnalu::SetTypSygnalu(TypSygnalu nowy) { typ = nowy; }
void GeneratorSygnalu::SetAmplituda(double nowa) { amplituda = nowa; }
void GeneratorSygnalu::SetDlugosc(double nowa) { dlugosc = nowa; }
void GeneratorSygnalu::SetWypelnienie(int nowa) { wypelnienie = nowa; }
