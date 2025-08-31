#ifndef CINEMA_H
#define CINEMA_H

#include <string>
#include <vector>

class Media;

using namespace std;

class Cinema{
    private:

    string c_nomeCinema;
    string c_copertinaCinema;
    vector<Media*> c_media;
    
    public:
    Cinema(const string &nome, const string &copertina);

    ~Cinema();

    //set
    void setNomeCinema(const string& nome);
    void setCopertinaCinema(const string& copertina);
    void addMedia(Media* media);
    void removeMedia(Media* media);

    //get
    string getNomeCinema()const;
    string getCopertinaCinema()const;
    vector<Media*> getListaMedia()const;
};

#endif //CINEMA_H
