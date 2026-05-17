#pragma once
#include "SkladnikUslugi.h"
#include "Czesc.h"
#include "StanowiskoNaprawcze.h"
#include <map>
#include <vector>
#include <string>
#include <memory>

class BazaUslug;

class UslugaProsta : public SkladnikUslugi, public std::enable_shared_from_this<UslugaProsta> {
private:
    std::string nazwa;
    std::string model;
    float cena_bazowa_robocizny;
    int szacowany_czas_min;
    std::map<Czesc, int> wymagane_czesci;
    std::vector<std::shared_ptr<StanowiskoNaprawcze>> stanowiska;
    std::map<std::string, float> ceny_dla_modeli;

public:
    UslugaProsta(std::string nazwa, float cena, std::string model = "");

    void dodajCzesc(const Czesc& czesc);
    void ustawCzasNaprawy(int minuty);
    void dodajStanowisko(std::shared_ptr<StanowiskoNaprawcze> stanowisko);
    void ustawCeneDlaModelu(const std::string& model, float cena);

    float obliczKoszt(std::shared_ptr<Pojazd> pojazd = nullptr) override;
    std::string getNazwa() const override;
    std::string getModel() const;
    int getSzacowanyCzas() const;

    void zapiszWBazie(BazaUslug& baza);
};
