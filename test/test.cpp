// /* /*#include <iostream>
// #include "../model/Media.h"
// #include <chrono>
// #include <cassert>

// using namespace std;
// using namespace std::chrono;

// int main() {
//     /* year_month_day dataInizio(year(2023) / month(3) / day(2));
//     year_month_day dataFine(year(2023) / month(1) / day(1));

//     // Creazione di un oggetto Media
//     Media film("Christopher Nolan","Inception", "Un film di Christopher Nolan", dataInizio, dataFine, 1000000, 148);

//     // Test di set e get con assert
//     assert(film.getTitolo() == "Inception");
//     assert(film.getDescrizione() == "Un film di Christopher Nolan");
//     assert(film.getVisualizzazioni() == 1000000);
//     assert(film.getDurataMinuti() == 148);
//     cout << "Test set/get superati \n";

//     // Aggiunta di lingue e sottotitoli
//     film.aggiungiLingua(Lingua::Inglese);
//     film.aggiungiLingua(Lingua::Italiano);
//     film.aggiungiSottotitolo(Lingua::Francese);
//     film.aggiungiSottotitolo(Lingua::Spagnolo);

//     // Verifica lingue
//     vector<Lingua> lingue = film.getLingue();
//     assert(find(lingue.begin(), lingue.end(), Lingua::Inglese) != lingue.end());
//     assert(find(lingue.begin(), lingue.end(), Lingua::Italiano) != lingue.end());
//     cout << "Test aggiunta lingue superato \n";

//     // Verifica sottotitoli
//     vector<Lingua> sottotitoli = film.getSottotitoli();
//     assert(find(sottotitoli.begin(), sottotitoli.end(), Lingua::Francese) != sottotitoli.end());
//     assert(find(sottotitoli.begin(), sottotitoli.end(), Lingua::Spagnolo) != sottotitoli.end());
//     cout << "Test aggiunta sottotitoli superato \n";

//     // Rimozione di una lingua e un sottotitolo
//     film.rimuoviLingua(Lingua::Italiano);
//     film.rimuoviSottotitolo(Lingua::Spagnolo);

//     // Verifica dopo la rimozione
//     lingue = film.getLingue();
//     assert(find(lingue.begin(), lingue.end(), Lingua::Italiano) == lingue.end());
//     cout << "Test rimozione lingua superato \n";

//     sottotitoli = film.getSottotitoli();
//     assert(find(sottotitoli.begin(), sottotitoli.end(), Lingua::Spagnolo) == sottotitoli.end());
//     cout << "Test rimozione sottotitolo superato \n";


//     auto oggi = year_month_day{floor<days>(system_clock::now())};

//     // Test FuoriProduzione()
//     Media media1("Autore1","Vecchio Film", "Descrizione", 2020y / 1 / 1, 2022y / 12 / 31, 1000, 120);
//     assert(media1.FuoriProduzione() == true);
//     cout << "FuoriProduzione() test 1 superato\n";

//     Media media2("Autore2","Nuovo Film", "Descrizione", 2023y / 1 / 1, oggi + years(1), 2000, 130);
//     assert(media2.FuoriProduzione() == false);
//     cout << "FuoriProduzione() test 2 superato\n";

//     // Test DurataCampagna()
//     Media media3("Autore3","Campagna 1 anno", "Descrizione", 2023y / 3 / 30, 2024y / 3 / 30, 1500, 110);
//     assert(media3.DurataCampagna() == 366);
//     cout << "DurataCampagna() test 1 superato\n";

//     Media media4("Autore4","Campagna breve", "Descrizione", 2025y / 1 / 1, 2025y / 1 / 10, 500, 90);
//     assert(media4.DurataCampagna() == 9);
//     cout << "DurataCampagna() test 2 superato\n";

//     cout << "Tutti i test superati con successo!\n";
//     return 0; 
    

