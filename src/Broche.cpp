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
/*void Broche::fade( unsigned int f )
{
                                     
    if ( !this->fwd )
    { 
        this->valeur++; // On incrémente proprement
        if (this->valeur > this->inter.stop) this->valeur = this->inter.stop; // Équivalent de min() safely
    } 
    else 
    {
        if (this->valeur > 0) this->valeur--; // (évite de passer sous 0 avec un unsigned int !)
        if (this->valeur < this->inter.start) this->valeur = this->inter.start; // Équivalent de max() safely
    }

    // Gestion du changement de direction
    if( !this->fwd )
    {
        if( this->valeur % this->inter.stop == 0 && f == 255 )
            this->fwd = !this->fwd;    
    } 
    else if( this->valeur % this->inter.stop == 0 )
    {
        this->fwd = !this->fwd;
    }

    this->set();  
}*/

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
void Broche::fadin()
{
    if (this->valeur < this->seuil)
        this->valeur++;

    if (this->valeur > this->seuil)
        this->valeur = this->seuil;
    
    this->set();
}
//
void Broche::fadout()
{
    if (this->valeur > 0)
        this->valeur--; 
    
    if (this->valeur < 0)
        this->valeur = 0; 
    
    this->set();
}
//
bool Broche::seuilHaut() { return (this->valeur == this->seuil); }
//
bool Broche::seuilBas() { return (this->valeur == 0); }
