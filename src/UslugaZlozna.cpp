#include "UslugaZlozna.h"
#include "Pojazd.h"
#include <algorithm>

UslugaZlozna::UslugaZlozna(std::string nazwa)
    : nazwa(std::move(nazwa)) {}

void UslugaZlozna::dodajSkladnik(std::shared_ptr<SkladnikUslugi> skladnik) {
    skladniki.push_back(std::move(skladnik));
}

void UslugaZlozna::usunSkladnik(std::shared_ptr<SkladnikUslugi> skladnik) {
    skladniki.erase(std::remove(skladniki.begin(), skladniki.end(), skladnik), skladniki.end());
}

float UslugaZlozna::obliczKoszt(std::shared_ptr<Pojazd> pojazd) {
    float suma = 0.0f;
    for (const auto& s : skladniki) {
        suma += s->obliczKoszt(pojazd);
    }
    return suma;
}

std::string UslugaZlozna::getNazwa() const {
    return nazwa;
}
