#include "Kosztorys.h"
#include "Pojazd.h"

Kosztorys::Kosztorys()
    : kosztorys_id(0), koszt_calkowity(0.0f), rabat_procentowy(0.0f) {}

void Kosztorys::ustawRabat(float rabat) {
    rabat_procentowy = rabat;
}

void Kosztorys::dodajUsluge(std::shared_ptr<SkladnikUslugi> skladnik) {
    if (skladnik) {
        skladnikiUslugi.push_back(std::move(skladnik));
    }
}

float Kosztorys::obliczKoszt(std::shared_ptr<Pojazd> pojazd) {
    float suma = 0.0f;
    for (const auto& skladnik : skladnikiUslugi) {
        suma += skladnik->obliczKoszt(pojazd);
    }
    if (rabat_procentowy > 0.0f) {
        suma -= suma * (rabat_procentowy / 100.0f);
    }
    koszt_calkowity = suma;
    return koszt_calkowity;
}
