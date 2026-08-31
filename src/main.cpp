#include <Arduino.h>
#include "Ticker.h"
#include "Orchestre.h"
#include "Broche.h"
#include "Couleur.h"

int note;

//Couleur c1 = Couleur(true,255,0,255); // 255, 100, 0
//Couleur c2 = Couleur(true,0,255,0); // 0, 100, 255


Couleur pCol = col[0];

Ticker *pOrchesTimer = nullptr;
Orchestre Bernstein = Orchestre(pCol, pOrchesTimer);
Ticker Timer = Ticker( [](){Bernstein.Melodie();}, 15, 0, MILLIS );

void setup()
{
    Serial.begin(115200);
    pOrchesTimer = &Timer;
    note = 100;
    Bernstein.Play(note);
}

void loop()
{
  Bernstein.Upd();
}


