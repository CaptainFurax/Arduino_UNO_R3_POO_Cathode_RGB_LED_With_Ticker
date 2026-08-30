#include "Orchestre.h"
#include "Couleur.h"
#include "Ticker.h"

Orchestre::Orchestre( Couleur *c, Ticker*& t):c(c), t(t)
{
}

void Orchestre::Play( int note )
{
    this->Note = note;
    this->t->start();
}
void Orchestre::Upd()
{
    this->t->update();
    if ( this->Mouvement ) 
    {
        this->Note--;
        if ( this->Note < 101 )
            this->Note = 102;
        this->Mouvement = false;
    }
}

void Orchestre::Melodie()
{
  if ( this->t != NULL )
  {
    switch (this->Note)
    {
      case 101:
        this->Mouvement = this->c->fadin();
      break;

      case 102:
        this->Mouvement = this->c->fadout();
      break;
      
      default:
      break;
    }
  } 
}