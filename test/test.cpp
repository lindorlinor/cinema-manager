/*
int main() {
    year_month_day dataInizio(year(2023) / month(3) / day(2));
    year_month_day dataFine(year(2023) / month(1) / day(1));

    // Creazione di un oggetto Media
    Media film("Christopher Nolan","Inception", "Un film di Christopher Nolan", dataInizio, dataFine, 1000000, 148);

    // Test di set e get con assert
    assert(film.getTitolo() == "Inception");
    assert(film.getDescrizione() == "Un film di Christopher Nolan");
    assert(film.getVisualizzazioni() == 1000000);
    assert(film.getDurataMinuti() == 148);
    cout << "Test set/get superati \n";

    // Aggiunta di lingue e sottotitoli
    film.aggiungiLingua(Lingua::Inglese);
    film.aggiungiLingua(Lingua::Italiano);
    film.aggiungiSottotitolo(Lingua::Francese);
    film.aggiungiSottotitolo(Lingua::Spagnolo);

    // Verifica lingue
    vector<Lingua> lingue = film.getLingue();
    assert(find(lingue.begin(), lingue.end(), Lingua::Inglese) != lingue.end());
    assert(find(lingue.begin(), lingue.end(), Lingua::Italiano) != lingue.end());
    cout << "Test aggiunta lingue superato \n";

    // Verifica sottotitoli
    vector<Lingua> sottotitoli = film.getSottotitoli();
    assert(find(sottotitoli.begin(), sottotitoli.end(), Lingua::Francese) != sottotitoli.end());
    assert(find(sottotitoli.begin(), sottotitoli.end(), Lingua::Spagnolo) != sottotitoli.end());
    cout << "Test aggiunta sottotitoli superato \n";

    // Rimozione di una lingua e un sottotitolo
    film.rimuoviLingua(Lingua::Italiano);
    film.rimuoviSottotitolo(Lingua::Spagnolo);

    // Verifica dopo la rimozione
    lingue = film.getLingue();
    assert(find(lingue.begin(), lingue.end(), Lingua::Italiano) == lingue.end());
    cout << "Test rimozione lingua superato \n";

    sottotitoli = film.getSottotitoli();
    assert(find(sottotitoli.begin(), sottotitoli.end(), Lingua::Spagnolo) == sottotitoli.end());
    cout << "Test rimozione sottotitolo superato \n";


    auto oggi = year_month_day{floor<days>(system_clock::now())};

    // Test FuoriProduzione()
    Media media1("Autore1","Vecchio Film", "Descrizione", 2020y / 1 / 1, 2022y / 12 / 31, 1000, 120);
    assert(media1.FuoriProduzione() == true);
    cout << "FuoriProduzione() test 1 superato\n";

    Media media2("Autore2","Nuovo Film", "Descrizione", 2023y / 1 / 1, oggi + years(1), 2000, 130);
    assert(media2.FuoriProduzione() == false);
    cout << "FuoriProduzione() test 2 superato\n";

    // Test DurataCampagna()
    Media media3("Autore3","Campagna 1 anno", "Descrizione", 2023y / 3 / 30, 2024y / 3 / 30, 1500, 110);
    assert(media3.DurataCampagna() == 366);
    cout << "DurataCampagna() test 1 superato\n";

    Media media4("Autore4","Campagna breve", "Descrizione", 2025y / 1 / 1, 2025y / 1 / 10, 500, 90);
    assert(media4.DurataCampagna() == 9);
    cout << "DurataCampagna() test 2 superato\n";

    cout << "Tutti i test superati con successo!\n";
    return 0; 

#include <iostream>
#include <cassert>
#include "../model/Film.h"
#include "../model/Trailer.h"

using namespace std;
using namespace std::chrono;

int main() {
    // Creazione di un film
    Film film("Christopher Nolan", "Inception", "Un film sui sogni dentro i sogni",
              year_month_day{2024y, April, 1d}, year_month_day{2024y, June, 30d}, 
              1000000, 148, "Fantascienza", Classificazione::QUATTORDICI_PIU, 
              8.8, "Warner Bros", 1, 10.0);

    // Verifica delle informazioni del film
    assert(film.getAutore() == "Christopher Nolan");
    assert(film.getTitolo() == "Inception");
    assert(film.getCostoBiglietto() == 10.0);
    assert(film.getVisualizzazioni() == 1000000);
    
    // Creazione di un trailer associato
    Trailer trailer("Warner Bros", "Inception Trailer", "Trailer di Inception",
                    year_month_day{2024y, March, 1d}, year_month_day{2024y, April, 15d},
                    5000000, 2, Classificazione::SEI_PIU, &film);
    
    // Verifica dell'associazione tra film e trailer
    assert(trailer.calcolaIncasso() > 0);


    // Controllo della modifica della data di fine rilascio
     film.setDataFineRilascio(year_month_day{2024y, July, 31d});
    assert(film.getDataFineRilascio() == year_month_day{2024y, July, 31d});
    assert(trailer.getDataFineRilascio() == year_month_day{2024y, July, 31d});

    // Verifica del metodo estendiDataFineRilascio
    film.estendiDataFineRilascio();
    assert(film.getDataFineRilascio() == year_month_day{2024y, August, 7d});
    assert(trailer.getDataFineRilascio() == year_month_day{2024y, August, 7d}); 
    cout << "Tutti i test sono stati superati con successo!" << endl;
    return 0;
}*/

