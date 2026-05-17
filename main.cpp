#include <iostream>
#include "BazaUslug.h"
#include "Kosztorys.h"
#include "UslugaProsta.h"
#include "UslugaZlozna.h"
#include "Czesc.h"
#include "StanowiskoNaprawcze.h"
#include "Pojazd.h"

int main() {
    BazaUslug baza;
    auto kosztorys = std::make_shared<Kosztorys>();

    baza.dodajDoBazy(std::make_shared<UslugaProsta>("Wymiana oleju", 100.0f, "Toyota Corolla"));

    auto uslugi = baza.pobierzDlaModelu("Toyota Corolla");
    if(!uslugi.empty()) {
        kosztorys->dodajUsluge(uslugi[0]);
    }

    auto nowaUsluga = std::make_shared<UslugaProsta>("Usluga niestandardowa", 150.0f);
    nowaUsluga->dodajCzesc(Czesc("Tarcze hamulcowe", "Bosch", 299.0f, 2));
    nowaUsluga->zapiszWBazie(baza);
    kosztorys->dodajUsluge(nowaUsluga);

    kosztorys->ustawRabat(10);

    std::cout << "Koszt po rabacie: " << kosztorys->obliczKoszt() << " zl\n";

    return 0;
}
