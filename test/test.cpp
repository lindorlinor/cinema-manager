#include "../catch.hpp"
#include "../Film.h"
#include "../Trailer.h"
#include "../Inserzione.h"
#include "../Podcast.h"
#include "../Puntata.h"
#include <chrono>

using namespace std;
using namespace std::chrono;
// #define YMD(y, m, d) year_month_day{year{y}, month{m}, day{d}}

// Test 1
TEST_CASE("1. Estensione Film attivo")
{
    year_month_day inizio{2025y, December, 1d};
    year_month_day fine{2025y, December, 15d};

    Film film("Titolo", "Descrizione", inizio, fine, 120, Formato::IMAX_3D, Risoluzione::FullHD_1080p,
              3, 9.3, "azienda", "Autore");

    film.estendiDataFineRilascio();

    year_month_day atteso = year_month_day{sys_days(fine) + days{7}};
    REQUIRE(film.getDataFineRilascio() == atteso);
}

// Test 2: Trailer aggiornati solo se data coincide
TEST_CASE("2. Estensione Trailer associati condizionale")
{
    year_month_day inizio{2025y, April, 1d};
    year_month_day fine{2025y, December, 15d};
    year_month_day fine2{2025y, December, 22d};

    Film film("Titolo", "Descrizione", inizio, fine, 120, Formato::IMAX_3D, Risoluzione::FullHD_1080p,
              3, 9.3, "azienda", "Autore");

    Trailer *t1 = new Trailer("Titolo", "Descrizione", inizio, fine, 120, Formato::IMAX_3D, Risoluzione::FullHD_1080p,
                              3, &film, "Autore");
    Trailer *t2 = new Trailer("Titolo", "Descrizione", inizio, fine, 120, Formato::IMAX_3D, Risoluzione::FullHD_1080p,
                              3, &film, "Autore");

    film.aggiungiTrailer(t1);
    film.aggiungiTrailer(t2);

    film.estendiDataFineRilascio();

    year_month_day nuovaData = film.getDataFineRilascio();

    SECTION("2.1 Trailer non fuori produzione viene aggiornato")
    {
        REQUIRE(t1->getDataFineRilascio() == nuovaData);
    }

    SECTION("2.2 Trailer fuori produzione non viene aggiornato")
    {
        REQUIRE(t2->getDataFineRilascio() == fine2);
    }
}

// Test 3: Trailer fuori produzione
TEST_CASE("3. Trailer fuori produzione non aggiornato")
{
    std::cout << "Eseguo test 3\n";
    year_month_day inizio{2025y, April, 1d};
    year_month_day fine{2025y, April, 15d};

    Film film("Titolo", "Descrizione", inizio, fine, 120, Formato::IMAX_3D, Risoluzione::FullHD_1080p,
              3, 9.3, "azienda", "Autore");

    Trailer *t1 = new Trailer("Titolo", "Descrizione", inizio, fine, 120, Formato::IMAX_3D, Risoluzione::FullHD_1080p,
                              3, &film, "Autore");

    film.aggiungiTrailer(t1);
    film.estendiDataFineRilascio();

    REQUIRE(t1->getDataFineRilascio() == fine);
}

TEST_CASE("4. Inserzione.estendiDataFineRilascio()")
{
    year_month_day inizio{2025y, July, 30d};
    year_month_day fine{2025y, December, 15d};
    year_month_day fine2{2025y, July, 29d};

    Inserzione i1("Titolo", "Descrizione", inizio, fine, 120, Formato::IMAX_3D, Risoluzione::FullHD_1080p,
                  3, Classificazione::TUTTI, 20.0, "azienda");
    Inserzione i2("Titolo", "Descrizione", inizio, fine, 120, Formato::IMAX_3D, Risoluzione::FullHD_1080p,
                  3, Classificazione::TUTTI, 20.0, "azienda");
    i1.estendiDataFineRilascio();
    SECTION("4.1 Inserzione attiva")
    {
        REQUIRE(i1.getDataFineRilascio() == fine + months{1});
    }
    SECTION("4.1 Inserzione fuori produzione")
    {
        REQUIRE(i1.getDataFineRilascio() == fine + months{1});
    }
}

