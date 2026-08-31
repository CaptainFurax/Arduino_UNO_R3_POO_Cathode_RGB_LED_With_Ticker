#ifndef BROCHE_H
#define BROCHE_H

#include <Arduino.h> // Obligatoire sous PIO pour utiliser le framework Arduino

class Broche
{
    private:

    protected:


    public:
        int pin;
        unsigned int valeur;
        unsigned int seuil;
        // Constructeur
        Broche(String state, int pin, unsigned int valeur);

        // Méthodes (fonctions de la classe)
        void on();
        void off();
        void set();
        void set( int );  
        void slide( unsigned int );
        void fade( unsigned int );
        void fadin();
        void fadout();
        bool seuilMax();
        bool seuilMin();
};

#endif