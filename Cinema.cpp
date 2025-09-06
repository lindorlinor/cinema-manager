#include "Cinema.h"
#include "Media.h"
#include "Film.h"
#include "Podcast.h"
#include "Trailer.h"
#include "Puntata.h"
#include <QDebug>

Cinema::Cinema(const string &nome, const string &copertina):c_nomeCinema(nome),c_copertinaCinema(copertina){}

Cinema::~Cinema(){
    for(Media* m : c_media){

        if(Film* film = dynamic_cast<Film*>(m)) //disaccoppio tutti i trailer prima di eliminarli
            for(Trailer* t : film->getTrailers())
                film->disaccoppiaTrailer(t);

        if(Podcast* podcast = dynamic_cast<Podcast*>(m)) //disaccoppio tutte le puntate prima di eliminarle
            for(Puntata* p : podcast->getElencoPuntate())
                podcast->disaccoppiaPuntata(p);
    }

    for(Media* m : c_media) delete m;
    c_media.clear();  //dopo che tutti i media trailer e puntata sono stati disaccoppiati, elimino tutto evitando doppio delete 
     
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
list<Media*> Cinema::getListaMedia()const{
    return c_media;
}