TEST_CASE("5. Inserzione.calcolaIncasso()")
{
    Inserzione i1("Titolo", "Descrizione", year_month_day{2025y, July, 1d}, year_month_day{2025y, July, 30d}, 120,
                  Formato::IMAX_3D, Risoluzione::FullHD_1080p, 15, Classificazione::TUTTI, 30.0, "azienda");

    REQUIRE(i1.calcolaIncasso() == 30 * 15 * i1.DurataCampagna());
}

TEST_CASE("6. Inserzione.aggiungiFasciaOraria(FasciaOraria)")
{
    SECTION("6.1 verifica aggiunta della stessa fascia oraria")
    {
        Inserzione i1("Titolo", "Descrizione", year_month_day{2025y, July, 1d}, year_month_day{2025y, July, 30d}, 120,
                      Formato::IMAX_3D, Risoluzione::FullHD_1080p, 15, Classificazione::TUTTI, 15.0, "azienda");
        i1.aggiungiFasciaOraria(FasciaOraria::Mattina);
        i1.aggiungiFasciaOraria(FasciaOraria::Mattina);
        REQUIRE(i1.getFasceOrarie()[0] == FasciaOraria::Mattina);
        REQUIRE(i1.getFasceOrarie().size() == 1);
    }

    SECTION("6.2 Inserzione.calcoloIncasso()")
    {
        Inserzione i1("Titolo", "Descrizione", year_month_day{2025y, July, 1d}, year_month_day{2025y, July, 30d}, 120,
                      Formato::IMAX_3D, Risoluzione::FullHD_1080p, 15, Classificazione::TUTTI, 15.0, "azienda");
        i1.aggiungiFasciaOraria(FasciaOraria::Mattina);
        REQUIRE(i1.calcolaIncasso() == 15 * 15 * i1.DurataCampagna());
        i1.aggiungiFasciaOraria(FasciaOraria::Sera);
        REQUIRE(i1.calcolaIncasso() == 15 * 15 * i1.DurataCampagna() * 1.2);
        i1.aggiungiFasciaOraria(FasciaOraria::Pomeriggio);
        REQUIRE(i1.calcolaIncasso() == 15 * 15 * i1.DurataCampagna() * 1.3);
    }
}

TEST_CASE("7. Inserzione.rimuoviFasciaOraria(FasciaOraria)")
{
    SECTION("7.1 verifica rimozione di una fascia oraria aggiunta")
    {
        Inserzione i1("Titolo", "Descrizione", year_month_day{2025y, July, 1d}, year_month_day{2025y, July, 30d}, 120,
                      Formato::IMAX_3D, Risoluzione::FullHD_1080p, 15, Classificazione::TUTTI, 15.0, "azienda");
        i1.aggiungiFasciaOraria(FasciaOraria::Mattina);
        REQUIRE(i1.getFasceOrarie()[0] == FasciaOraria::Mattina);
        REQUIRE(i1.getFasceOrarie().size() == 1);
        i1.rimuoviFasciaOraria(FasciaOraria::Mattina);
        REQUIRE(i1.getFasceOrarie().size() == 1); // sempre presente mattina
    }
    SECTION("7.2 verifica rimozione di una fascia oraria non aggiunta")
    {
        Inserzione i1("Titolo", "Descrizione", year_month_day{2025y, July, 1d}, year_month_day{2025y, July, 30d}, 120,
                      Formato::IMAX_3D, Risoluzione::FullHD_1080p, 3, Classificazione::TUTTI, 20.0, "azienda");
        i1.rimuoviFasciaOraria(FasciaOraria::Sera);
        REQUIRE(i1.getFasceOrarie().size() == 1); // presente mattina
    }

    SECTION("7.3 verifica calcoloIncasso")
    {
        Inserzione i1("Titolo", "Descrizione", year_month_day{2025y, July, 1d}, year_month_day{2025y, July, 30d}, 120,
                      Formato::IMAX_3D, Risoluzione::FullHD_1080p, 15, Classificazione::TUTTI, 15.0, "azienda");
        i1.aggiungiFasciaOraria(FasciaOraria::Mattina);
        i1.aggiungiFasciaOraria(FasciaOraria::Sera);
        i1.aggiungiFasciaOraria(FasciaOraria::Pomeriggio);
        i1.rimuoviFasciaOraria(FasciaOraria::Mattina);
        REQUIRE(i1.calcolaIncasso() == 15 * 15 * i1.DurataCampagna() * 1.3);

        i1.rimuoviFasciaOraria(FasciaOraria::Pomeriggio);
        REQUIRE(i1.calcolaIncasso() == 15 * 15 * i1.DurataCampagna() * 1.2);
        i1.rimuoviFasciaOraria(FasciaOraria::Sera);
        REQUIRE(i1.calcolaIncasso() == 15 * 15 * i1.DurataCampagna());
    }
}

