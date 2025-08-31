#include "Cinema.h"
#include "Media.h"

Cinema::Cinema(const string &nome, const string &copertina):c_nomeCinema(nome),c_copertinaCinema(copertina){}

Cinema::~Cinema(){
    for(Media* m : c_media){
        delete m;
    }
}

//set
void Cinema::setNomeCinema(const string& nome){
    c_nomeCinema = nome;
}
void Cinema::setCopertinaCinema(const string& copertina){
    c_copertinaCinema = copertina;
}
void Cinema::addMedia(Media* media){
    for(Media* m : c_media){
        if(media->getTitolo() == m->getTitolo() && media->getAutore() == m->getAutore()) return;
    }
    c_media.push_back(media);
}
void Cinema::removeMedia(Media* media){
    auto it = find(c_media.begin(), c_media.end(), media);
    if (it != c_media.end()){
        c_media.erase(it);
    }
}

//get
string Cinema::getNomeCinema()const{
    return c_nomeCinema;
}
string Cinema::getCopertinaCinema()const{
    return c_copertinaCinema;
}
vector<Media*> Cinema::getListaMedia()const{
    return c_media;
}