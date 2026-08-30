#ifndef ORCHESTRE_H
#define ORCHESTRE_H 

#include <Arduino.h>
#include "Couleur.h"
#include "Ticker.h"

class Orchestre
{
    private:

    protected:


    public:
        Couleur *c;
        Ticker*& t;
        int Note;
        bool Mouvement;
        // Constructeur
        Orchestre(Couleur *c, Ticker*& t);
        
        // Méthodes (fonctions de la classe)
        void Play( int n=0 );
        void Melodie();
        void Upd();
};

#endif