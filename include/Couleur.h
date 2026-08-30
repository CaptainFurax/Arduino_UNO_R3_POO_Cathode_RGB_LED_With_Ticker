#ifndef COULEUR_H
#define COULEUR_H

#include <Arduino.h> // Obligatoire sous PIO pour utiliser le framework Arduino
#include "Broche.h" 

const int R = 9; const int V = 10; const int B = 11;

class Couleur
{
    private:

    protected:


    public:

        bool state;
        Broche rouge;
        Broche vert;
        Broche bleu;
        
        // Constructeur
        Couleur(bool, int r=0,int v=0,int b=0);
        
        // Méthodes (fonctions de la classe)
        void set(int r=0,int v=0,int b=0);
        bool fadin();
        bool fadout();
        bool plafond();
        bool plancher();
        void on();
        void off();
        void dbug();
};

#endif