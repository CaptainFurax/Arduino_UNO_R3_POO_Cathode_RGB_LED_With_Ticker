#include "Couleur.h"

// Constructeur avec liste d'initialisation (plus rapide en C++)
Couleur::Couleur(String state, int r, int v, int b):rouge(state, R,r),vert(state, V,v),bleu(state, B,b)
{
    this->state = ( state == "Off" ) ? false : true;
    ( this->state ) ? this->on() : this->off();
}
//
bool Couleur::equiv( Couleur c )
{
    return( this->rouge.valeur == c.rouge.seuil && this->vert.valeur == c.vert.seuil && this->bleu.valeur == c.bleu.seuil );
}
bool Couleur::fadeto( Couleur c )
{
    this->rouge.slide( c.rouge.seuil );
    this->vert.slide( c.vert.seuil );
    this->bleu.slide( c.bleu.seuil );
    return this->equiv( c );
}
bool Couleur::fadin()
{
    this->rouge.fadin();
    this->vert.fadin();
    this->bleu.fadin();
    return this->plafond();
}
bool Couleur::fadout()
{
    this->rouge.fadout();
    this->vert.fadout();
    this->bleu.fadout();
    return this->plancher();
}
bool Couleur::plafond()
{
    return (this->rouge.seuilMax() && this->vert.seuilMax() && this->bleu.seuilMax() );
}
bool Couleur::plancher()
{
    return (this->rouge.seuilMin() && this->vert.seuilMin() && this->bleu.seuilMin() );
}
void Couleur::on()
{
    if ( !state )
    {
        this->rouge.on(); this->vert.on(); this->bleu.on();
        state = !state;
    }
}
void Couleur::off()
{
    if ( state )
    {
        this->rouge.off(); this->vert.off(); this->bleu.off();
        state = !state;
    }

}
void Couleur::dbug()
{
    Serial.println(String("") + this->rouge.valeur + " - " + this->vert.valeur + " - " + this->bleu.valeur );
}

