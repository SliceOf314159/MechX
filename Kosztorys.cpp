#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>


class Pojazd {
public:
    std::string model;
    Pojazd(std::string m) : model(std::move(m)) {}
};

class Czesc {
public:
    std::string nazwa;
    std::string producent;
    float cena_bazowa;
    int ilosc;

    Czesc(std::string n, std::string p, float cena, int il)
        : nazwa(std::move(n)), producent(std::move(p)), cena_bazowa(cena), ilosc(il) {}

    bool operator<(const Czesc& inna) const {
        if (nazwa != inna.nazwa) return nazwa < inna.nazwa;
        return producent < inna.producent;
    }
};


class SkladnikUslugi {
public:
    virtual ~SkladnikUslugi() = default;

    virtual float obliczKoszt(std::shared_ptr<Pojazd> pojazd = nullptr) = 0;
    virtual std::string getNazwa() const = 0;
};

class UslugaProsta;
class BazaUslug {
private:
    std::vector<std::shared_ptr<UslugaProsta>> dane;
public:
    void dodajDoBazy(std::shared_ptr<UslugaProsta> u) {
        dane.push_back(u);
    }

    std::vector<std::shared_ptr<UslugaProsta>> pobierzDlaModelu(const std::string& model);
};

class UslugaProsta : public SkladnikUslugi, public std::enable_shared_from_this<UslugaProsta> {
private:
    std::string nazwa;
    std::string model;
    float cena_bazowa_robocizny;
    std::map<Czesc, int> wymagane_czesci;

public:
    UslugaProsta(std::string n, float cena, std::string m = "")
        : nazwa(std::move(n)), cena_bazowa_robocizny(cena), model(std::move(m)) {}

    void dodajCzesc(const Czesc& czesc) {
        wymagane_czesci[czesc] += czesc.ilosc;
    }

    float obliczKoszt(std::shared_ptr<Pojazd> pojazd = nullptr) override {
        float suma = cena_bazowa_robocizny;
        for (const auto& para : wymagane_czesci) {
            suma += para.first.cena_bazowa * para.second;
        }
        return suma;
    }

    std::string getNazwa() const override {
        return nazwa;
    }

    std::string getModel() const {
        return model;
    }

    void zapiszWBazie(BazaUslug& baza) {
        baza.dodajDoBazy(shared_from_this());
    }
};

std::vector<std::shared_ptr<UslugaProsta>> BazaUslug::pobierzDlaModelu(const std::string& model) {
    std::vector<std::shared_ptr<UslugaProsta>> wynik;
    for (const auto& u : dane) {
        if (u->getModel() == model) {
            wynik.push_back(u);
        }
    }
    return wynik;
}


class Kosztorys {
private:
    int kosztorys_id;
    float koszt_calkowity;
    float rabat_procentowy;
    std::vector<std::shared_ptr<SkladnikUslugi>> skladnikiUslugi;

public:
    Kosztorys() : kosztorys_id(0), koszt_calkowity(0.0f), rabat_procentowy(0.0f) {}

    void ustawRabat(float rabat) {
        rabat_procentowy = rabat;
    }

    void dodajUsluge(std::shared_ptr<SkladnikUslugi> skladnik) {
        if (skladnik) {
            skladnikiUslugi.push_back(skladnik);
        }
    }

    float obliczKoszt(std::shared_ptr<Pojazd> pojazd = nullptr) {
        float suma = 0.0f;
        for (const auto& skladnik : skladnikiUslugi) {
            suma += skladnik->obliczKoszt(pojazd);
        }
        if (rabat_procentowy > 0.0f) {
            suma -= suma * (rabat_procentowy / 100.0f);
        }
        koszt_calkowity = suma;
        return koszt_calkowity;
    }
};


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