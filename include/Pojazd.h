#pragma once
#include <string>

class Pojazd {
public:
    std::string model;
    std::string marka;

    Pojazd(std::string marka, std::string model);

    bool pasuje(const std::string& wzorzecModelu) const;
};
