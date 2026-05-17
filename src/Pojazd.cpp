#include "Pojazd.h"

Pojazd::Pojazd(std::string marka, std::string model)
    : marka(std::move(marka)), model(std::move(model)) {}

bool Pojazd::pasuje(const std::string& wzorzecModelu) const {
    if (wzorzecModelu.empty()) return true;
    return model == wzorzecModelu || marka == wzorzecModelu;
}
