#include "Media.h"
#include <iostream>
#include <algorithm>
Media::~Media () {}
// Costruttore
Media::Media(const string& autore, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, unsigned int visualizzazioni, unsigned int durataMinuti)
    : _autore(autore),_titolo(titolo), _descrizione(descrizione), _dataInizioRilascio(gg_mm_aaInizioRilascio), _dataFineRilascio(gg_mm_aaFineRilascio), 
      _visualizzazioni(visualizzazioni), _durataMinuti(durataMinuti) {}

// Metodi set
void Media::setAutore(const string& autore){
    _autore = autore;
}
void Media::setTitolo(const string& titolo) {
    _titolo = titolo;
}

void Media::setDescrizione(const string& descrizione) {
    _descrizione = descrizione;
}

void Media::setDataInizioRilascio(year_month_day gg_mm_aaInizioRilascio) {
    _dataInizioRilascio = gg_mm_aaInizioRilascio;
}

void Media::setDataFineRilascio(year_month_day gg_mm_aaFineRilascio) {
    _dataFineRilascio = gg_mm_aaFineRilascio;
}

void Media::setVisualizzazioni(unsigned int visualizzazioni) {
    _visualizzazioni = visualizzazioni;
}

void Media::setDurataMinuti(unsigned int durata) {
    _durataMinuti = durata;
}

void Media::aggiungiLingua(Lingua lingua) {
    if (find(_lingueDisponibili.begin(), _lingueDisponibili.end(), lingua) == _lingueDisponibili.end()) {
        _lingueDisponibili.push_back(lingua);
    }
}

void Media::aggiungiSottotitolo(Lingua lingua) {
    if (find(_sottotitoliDisponibili.begin(), _sottotitoliDisponibili.end(), lingua) == _sottotitoliDisponibili.end()) {
        _sottotitoliDisponibili.push_back(lingua);
    }
}

void Media::rimuoviLingua(Lingua lingua) {
    auto it = find(_lingueDisponibili.begin(), _lingueDisponibili.end(), lingua);
    if (it != _lingueDisponibili.end()) {
        _lingueDisponibili.erase(it);
    }
}

void Media::rimuoviSottotitolo(Lingua lingua) {
    auto it = find(_sottotitoliDisponibili.begin(), _sottotitoliDisponibili.end(), lingua);
    if (it != _sottotitoliDisponibili.end()) {
        _sottotitoliDisponibili.erase(it);
    }
}

// Metodi get
string Media::getAutore() const{
    return _autore;
}
string Media::getTitolo() const {
    return _titolo;
}

string Media::getDescrizione() const {
    return _descrizione;
}

year_month_day Media::getDataInizioRilascio() const {
    return _dataInizioRilascio;
}

year_month_day Media::getDataFineRilascio() const {
    return _dataFineRilascio;
}

unsigned int Media::getVisualizzazioni() const {
    return _visualizzazioni;
}

unsigned int Media::getDurataMinuti() const {
    return _durataMinuti;
}

vector<Lingua> Media::getLingue() const {
    return _lingueDisponibili;
}

vector<Lingua> Media::getSottotitoli() const {
    return _sottotitoliDisponibili;
}


bool Media::FuoriProduzione() const {
    auto today = year_month_day{floor<days>(system_clock::now())}; 
    return today >= _dataFineRilascio; 
}

unsigned int Media::DurataCampagna() const {
    sys_days inizio = _dataInizioRilascio;
    sys_days fine = _dataFineRilascio;
    return static_cast<unsigned int>((fine-inizio).count());
}


