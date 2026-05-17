#pragma once
#include <string>
#include <vector>

class Czesc {
public:
    std::string nazwa;
    std::string producent;
    float cena_bazowa;
    int ilosc;
    std::vector<std::string> modele;

    Czesc(std::string nazwa, std::string producent, float cena, int ilosc,
          std::vector<std::string> modele = {});

    bool operator<(const Czesc& inna) const;

    bool czyUniwersalna() const;
    bool pasujeDo(const std::string& model) const;
};