TEST_CASE("8. Podcast.aggiungiPuntata(puntata)")
{
    SECTION("8.1 verifica aggiunta della puntata")
    {
        year_month_day inizio{2025y, December, 1d};
        year_month_day fine{2025y, December, 15d};

        Podcast podcast("Titolo", "Descrizione",
                        Formato::IMAX_3D, Risoluzione::FullHD_1080p);
        Puntata *puntata1 = new Puntata("Titolo", "Descrizione", inizio, fine, 60, &podcast, 3);
        // podcast.estendiDataFineRilascio(); non lo faccio perché non ha senso farlo, in quanto non accadrà mai
        puntata1->estendiDataFineRilascio();

        REQUIRE(podcast.getDataFineRilascio() == year_month_day{2025y, December, 16d});
        REQUIRE(puntata1->getDataFineRilascio() == year_month_day{2025y, December, 16d});
        REQUIRE(podcast.getDurataMinuti() == 60);

        Puntata *puntata2 = new Puntata("Titolo", "Descrizione", year_month_day{2025y, December, 15d}, year_month_day{2025y, December, 25d},
                                        60, &podcast, 3);
        REQUIRE(podcast.getDataFineRilascio() == year_month_day{2025y, December, 25d});
        REQUIRE(podcast.getDurataMinuti() == 120);
        REQUIRE(puntata2->getPodcast() == &podcast);
    }

    SECTION("8.2 verifica rimozione della puntata")
    {
        year_month_day inizio{2025y, April, 1d};
        year_month_day fine{2025y, April, 15d};

        Podcast podcast("Titolo", "Descrizione",
                        Formato::IMAX_3D, Risoluzione::FullHD_1080p);

        Puntata *puntata1 = new Puntata("Titolo", "Descrizione",
                                        year_month_day{2025y, December, 15d}, year_month_day{2025y, December, 19d},
                                        60, &podcast, 3);
        Puntata *puntata2 = new Puntata("Titolo", "Descrizione",
                                        year_month_day{2025y, December, 15d}, year_month_day{2025y, December, 25d},
                                        60, &podcast, 3);

        REQUIRE((podcast.getElencoPuntate()).empty() == false);
        REQUIRE((podcast.getVisualizzazioni()) == puntata1->getVisualizzazioni() + puntata2->getVisualizzazioni());
        REQUIRE(podcast.getDataFineRilascio() == year_month_day{2025y, December, 25d});
        REQUIRE(puntata1->calcolaIncasso() == Approx(puntata1->getVisualizzazioni() * 3 * 0.05));
        REQUIRE(podcast.calcolaIncasso() == Approx(puntata1->getVisualizzazioni() * 3 * 0.05 + puntata2->getVisualizzazioni() * 3 * 0.05));
        podcast.rimuoviPuntata(puntata2);
        REQUIRE((podcast.getVisualizzazioni()) == puntata1->getVisualizzazioni());
        REQUIRE((podcast.calcolaIncasso()) == Approx(puntata1->getVisualizzazioni() * 3 * 0.05));
        REQUIRE(podcast.getDataFineRilascio() == year_month_day{2025y, December, 19d});
        REQUIRE(podcast.getDurataMinuti() == 60);
    }

    SECTION("8.3 verifica riassegnazione puntata")
    {

        Podcast podcast1("Titolo", "Descrizione",
                         Formato::IMAX_3D, Risoluzione::FullHD_1080p);

        Podcast podcast2("Titolo", "Descrizione",
                         Formato::IMAX_3D, Risoluzione::FullHD_1080p);
        Puntata *puntata1 = new Puntata("Titolo", "Descrizione",
                                        year_month_day{2025y, December, 15d}, year_month_day{2025y, December, 19d},
                                        60, &podcast1, 3);
        REQUIRE(podcast1.getElencoPuntate() == vector<Puntata *>{puntata1});
        puntata1->associaPodcast(&podcast2);
        REQUIRE(podcast1.getElencoPuntate().empty() == true);
        REQUIRE(podcast2.getElencoPuntate() == vector<Puntata *>{puntata1});
    }
}

