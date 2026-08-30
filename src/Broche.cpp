#include "Broche.h"

Broche::Broche(bool state, int pin, unsigned int valeur):pin(pin)
{
    pinMode(this->pin, OUTPUT);
    this->fwd = state;
    this->valeur = valeur;
    ( state ) ? this->set( valeur ) : this->off();
    this->inter = {0, valeur, valeur - 0};
}
//
void Broche::set(int v)
{
    if ( v > 0 )
        this->fwd = true;

    this->valeur = v;
    analogWrite(this->pin, this->valeur);
}
void Broche::on()
{
    this->set( this->inter.amp );
}
//
void Broche::off()
{
    this->set(0);
}
//
void Broche::fade( unsigned int f )
{
    // Affiche le debug avant toute modification
    // AJOUTER DES PARENTHÈSES AUTOUR DU MODULO :
    // Serial.println(String("val : ") + this->valeur + " - " + f + " % " + (this->valeur % this->inter.stop) );
                                     
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

    this->set( this->valeur );  
}


void Broche::fadin()
{
    if (this->valeur < this->inter.stop)
        this->valeur++;

    if (this->valeur > this->inter.stop)
        this->valeur = this->inter.stop;
    
    if ( this->seuilHaut() )
        this->fwd = !this->fwd;

    this->set( this->valeur );
}
void Broche::fadout()
{
    if (this->valeur > this->inter.start)
        this->valeur--; 
    
    if (this->valeur < this->inter.start)
        this->valeur = this->inter.start; 
    
    if ( this->seuilBas() )
        this->fwd = !this->fwd;

    this->set( this->valeur );
}
bool Broche::seuilHaut()
{
    return (this->valeur == this->inter.stop);
}
bool Broche::seuilBas()
{
    return (this->valeur == this->inter.start);
}
