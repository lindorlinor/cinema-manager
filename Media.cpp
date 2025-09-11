#include "Media.h"
#include "EnumClasses.h"
#include <iostream>
#include <algorithm>

Media::~Media() {}


Media::Media(const string &titolo, const string &descrizione, 
             year_month_day gg_mm_aaInizioRilascio,
             year_month_day gg_mm_aaFineRilascio, 
             unsigned int durataMinuti, 
             Formato formato, Risoluzione risoluzione,
             const string &autore, const string &path)
    : m_titolo(titolo),
      m_descrizione(descrizione),
      m_dataInizioRilascio( gg_mm_aaInizioRilascio.ok() ? gg_mm_aaInizioRilascio : today() ),
      m_dataFineRilascio( gg_mm_aaFineRilascio.ok() ? 
                          (gg_mm_aaFineRilascio < (gg_mm_aaInizioRilascio.ok()?gg_mm_aaInizioRilascio:today())
                             ? (gg_mm_aaInizioRilascio.ok()?gg_mm_aaInizioRilascio:today())
                             : gg_mm_aaFineRilascio)
                          : (gg_mm_aaInizioRilascio.ok()?gg_mm_aaInizioRilascio:today()) ),
      m_durataMinuti(durataMinuti),
      m_formato(formato),
      m_risoluzione(risoluzione),
      m_autore(autore),
      m_imPath(path),
      m_dataLastViewUpdate( gg_mm_aaInizioRilascio.ok() ? gg_mm_aaInizioRilascio : today() ),
      m_visualizzazioni(0)
{
    IncrementaVisualizzazioni();
}


bool Media::FuoriProduzione() const{
    auto today = year_month_day{floor<days>(system_clock::now())};
    return today > m_dataFineRilascio;
}

unsigned int Media::DurataCampagna() const{
    sys_days inizio = m_dataInizioRilascio;
    sys_days fine = m_dataFineRilascio;
    return static_cast<unsigned int>((fine - inizio).count() +1);
}

void Media::aggiungiLingua(Lingua lingua){
    if (find(m_lingueDisponibili.begin(), m_lingueDisponibili.end(), lingua) == m_lingueDisponibili.end())
        m_lingueDisponibili.push_back(lingua);
}

void Media::aggiungiSottotitolo(Lingua lingua){
    if (find(m_sottotitoliDisponibili.begin(), m_sottotitoliDisponibili.end(), lingua) == m_sottotitoliDisponibili.end())
        m_sottotitoliDisponibili.push_back(lingua);

}

void Media::rimuoviLingua(Lingua lingua){
    auto it = find(m_lingueDisponibili.begin(), m_lingueDisponibili.end(), lingua);
    if (it != m_lingueDisponibili.end())
        m_lingueDisponibili.erase(it);
}

void Media::rimuoviSottotitolo(Lingua lingua){
    auto it = find(m_sottotitoliDisponibili.begin(), m_sottotitoliDisponibili.end(), lingua);
    if (it != m_sottotitoliDisponibili.end())
        m_sottotitoliDisponibili.erase(it);
}

void Media::IncrementaVisualizzazioni()
{
    // per poter facilitare i calcoli sulla data
    sys_days inizio = sys_days{m_dataLastViewUpdate};
    sys_days fine = sys_days{m_dataFineRilascio};
    sys_days oggi = floor<days>(system_clock::now());

    std::srand(std::time(nullptr)); // seme basato sull’orario attuale

    for (sys_days it = inizio; it <= oggi && it <= fine; it += days{1}){
        unsigned int numero = std::rand() % 1201; // al massimo 1200 visualizzazioni al giorno
        setVisualizzazioni(getVisualizzazioni() + numero);

        if (it + days{1} == fine)
            m_dataLastViewUpdate = m_dataFineRilascio;
        else if (it + days{1} == oggi)
            m_dataLastViewUpdate = year_month_day{oggi};
    }
}

void Media::setDataInizioRilascio(year_month_day gg_mm_aaInizioRilascio) {
    if(m_dataInizioRilascio>m_dataFineRilascio)
        m_dataInizioRilascio = m_dataFineRilascio;
    m_dataInizioRilascio = gg_mm_aaInizioRilascio;
}


// Metodi set

void Media::setAutore(const string& autore){
    m_autore = autore;
}
void Media::setTitolo(const string& titolo) {
    m_titolo = titolo;
}

void Media::setFormato(const Formato& formato) {
    m_formato = formato;
}

void Media::setRisoluzione(const Risoluzione& risoluzione) {
    m_risoluzione = risoluzione;
}

void Media::setDescrizione(const string& descrizione) {
    m_descrizione = descrizione;
}

void Media::setPath(const string& path) {
    m_imPath = path;
}

void Media::setDataFineRilascio(year_month_day gg_mm_aaFineRilascio){
    if(gg_mm_aaFineRilascio<getDataInizioRilascio())
        m_dataFineRilascio = m_dataInizioRilascio;
    else
        m_dataFineRilascio = gg_mm_aaFineRilascio;
}

void Media::setDurataMinuti(unsigned int durata){
    m_durataMinuti = durata;
}

void Media::setVisualizzazioni(unsigned int visualizzazioni){
    m_visualizzazioni = visualizzazioni;
}


// Metodi get
string Media::getAutore() const{
    return m_autore;
}
string Media::getTitolo() const {
    return m_titolo;
}

string Media::getDescrizione() const {
    return m_descrizione;
}

vector<Lingua> Media::getLingue() const {
    return m_lingueDisponibili;
}

vector<Lingua> Media::getSottotitoli() const {
    return m_sottotitoliDisponibili;
}

year_month_day Media::getDataInizioRilascio() const
{
    return m_dataInizioRilascio;
}

year_month_day Media::getDataFineRilascio() const{
    return m_dataFineRilascio;
}

year_month_day Media::getDataLastViewUpdate() const{
    return m_dataLastViewUpdate;
}

unsigned int Media::getVisualizzazioni() const{
    return m_visualizzazioni;
}


unsigned int Media::getDurataMinuti() const{
    return m_durataMinuti;
}

Formato Media::getFormato() const{
    return m_formato;
}

Risoluzione Media::getRisoluzione() const{
    return m_risoluzione;
}

string Media::getImPath() const{
    return m_imPath;
}
