#include "ModelARX.h"

ModelARX::ModelARX(const std::vector<double>& WspA, const std::vector<double>& WspB, int k, double z)
    : WspWektA(WspA), WspWektB(WspB), OpoznienieTransportowe(k), zaklocenie(z) {

    krokA = (int)WspWektA.size();
    krokB = (int)WspWektB.size();

    for (int i = 0; i < WspWektB.size() + OpoznienieTransportowe; ++i) {
        SygnalWe.push_back(0.0);
    }

    for (int i = 0; i < WspWektA.size(); ++i) {
        SygnalWy.push_back(PoprzedniSygWy);
    }
}

void ModelARX::SetWspWekA(const std::vector<double>& WspA) {
    WspWektA = WspA;
    krokA = (int)WspWektA.size();
    if (SygnalWy.size() < krokA) {
        SygnalWy.resize(krokA, 0.0);
    }
}

void ModelARX::SetWspWekB(const std::vector<double>& WspB) {
    WspWektB = WspB;
    krokB = (int)WspWektB.size();
    if (SygnalWe.size() < krokB + OpoznienieTransportowe) {
        SygnalWe.resize(krokB + OpoznienieTransportowe, 0.0);
    }
}

void ModelARX::SetOpoznienie(int k) {
    OpoznienieTransportowe = k;
    if (SygnalWe.size() < krokB + OpoznienieTransportowe) {
        SygnalWe.resize(krokB + OpoznienieTransportowe, 0.0);
    }
}

double ModelARX::ObliczeniaARX(double zaklocenie) {
    for (int i = (int)SygnalWe.size() - 1; i > 0; --i) {
        SygnalWe[i] = SygnalWe[i - 1];
    }

    SygnalWe.pop_back();
    SygnalWe.push_front(AktualnySygnal);

    double WspBObl = 0.0;
    double WspAObl = 0.0;
    double y = 0.0;

    for (int i = 0; i < WspWektB.size(); ++i) {
        int index = i + OpoznienieTransportowe;
        if (index < SygnalWe.size()) {
            WspBObl += WspWektB[i] * SygnalWe[index];
        }
    }

    for (int i = 0; i < WspWektA.size(); ++i) {
        if (i < SygnalWy.size()) {
            WspAObl += WspWektA[i] * SygnalWy[i];
        }
    }

    y = WspBObl - WspAObl + zaklocenie;

    for (int i = (int)SygnalWy.size() - 1; i > 0; --i) {
        SygnalWy[i] = SygnalWy[i - 1];
    }

    SygnalWy.pop_back();
    SygnalWy.push_front(y);

    return y;
}

double ModelARX::symuluj(double SygWe_, double zaklocenie_) {
    AktualnySygnal = SygWe_;
    return ObliczeniaARX(zaklocenie_);
}
