#include "UslugaProsta.h"
#include "BazaUslug.h"
#include "Pojazd.h"

UslugaProsta::UslugaProsta(std::string nazwa, float cena, std::string model)
    : nazwa(std::move(nazwa)), cena_bazowa_robocizny(cena),
      model(std::move(model)), szacowany_czas_min(0) {}

void UslugaProsta::dodajCzesc(const Czesc& czesc) {
    wymagane_czesci[czesc] += czesc.ilosc;
}

void UslugaProsta::ustawCzasNaprawy(int minuty) {
    szacowany_czas_min = minuty;
}

void UslugaProsta::dodajStanowisko(std::shared_ptr<StanowiskoNaprawcze> stanowisko) {
    stanowiska.push_back(std::move(stanowisko));
}

void UslugaProsta::ustawCeneDlaModelu(const std::string& m, float cena) {
    ceny_dla_modeli[m] = cena;
}

float UslugaProsta::obliczKoszt(std::shared_ptr<Pojazd> pojazd) {
    float robocizna = cena_bazowa_robocizny;
    if (pojazd) {
        auto it = ceny_dla_modeli.find(pojazd->model);
        if (it != ceny_dla_modeli.end()) {
            robocizna = it->second;
        }
    }
    float suma = robocizna;
    for (const auto& para : wymagane_czesci) {
        suma += para.first.cena_bazowa * para.second;
    }
    return suma;
}

std::string UslugaProsta::getNazwa() const {
    return nazwa;
}

std::string UslugaProsta::getModel() const {
    return model;
}

int UslugaProsta::getSzacowanyCzas() const {
    return szacowany_czas_min;
}

void UslugaProsta::zapiszWBazie(BazaUslug& baza) {
    baza.dodajDoBazy(shared_from_this());
}
