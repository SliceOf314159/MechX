#pragma once
#include "SkladnikUslugi.h"
#include <vector>
#include <memory>

class Pojazd;

class Kosztorys {
private:
    int kosztorys_id;
    float koszt_calkowity;
    float rabat_procentowy;
    std::vector<std::shared_ptr<SkladnikUslugi>> skladnikiUslugi;

public:
    Kosztorys();

    void ustawRabat(float rabat);
    void dodajUsluge(std::shared_ptr<SkladnikUslugi> skladnik);
    float obliczKoszt(std::shared_ptr<Pojazd> pojazd = nullptr);
};
