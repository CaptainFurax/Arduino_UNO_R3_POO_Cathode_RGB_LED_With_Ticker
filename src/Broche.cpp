#include "Broche.h"

Broche::Broche(String state, int pin, unsigned int valeur):pin(pin)
{
    pinMode(this->pin, OUTPUT);
    this->seuil = valeur;
    ( state == "Off") ? this->off():this->on();
}
//
void Broche::set(int v)
{
    this->valeur = v;
    this->set();
}
//
void Broche::set() { analogWrite(this->pin, this->valeur); }
//
void Broche::on() { this->set(this->seuil); }
//
void Broche::off() { this->set(0); }
//
void Broche::slide( unsigned int v )
{
    if ( this->valeur < v )
        this->valeur++;

    if ( this->valeur > v )
        this->valeur--;

    if ( this->valeur == v )
        this->seuil = v;

    this->set();
}
//
void Broche::fadin() { this->slide( this->seuil ); }
//
void Broche::fadout() { this->slide(); }
//
bool Broche::seuilMax() { return (this->valeur == this->seuil); }
//
bool Broche::seuilMin() { return (this->valeur == 0); }
