/* /*#include <iostream>
#include "../model/Media.h"
#include <chrono>
#include <cassert>

using namespace std;
using namespace std::chrono;

int main() {
    /* year_month_day dataInizio(year(2023) / month(3) / day(2));
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
    

}*/
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
   /*  film.setDataFineRilascio(year_month_day{2024y, July, 31d});
    assert(film.getDataFineRilascio() == year_month_day{2024y, July, 31d});
    assert(trailer.getDataFineRilascio() == year_month_day{2024y, July, 31d});

    // Verifica del metodo estendiDataFineRilascio
    film.estendiDataFineRilascio();
    assert(film.getDataFineRilascio() == year_month_day{2024y, August, 7d});
    assert(trailer.getDataFineRilascio() == year_month_day{2024y, August, 7d}); */
    
    cout << "Tutti i test sono stati superati con successo!" << endl;
    
    return 0;
}

 