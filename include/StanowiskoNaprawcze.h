#pragma once
#include <string>

class StanowiskoNaprawcze {
public:
    int id;
    std::string nazwa;
    bool dostepne;

    StanowiskoNaprawcze(int id, std::string nazwa);

    void ustawDostepnosc(bool dostepne);
    bool czyDostepne() const;
};
