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

    Czesc(std::string n, std::string p, float cena) 
        : nazwa(std::move(n)), producent(std::move(p)), cena_bazowa(cena) {}

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

    std::vector<std::shared_ptr<UslugaProsta>> pobierzDlaModelu(const std::string& model) {
        return dane; 
    }
};

class UslugaProsta : public SkladnikUslugi, public std::enable_shared_from_this<UslugaProsta> {
private:
    std::string nazwa;
    float cena_bazowa_robocizny;
    std::map<Czesc, int> wymagane_czesci;

public:
    UslugaProsta(std::string n, float cena) 
        : nazwa(std::move(n)), cena_bazowa_robocizny(cena) {}

    void dodajCzesc(const Czesc& czesc, int ilosc) {
        wymagane_czesci[czesc] += ilosc;
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

    void zapiszWBazie(BazaUslug& baza) {
        baza.dodajDoBazy(shared_from_this());
    }
};


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

    float obliczKosztCalkowity(std::shared_ptr<Pojazd> pojazd = nullptr) {
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
    auto mojSamochod = std::make_shared<Pojazd>("Toyota Corolla");
    
    
    BazaUslug baza;
    auto kosztorys = std::make_shared<Kosztorys>();
     
    // Uzupełnienie bazy symulowanymi danymi (aby pobierzDlaModelu nie zwróciło pustego)
    baza.dodajDoBazy(std::make_shared<UslugaProsta>("Wymiana oleju", 100.0f));

    // Pobranie usług predefiniowanych i dodanie wybranej
    auto uslugi = baza.pobierzDlaModelu("Toyota Corolla");
    if(!uslugi.empty()) {
        kosztorys->dodajUsluge(uslugi[0]);
    }
    
    //  Tworzenie usługi niestandardowej
    auto nowaUsluga = std::make_shared<UslugaProsta>("Usluga niestandardowa", 150.0f);
    nowaUsluga->dodajCzesc(Czesc("Tarcze hamulcowe", "Bosch", 299.0f), 2);
    nowaUsluga->zapiszWBazie(baza); // Zapis do bazy 
    kosztorys->dodajUsluge(nowaUsluga);
    
    // Dodanie rabatu
    kosztorys->ustawRabat(10); // 10% rabatu
    
    // Obliczenie końcowego kosztu
    std::cout << "Koszt po rabacie: " << kosztorys->obliczKosztCalkowity(mojSamochod) << " zl\n";

    return 0;
}
//OUTPUT
//Koszt po rabacie: 763.2 zl
