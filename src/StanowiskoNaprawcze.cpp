#include "StanowiskoNaprawcze.h"

StanowiskoNaprawcze::StanowiskoNaprawcze(int id, std::string nazwa)
    : id(id), nazwa(std::move(nazwa)), dostepne(true) {}

void StanowiskoNaprawcze::ustawDostepnosc(bool d) {
    dostepne = d;
}

bool StanowiskoNaprawcze::czyDostepne() const {
    return dostepne;
}
