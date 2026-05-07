import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;

public enum StatusZlecenia {
    NOWE,
    PRZYDZIELONE,
    NA_STANOWISKU,
    OCZEKUJE_NA_ZATWIERDZENIE,
    GOTOWE_DO_ODBIORU,
    ZAMKNIETE
}

public interface SkladnikUslugi {
    String nazwa;
    Float obliczKoszt(Pojazd pojazd);
    Integer szacujCzas();
}

public abstract class Pracownik {
    private Integer pracownik_id;
    private String imie;
    private String nazwisko;
    private String login;
}

public class Mechanik extends Pracownik {
    private List<Stanowisko> stanowiska = new ArrayList<>();

    public List<Zlecenie> przegladajNieprzydzielone() {
        return new ArrayList<>();
    }

    public void przyjmijZlecenie(Zlecenie zlecenie) {
    }

    public void zglosRozszerzenieNaprawy(SkladnikUslugi usluga) {
    }

    public RaportNaprawy zakonczNaprawe(Zlecenie zlecenie) {
        return new RaportNaprawy();
    }
}

public class PracownikBiura extends Pracownik {
    public Zlecenie utworzZlecenie(Klient klient, Pojazd pojazd) {
        return new Zlecenie();
    }

    public void negocjujKosztorys(Zlecenie zlecenie) {
    }

    public void zamknijZlecenie(Zlecenie zlecenie) {
    }
}

public class Stanowisko {
    private Integer stanowisko_id;
    private String nazwa;
    private Boolean czy_aktywne;

    public void aktywuj() {
        this.czy_aktywne = true;
    }

    public void dezaktywuj() {
        this.czy_aktywne = false;
    }
}

public class Klient {
    private Integer klient_id;
    private String imie_nazwisko;
    private String email;
    private String nr_telefonu;
    private Boolean zgoda_rodo;

    public void zaktualizujDane(String email, String tel) {
        this.email = email;
        this.nr_telefonu = tel;
    }
}

public class ModelPojazdu {
    private Integer model_id;
    private String marka;
    private String model;
    private String grupa;
}

public class Pojazd {
    private String nr_rejestracyjny;
    private String vin;
    private ModelPojazdu model;
    private Klient wlasciciel;

    public void przypiszModel(ModelPojazdu model) {
        this.model = model;
    }
}

public class Czesc {
    private Integer czesc_id;
    private String nazwa;
    private String producent;
    private Float cena_bazowa;
    private Boolean czy_uniwersalna;
}

public class UslugaProsta implements SkladnikUslugi {
    private Integer usluga_id;
    private String nazwa;
    private Integer szacowany_czas_naprawy;
    private Float cena_bazowa_robocizny;
    private Boolean czy_uniwersalna;
    
    private Map<ModelPojazdu, Float> cennik_dla_modeli = new HashMap<>();
    private Map<Czesc, Integer> wymagane_czesci = new HashMap<>();

    public void dodajCzesc(Czesc czesc, Integer ilosc) {
        wymagane_czesci.put(czesc, ilosc);
    }

    @Override
    public Float obliczKoszt(Pojazd pojazd) {
        return 0.0f;
    }

    @Override
    public Integer szacujCzas() {
        return szacowany_czas_naprawy;
    }
}

public class UslugaZlozona implements SkladnikUslugi {
    private Integer pakiet_id;
    private String nazwa;
    private List<SkladnikUslugi> skladniki = new ArrayList<>();

    public void dodajSkladnik(SkladnikUslugi skladnik) {
        skladniki.add(skladnik);
    }

    public void usunSkladnik(SkladnikUslugi skladnik) {
        skladniki.remove(skladnik);
    }

    @Override
    public Float obliczKoszt(Pojazd pojazd) {
        float suma = 0.0f;
        for(SkladnikUslugi s : skladniki) suma += s.obliczKoszt(pojazd);
        return suma;
    }

    @Override
    public Integer szacujCzas() {
        int sumaCzasu = 0;
        for(SkladnikUslugi s : skladniki) sumaCzasu += s.szacujCzas();
        return sumaCzasu;
    }
}

public class Kosztorys {
    private Integer kosztorys_id;
    private Float koszt_calkowity;
    private Float rabat_procentowy;
    private List<SkladnikUslugi> skladniki = new ArrayList<>();

    public void ustawRabat(Float rabat) {
        this.rabat_procentowy = rabat;
    }

    public void dodajSkladnikKosztorysu(SkladnikUslugi skladnik) {
        skladniki.add(skladnik);
    }

    public Float obliczKosztCalkowity() {
        return 0.0f;
    }
}

public class RaportNaprawy {
    private Integer raport_id;
    private LocalDateTime czas_rozpoczecia;
    private LocalDateTime czas_zakonczenia;
    private String opis_wykonanych_prac;
    private String sugerowane_naprawy;

    public String generujPodsumowanie() {
        return "";
    }
}

public class Zlecenie {
    private Integer zlecenie_id;
    private LocalDate data_przyjecia;
    private LocalDate szacowana_data_odbioru;
    private Float wysokosc_zaliczki;
    private StatusZlecenia status;
    private Klient klient;
    private Pojazd pojazd;
    private Mechanik mechanik;
    private Kosztorys kosztorys;
    private RaportNaprawy raportNaprawy;

    public void zmienStatus(StatusZlecenia nowy_status) {
        this.status = nowy_status;
    }

    public void przypiszMechanika(Mechanik mechanik) {
        this.mechanik = mechanik;
    }

    public void powiadomKlientaOOdbiorze() {
    }

    public String generujDokumentKoncowy() {
        return "";
    }
}
