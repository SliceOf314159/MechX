#pragma once
#include <string>
#include <memory>

class Pojazd;

class SkladnikUslugi {
public:
    virtual ~SkladnikUslugi() = default;

    virtual float obliczKoszt(std::shared_ptr<Pojazd> pojazd = nullptr) = 0;
    virtual std::string getNazwa() const = 0;
};
