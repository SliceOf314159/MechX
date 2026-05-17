#include "Czesc.h"
#include <algorithm>

Czesc::Czesc(std::string nazwa, std::string producent, float cena, int ilosc,
             std::vector<std::string> modele)
    : nazwa(std::move(nazwa)), producent(std::move(producent)),
      cena_bazowa(cena), ilosc(ilosc), modele(std::move(modele)) {}

bool Czesc::operator<(const Czesc& inna) const {
    if (nazwa != inna.nazwa) return nazwa < inna.nazwa;
    return producent < inna.producent;
}

bool Czesc::czyUniwersalna() const {
    return modele.empty();
}

bool Czesc::pasujeDo(const std::string& model) const {
    if (czyUniwersalna()) return true;
    return std::find(modele.begin(), modele.end(), model) != modele.end();
}