// }*/
// #include <iostream>
// #include <cassert>
// #include "../model/Film.h"
// #include "../model/Trailer.h"

// using namespace std;
// using namespace std::chrono;

// int main() {
//     // Creazione di un film
//     Film film("Christopher Nolan", "Inception", "Un film sui sogni dentro i sogni",
//               year_month_day{2024y, April, 1d}, year_month_day{2024y, June, 30d}, 
//               1000000, 148, "Fantascienza", Classificazione::QUATTORDICI_PIU, 
//               8.8, "Warner Bros", 1, 10.0);

//     // Verifica delle informazioni del film
//     assert(film.getAutore() == "Christopher Nolan");
//     assert(film.getTitolo() == "Inception");
//     assert(film.getCostoBiglietto() == 10.0);
//     assert(film.getVisualizzazioni() == 1000000);
    
//     // Creazione di un trailer associato
//     Trailer trailer("Warner Bros", "Inception Trailer", "Trailer di Inception",
//                     year_month_day{2024y, March, 1d}, year_month_day{2024y, April, 15d},
//                     5000000, 2, Classificazione::SEI_PIU, &film);
    
//     // Verifica dell'associazione tra film e trailer
//     assert(trailer.calcolaIncasso() > 0);


//     // Controllo della modifica della data di fine rilascio
//    /*  film.setDataFineRilascio(year_month_day{2024y, July, 31d});
//     assert(film.getDataFineRilascio() == year_month_day{2024y, July, 31d});
//     assert(trailer.getDataFineRilascio() == year_month_day{2024y, July, 31d});

//     // Verifica del metodo estendiDataFineRilascio
//     film.estendiDataFineRilascio();
//     assert(film.getDataFineRilascio() == year_month_day{2024y, August, 7d});
//     assert(trailer.getDataFineRilascio() == year_month_day{2024y, August, 7d}); */
    
//     cout << "Tutti i test sono stati superati con successo!" << endl;
    
