#include "Couleur.h"

// Constructeur avec liste d'initialisation (plus rapide en C++)
Couleur::Couleur(bool state, int r, int v, int b):rouge(state, R,r),vert(state, V,v),bleu(state, B,b)
{
    this->state = state;
}
//
void Couleur::set( int r, int v, int b )
{
    this->rouge.set( r );
    this->vert.set( v );
    this->bleu.set( b );
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
    return (this->rouge.seuilHaut() && this->vert.seuilHaut() && this->bleu.seuilHaut() );
}
bool Couleur::plancher()
{
    return (this->rouge.seuilBas() && this->vert.seuilBas() && this->bleu.seuilBas() );
}
void Couleur::on()
{
    this->state = true;
    this->rouge.on(); this->vert.on(); this->bleu.on();
}
void Couleur::off()
{
    state = false;
    this->set();
}
void Couleur::dbug()
{
    Serial.println(String("") + this->rouge.valeur + " - " + this->vert.valeur + " - " + this->bleu.valeur );
}