TEST_CASE("9. Verifica aggiunta ospite e rimozione")
{

    Podcast podcast("Titolo", "Descrizione",
                    Formato::IMAX_3D, Risoluzione::FullHD_1080p);
    Puntata *puntata = new Puntata("Titolo", "Descrizione", year_month_day{2025y, December, 15d}, year_month_day{2025y, December, 19d},
                                   60, &podcast, 3);
    puntata->aggiungiOspite("Minnie");
    puntata->aggiungiOspite("Topolino");
    puntata->aggiungiOspite("Paperino");
    std::vector<string> OspitiAttesi1 = {"Minnie", "Topolino", "Paperino"};

    REQUIRE(puntata->getOspiti() == OspitiAttesi1);
    puntata->rimuoviOspite("Topolino");
    std::vector<string> OspitiAttesi2 = {"Minnie", "Paperino"};
    REQUIRE(puntata->getOspiti() == OspitiAttesi2);

    REQUIRE(puntata->calcolaIncasso() == Approx(puntata->getVisualizzazioni() * 3 * 0.05));
    puntata->estendiDataFineRilascio();
    REQUIRE(puntata->getDataFineRilascio() == year_month_day{2025y, December, 20d});
}

TEST_CASE("10. Film::getVisualizzazioni() e Film::IncrementaVisualizzazioni()")
{
    year_month_day inizio{2025y, July, 1d};
    year_month_day fine{2025y, July, 15d};

    Film film1("Titolo", "Descrizione", inizio, fine, 120, Formato::IMAX_3D, Risoluzione::FullHD_1080p,
               3, 9.3, "CasaProd", "Autore");
    Film film2("Titolo", "Descrizione", inizio, fine, 120, Formato::IMAX_3D, Risoluzione::FullHD_1080p,
               3, 9.3, "CasaProd", "Autore");
    REQUIRE(film1.getVisualizzazioni() != 0);
    REQUIRE(film1.getDataLastViewUpdate() != inizio);
    film1.setValutazione();
    REQUIRE(film1.getValutazione() <= 5);

    film2.setValutazione();
    REQUIRE(film2.getVisualizzazioni() != 0);
    REQUIRE(film2.getValutazione() <= 5);
}

