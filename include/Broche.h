#ifndef BROCHE_H
#define BROCHE_H

#include <Arduino.h> // Obligatoire sous PIO pour utiliser le framework Arduino

struct Interval
{
    unsigned int start;
    unsigned int stop;
    unsigned int amp;
};

class Broche
{
    private:

    protected:


    public:
        int pin;
        unsigned int valeur;
        Interval inter;
        bool fwd;
        // Constructeur
        Broche(bool state, int pin, unsigned int valeur);

        // Méthodes (fonctions de la classe)
        void on();
        void off();
        void set( int );  
        void fade( unsigned int );
        void fadin();
        void fadout();
        bool seuilHaut();
        bool seuilBas();
};

#endif