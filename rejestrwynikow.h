#pragma once
#include <vector>
#include <string>
#include <fstream>
class RejestrWynikow
{
    std::vector<double> dane;

public:
    void AddWyniki(double dane);
    void CzyscRejestr();
    void ExportDoPliku(std::string sciezka);
    std::vector<double> GetWyniki();
};

