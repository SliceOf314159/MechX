#pragma once
#include <vector>
#include <memory>
#include <string>

class UslugaProsta;

class BazaUslug {
private:
    std::vector<std::shared_ptr<UslugaProsta>> dane;

public:
    void dodajDoBazy(std::shared_ptr<UslugaProsta> usluga);
    std::vector<std::shared_ptr<UslugaProsta>> pobierzDlaModelu(const std::string& model);
};
