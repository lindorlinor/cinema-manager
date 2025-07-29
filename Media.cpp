#include "Media.h"
#include <iostream>
#include <algorithm>


Media::~Media() {}

// Costruttore
Media::Media(const string &autore, const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, unsigned int visualizzazioni, unsigned int durataMinuti)
    : m_autore(autore), m_titolo(titolo), m_descrizione(descrizione), m_dataInizioRilascio(gg_mm_aaInizioRilascio), m_dataFineRilascio(gg_mm_aaFineRilascio),
      m_visualizzazioni(visualizzazioni), m_durataMinuti(durataMinuti) {}

bool Media::FuoriProduzione() const
{
    auto today = year_month_day{floor<days>(system_clock::now())};
    return today > m_dataFineRilascio;
}

unsigned int Media::DurataCampagna() const
{
    sys_days inizio = m_dataInizioRilascio;
    sys_days fine = m_dataFineRilascio;
    return static_cast<unsigned int>((fine - inizio).count());
}

void Media::aggiungiLingua(Lingua lingua) {
    if (find(m_lingueDisponibili.begin(), m_lingueDisponibili.end(), lingua) == m_lingueDisponibili.end()) {
        m_lingueDisponibili.push_back(lingua);
    }
}

void Media::aggiungiSottotitolo(Lingua lingua) {
    if (find(m_sottotitoliDisponibili.begin(), m_sottotitoliDisponibili.end(), lingua) == m_sottotitoliDisponibili.end()) {
        m_sottotitoliDisponibili.push_back(lingua);
    }
}

void Media::rimuoviLingua(Lingua lingua) {
    auto it = find(m_lingueDisponibili.begin(), m_lingueDisponibili.end(), lingua);
    if (it != m_lingueDisponibili.end()) {
        m_lingueDisponibili.erase(it);
    }
}

void Media::rimuoviSottotitolo(Lingua lingua) {
    auto it = find(m_sottotitoliDisponibili.begin(), m_sottotitoliDisponibili.end(), lingua);
    if (it != m_sottotitoliDisponibili.end()) {
        m_sottotitoliDisponibili.erase(it);
    }
}

//metodi get
year_month_day Media::getDataFineRilascio() const {
    return m_dataFineRilascio;
}






// // Metodi set
// void Media::setAutore(const string& autore){
//     m_autore = autore;
// }
// void Media::setTitolo(const string& titolo) {
//     m_titolo = titolo;
// }

// void Media::setDescrizione(const string& descrizione) {
//     m_descrizione = descrizione;
// }

// void Media::setDataInizioRilascio(year_month_day gg_mm_aaInizioRilascio) {
//     m_dataInizioRilascio = gg_mm_aaInizioRilascio;
// }

// void Media::setDataFineRilascio(year_month_day gg_mm_aaFineRilascio) {
//     m_dataFineRilascio = gg_mm_aaFineRilascio;
// }

// void Media::setVisualizzazioni(unsigned int visualizzazioni) {
//     m_visualizzazioni = visualizzazioni;
// }

// void Media::setDurataMinuti(unsigned int durata) {
//     m_durataMinuti = durata;
// }

// // Metodi get
// string Media::getAutore() const{
//     return m_autore;
// }
// string Media::getTitolo() const {
//     return m_titolo;
// }

// string Media::getDescrizione() const {
//     return m_descrizione;
// }

// year_month_day Media::getDataInizioRilascio() const {
//     return m_dataInizioRilascio;
// }


// unsigned int Media::getVisualizzazioni() const {
//     return m_visualizzazioni;
// }

// unsigned int Media::getDurataMinuti() const {
//     return m_durataMinuti;
// }

// vector<Lingua> Media::getLingue() const {
//     return m_lingueDisponibili;
// }

// vector<Lingua> Media::getSottotitoli() const {
//     return m_sottotitoliDisponibili;
// }