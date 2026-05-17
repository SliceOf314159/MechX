#include "BazaUslug.h"
#include "UslugaProsta.h"

void BazaUslug::dodajDoBazy(std::shared_ptr<UslugaProsta> usluga) {
    dane.push_back(std::move(usluga));
}

std::vector<std::shared_ptr<UslugaProsta>> BazaUslug::pobierzDlaModelu(const std::string& model) {
    std::vector<std::shared_ptr<UslugaProsta>> wynik;
    for (const auto& u : dane) {
        if (u->getModel().empty() || u->getModel() == model) {
            wynik.push_back(u);
        }
    }
    return wynik;
}