#include "../catch.hpp"
#include "../Film.h"
#include "../Trailer.h"
#include "../Inserzione.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

// Test 1
TEST_CASE("1. Estensione Film attivo") {
    year_month_day inizio{2025y, August, 1d};
    year_month_day fine{2025y, August, 15d};

    Film film("Regista", "Titolo", "Descrizione", inizio, fine, 100, 120, "Azione",
              Classificazione::QUATTORDICI_PIU, 4.2, "Produzione", 1, 9.5);

    film.estendiDataFineRilascio();

    year_month_day atteso = year_month_day{sys_days(fine) + days{7}};
    REQUIRE(film.getDataFineRilascio() == atteso);
}

// Test 2: Trailer aggiornati solo se data coincide
TEST_CASE("2. Estensione Trailer associati condizionale") {
    year_month_day inizio{2025y, April, 1d};
    year_month_day fine{2025y, August, 15d};
    year_month_day fine2{2025y, May, 1d};

    Film film("Regista", "Titolo", "Descrizione", inizio, fine, 100, 120, "Azione",
              Classificazione::QUATTORDICI_PIU, 4.2, "Produzione", 1, 9.5);

    Trailer* t1 = new Trailer("Autore", "T1", "Desc", inizio, fine, 50, 2,
                              Classificazione::QUATTORDICI_PIU, 4, &film);
    Trailer* t2 = new Trailer("Autore", "T2", "Desc", inizio, fine2, 50, 2,
                              Classificazione::QUATTORDICI_PIU, 5, &film);

    film.aggiungiTrailer(t1);
    film.aggiungiTrailer(t2);

    film.estendiDataFineRilascio();

    year_month_day nuovaData = film.getDataFineRilascio();

    SECTION("2.1 Trailer non fuori produzione viene aggiornato") {
        REQUIRE(t1->getDataFineRilascio() == nuovaData);
    }

    SECTION("2.2 Trailer fuori produzione non viene aggiornato") {
        REQUIRE(t2->getDataFineRilascio() == fine2);
    }

}

// Test 3: Trailer fuori produzione
TEST_CASE("3. Trailer fuori produzione non aggiornato") {
     std::cout << "Eseguo test 3\n";
    year_month_day inizio{2025y, April, 1d};
    year_month_day fine{2025y, April, 15d};

    Film film("Regista", "Titolo", "Descrizione", inizio,
              year_month_day{2025y, August, 15d}, 100, 120, "Azione",
              Classificazione::QUATTORDICI_PIU, 4.2, "Produzione", 1, 9.5);

    Trailer* t1 = new Trailer("Autore", "T1", "Desc", inizio, fine, 50, 2,
                              Classificazione::QUATTORDICI_PIU, 5, &film);

    film.aggiungiTrailer(t1);
    film.estendiDataFineRilascio();

    REQUIRE(t1->getDataFineRilascio() == fine);

}


TEST_CASE("4. Inserzione.estendiDataFineRilascio()"){
    year_month_day inizio{2025y,July,30d};
    year_month_day fine{2025y,August,15d};
    year_month_day fine2{2025y,July,29d};

    Inserzione i1("Lupo Lucio","Sushi Zu commercial 2025","Pubblicita' per ciname 2025 per Sushi Zu",inizio,fine,200,1,Classificazione::TUTTI,15,"Sushi Zu srl.",15);
    Inserzione i2("Lupo Lucio","Sushi Zu commercial 2025","Pubblicita' per ciname 2025 per Sushi Zu",inizio,fine,200,1,Classificazione::TUTTI,15,"Sushi Zu srl.",15);
    i1.estendiDataFineRilascio();
    SECTION("4.1 Inserzione attiva"){
        REQUIRE(i1.getDataFineRilascio() == fine+months{1});
    }
    SECTION("4.1 Inserzione fuori produzione"){
        REQUIRE(i1.getDataFineRilascio() == fine+months{1});
    }
}


TEST_CASE("5. Inserzione.calcolaIncasso()"){
    Inserzione i1("Matteo Villalonghi", "All you can pasta 2025","Contenuto promozionale",year_month_day{2025y,July,1d},year_month_day{2025y,July,30d},200,1,Classificazione::TUTTI,10,"caca",15);
    REQUIRE(i1.calcolaIncasso()==30*10*15);
}