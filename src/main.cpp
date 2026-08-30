#include <Arduino.h>
#include "Ticker.h"
#include "Orchestre.h"
#include "Broche.h"
#include "Couleur.h"

int note;

Couleur c1 = Couleur(false,255,100,0);
Couleur c2 = Couleur(false,0,100,255);
Couleur *pCol = &c2;

Ticker *pOrchesTimer = nullptr;
Orchestre Bernstein = Orchestre(pCol, pOrchesTimer);
Ticker Timer = Ticker( [](){Bernstein.Melodie();}, 15, 0, MILLIS );

void setup()
{
    Serial.begin(115200);
    pCol->on();
    pOrchesTimer = &Timer;
    note = 102;
    Bernstein.Play(note);
}

void loop()
{
  Bernstein.Upd();
}