TEST_CASE("11. Verifica Puntata::setDataFineRilascio()")
{
    SECTION("11.1 verifico che la modifica di una dataFineRilascio influisca sulle successive")
    {
        Podcast podcast("Titolo", "Descrizione",
                        Formato::IMAX_3D, Risoluzione::FullHD_1080p);
        Puntata *puntata1 = new Puntata("Titolo", "Descrizione", year_month_day{2025y, December, 15d}, year_month_day{2025y, December, 19d},
                                        60, &podcast, 3);
        Puntata *puntata2 = new Puntata("Titolo", "Descrizione", year_month_day{2025y, December, 15d}, year_month_day{2025y, December, 26d},
                                        60, &podcast, 3);

        puntata1->setDataFineRilascio({2025y, December, 30d});
        REQUIRE(puntata1->getDataFineRilascio() == year_month_day{2025y, December, 30d});
        REQUIRE(puntata2->getDataFineRilascio() == year_month_day{2025y, December, 26d});
        REQUIRE(podcast.getDataFineRilascio() == year_month_day{2025y, December, 30d});

        puntata1->setDataFineRilascio({2025y, December, 19d});
        REQUIRE(podcast.getDataFineRilascio() == year_month_day{2025y, December, 26d});
        REQUIRE(puntata1->getDataFineRilascio() == year_month_day{2025y, December, 19d});
        REQUIRE(puntata2->getDataFineRilascio() == year_month_day{2025y, December, 26d});
    }

    SECTION("11.2 verifico che se si immette una data di fine inferiore della data di inizio, questa venga sostituita con quella di inizio")
    {
        Podcast podcast("Titolo", "Descrizione", Formato::IMAX_3D, Risoluzione::FullHD_1080p);
        Puntata *puntata = new Puntata("Titolo", "Descrizione", year_month_day{2025y, December, 19d}, year_month_day{2025y, December, 15d}, 60, &podcast, 3);

        REQUIRE(puntata->getDataFineRilascio() == year_month_day{2025y, December, 19d});
    }
}
TEST_CASE("12. Film::rimuoviTrailer verifica liberazione memoria")
{
    Film film("Remov", "desc", year_month_day{2025y, May, 1d}, year_month_day{2025y, May, 31d},
              110, Formato::DCP, Risoluzione::FullHD_1080p, 0, 7.5, "Studio");

    Trailer *t = new Trailer("ToDelete", "desc", year_month_day{2025y, May, 1d}, year_month_day{2025y, May, 25d},
                             2, Formato::DCP, Risoluzione::HD_720p, 2, &film);

    film.rimuoviTrailer(t); // trailer distrutto
    REQUIRE(true);          // test base, controllo leak da fuori (valgrind)
}

TEST_CASE("13. setDataFineRilascio Film -> trailer aggiornati")
{
    Film film("Prolungato", "desc", year_month_day{2025y, December, 1d}, year_month_day{2025y, December, 20d},
              130, Formato::DCP, Risoluzione::FullHD_1080p, 2, 11.0, "Studio");

    Trailer *t = new Trailer("T", "desc", year_month_day{2025y, December, 1d}, year_month_day{2025y, December, 20d},
                             2, Formato::DCP, Risoluzione::HD_720p, 2, &film);

    film.aggiungiTrailer(t);

    year_month_day nuovaFine = year_month_day{2025y, December, 27d};
    film.setDataFineRilascio(nuovaFine);

    REQUIRE(t->getDataFineRilascio() == nuovaFine);
}

TEST_CASE("14. disaccoppiaTrailer")
{
    Film film("Film", "desc", year_month_day{2025y, July, 1d}, year_month_day{2025y, July, 31d},
              100, Formato::DCP, Risoluzione::HD_720p, 1, 9.0, "Studio");

    Trailer *t = new Trailer("T1", "desc", year_month_day{2025y, July, 1d}, year_month_day{2025y, July, 15d},
                             3, Formato::DCP, Risoluzione::HD_720p, 2, &film);
    film.disaccoppiaTrailer(t);
    // Trailer ancora valido, ma non nella lista del film, deve essere distrutto
    REQUIRE(t->getFilm() == &film);
    delete t;
}