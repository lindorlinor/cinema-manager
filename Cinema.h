#ifndef CINEMA_H
#define CINEMA_H

#include <string>
#include <list>

class Media;

using namespace std;

/**
 * @brief Rappresenta un cinema con una lista di media (film, trailer, ecc.)
 * 
 * La classe gestisce il nome, la copertina e la lista di Media associati.
 */
class Cinema{
    private:

    string c_nomeCinema;
    string c_copertinaCinema;
    list<Media*> c_media;
    
    public:
    Cinema(const string &nome, const string &copertina);

    /**
     * @brief Distruttore del cinema
     * 
     * Disaccoppia tutti i trailer dai film e tutte le puntate dai podcast
     * prima di eliminare i media, per evitare dangling pointer e doppi delete.
     * 
     * @see Film::disaccoppiaTrailer @see Podcast::disaccoppiaPuntata
     */
    ~Cinema();

    //set
    void setNomeCinema(const string& nome);
    void setCopertinaCinema(const string& copertina);
    void addMedia(Media* media);
    void removeMedia(Media* media);

    //get
    string getNomeCinema()const;
    string getCopertinaCinema()const;
    list<Media*> getListaMedia()const;
};

#endif //CINEMA_H