//     return 0;
// }
/*/
#include <iostream>
#include <chrono>
#include "../Media.h"   // Includi le tue classi reali
#include "../Film.h"
#include "../Trailer.h"
#include "../Inserzione.h"
using namespace std;
using namespace std::chrono;

void testEstensioneFilmAttivo() {
    cout << "Test 1: Estensione Film attivo...\n";

    year_month_day inizio{2025y, May, 1d};
    year_month_day fine{2025y, May, 15d};

    Film film("Regista", "Titolo", "Descrizione", inizio, fine, 100, 120, "Azione", Classificazione::QUATTORDICI_PIU, 4.2, "Produzione", 1, 9.5);
    film.estendiDataFineRilascio();

    year_month_day atteso = year_month_day{sys_days(fine) + days{7}};
    if (film.getDataFineRilascio() == atteso) {
        cout << "Test 1 superato: data estesa correttamente a " << static_cast<unsigned>(atteso.day()) << "/" << static_cast<unsigned>(atteso.month()) << "/" << int(atteso.year()) << "\n";
    } else {
        cout << "Test 1 fallito: data ottenuta " << static_cast<unsigned>(film.getDataFineRilascio().day()) << "/" << static_cast<unsigned>(film.getDataFineRilascio().month()) << "/" << int(film.getDataFineRilascio().year()) << "\n";
    }
}

void testEstensioneTrailer() {
    cout << "Test 2: Estensione Film e Trailer associati...\n";

    year_month_day inizio{2025y, May, 1d};
    year_month_day fine{2025y, May, 15d};
    year_month_day fine2{2025y, May, 1d};

    Film film("Regista", "Titolo", "Descrizione", inizio, fine, 100, 120, "Azione", Classificazione::QUATTORDICI_PIU, 4.2, "Produzione", 1, 9.5);
    Trailer* t1 = new Trailer("Autore", "T1", "Desc", inizio, fine, 50, 2, Classificazione::QUATTORDICI_PIU, 4, &film);
    Trailer* t2 = new Trailer("Autore", "T1", "Desc", inizio, fine2, 50, 2, Classificazione::QUATTORDICI_PIU, 5, &film);

    film.aggiungiTrailer(t1);
    film.aggiungiTrailer(t2);

    film.estendiDataFineRilascio(); //deve provocare l'aggiornamento solo di t1

    year_month_day nuovaData = film.getDataFineRilascio();
    if (t1->getDataFineRilascio() == nuovaData) {
        cout << "   Test 2.1/2 superato: trailer aggiornato a " << static_cast<unsigned>(nuovaData.day()) << "/" << static_cast<unsigned>(nuovaData.month()) << "/" << int(nuovaData.year()) << "\n";
    } else {
        cout << "   Test 2.1/2 fallito: trailer ha data " << static_cast<unsigned>(t1->getDataFineRilascio().day()) << "/" << static_cast<unsigned>(t1->getDataFineRilascio().month()) << "/" << int(t1->getDataFineRilascio().year()) << "\n";
    }

    if (t2->getDataFineRilascio() == fine2) {
        cout << "   Test 2.2/2 superato: trailer non aggiornato correttamente \n";
    } else {
        cout << "   Test 2.2/2 fallito: trailer ha data " << static_cast<unsigned>(t2->getDataFineRilascio().day()) << "/" << static_cast<unsigned>(t2->getDataFineRilascio().month()) << "/" << int(t2->getDataFineRilascio().year()) << "\n";
    }
    
}

void testTrailerFuoriProduzione() {
    cout << "Test 3: Trailer fuori produzione non viene aggiornato...\n";

    year_month_day inizio{2025y, April, 1d};
    year_month_day fine{2025y, April, 15d};
    
    Film film("Regista", "Titolo", "Descrizione", inizio, year_month_day{2025y, May, 15d}, 100, 120, "Azione", Classificazione::QUATTORDICI_PIU, 4.2, "Produzione", 1, 9.5);
    Trailer* t1 = new Trailer("Autore", "T1", "Desc", inizio, fine, 50, 2, Classificazione::QUATTORDICI_PIU, 5, &film);
    
    film.aggiungiTrailer(t1);
    film.estendiDataFineRilascio();
    
    if (t1->getDataFineRilascio() == fine) {
        cout << "Test 3 superato: trailer fuori produzione non è stato aggiornato\n";
    } else {
        cout << " Test 3 fallito: trailer aggiornato a " << static_cast<unsigned>(t1->getDataFineRilascio().day()) << "/" << static_cast<unsigned>(t1->getDataFineRilascio().month()) << "/" << int(t1->getDataFineRilascio().year()) << "\n";
    }
    
}

void testInserzioneAttiva(){
    cout << "Test 4: Tentativo di estendere data Inserzione attiva...\n";
    year_month_day inizio{2025y, May, 1d};
    year_month_day fine{2025y, May, 15d};
    Inserzione i1("Autore","Mi sono fatto la cacca addosso","Un bambino si fa la cacca addosso", inizio, fine,124,23,Classificazione::TUTTI, 2,"Michelangelo",120);
    i1.estendiDataFineRilascio();
    if(i1.getDataFineRilascio()==year_month_day{2025y,June,15d})
        cout << "Test 4 superato";
    else {
        cout << "   Test 4 fallito, inserzione ha data" << static_cast<unsigned>(i1.getDataFineRilascio().day()) << "/" << static_cast<unsigned>(i1.getDataFineRilascio().month()) << "/" << int(i1.getDataFineRilascio().year()) << "\n";
    }
}

int main() {
    testEstensioneFilmAttivo();
    testEstensioneTrailer();
    testTrailerFuoriProduzione();
    testInserzioneAttiva();
    cout << "caca" << endl;
    return 0;
}
 */

 #include "../catch.hpp"

TEST_CASE("Prova di base") {
    REQUIRE(1 + 1 == 2);
}
