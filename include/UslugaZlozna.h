#pragma once
#include "SkladnikUslugi.h"
#include <vector>
#include <string>
#include <memory>

class UslugaZlozna : public SkladnikUslugi {
private:
    std::string nazwa;
    std::vector<std::shared_ptr<SkladnikUslugi>> skladniki;

public:
    UslugaZlozna(std::string nazwa);

    void dodajSkladnik(std::shared_ptr<SkladnikUslugi> skladnik);
    void usunSkladnik(std::shared_ptr<SkladnikUslugi> skladnik);

    float obliczKoszt(std::shared_ptr<Pojazd> pojazd = nullptr) override;
    std::string getNazwa() const override;
};
