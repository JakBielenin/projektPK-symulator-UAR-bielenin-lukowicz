#include "RejestrWynikow.h"
void RejestrWynikow::AddWyniki(double wynik) {
    if (wynik != NULL) {
        dane.push_back(wynik);
    }
}
void RejestrWynikow::ExportDoPliku(std::string sciezka) {
    std::fstream plik;
    plik.open(sciezka, std::ios::out);
    if (plik.good()) {
        for (int i = 0; i < dane.size(); i++) {
            plik << dane[i] << "\n";
        }
        plik.flush();
    }
    plik.close();
}
void RejestrWynikow::CzyscRejestr() {
    dane.clear();
}
std::vector<double> RejestrWynikow::GetWyniki() {
    return dane;
}
