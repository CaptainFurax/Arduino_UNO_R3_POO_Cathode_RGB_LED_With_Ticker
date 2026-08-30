## LED RGB avec VSCode & PlatFormIO avec Ticker [ Work in Progress ] 
![Das Gross Scheme !](./rsc/001_Arduino_Uno_R3_POO_Cathode_RGB_LED_With_Ticker.png "Arduino Uno R3 Anode RGB Led")

### <ins>Rsc :</ins>

* Langage C/CPP via [PlatFormIO](https://platformio.org/platformio-ide) [ Greffon VSCode ]
* Orienté POO avec une classe *'Couleur'* composée de trois objets *'Broche'* et une classe orchestre gérant les interruptions et leurs retours.
* Coté librairie, Ticker.h de [Stefan Staub](https://github.com/sstaub/Ticker) téléchargée et installée sans peine dans PIO, section *"librairies"* ou dans le dossier 'lib' du projet.
* Une LED RGB à cathode [ Dans mon cas un module Velleman VMA-307 qui fait très bien le job ]
* Sinon, sans ce module : 3 x résistances, 150Ω [ Rouge ], 100Ω [ vert et bleu ] et une LED RGB à cathode
* Enfin un µControleur [Arduino](https://www.e-techno-tutos.com/2018/05/28/arduino-brochage/) ( ou autre...mais code ci apres à adapter )

*`Et...l'esprit de la bidouille !`* 

### <ins>Specs :</ins>

La LED RGB à `cathode a la particularité de recevoir la masse sur sa broche la plus longue.`</br> Tandis que les 3 autres controlent les signaux RGB via la masse [ Signal 'HIGH'/1 ou modulé en ~pwm ]   
Les signaux se combinent et la led ne limite pas à trois couleurs : Rouge, Vert et Bleu.</br>
En digital pur 0 ou 1 [ 0 : Allumée, 1 : Eteint ] avec 3 fils on a `2³ = 8 possibilités [ soit 7 couleurs et une à Off ! ]`</br>
Quand en *'analogique' simulé*, le PWM : on a 256 possibilités de signaux.</br>
Ce qui donne pour trois canaux, 256³ => `16 777 216 nuances !`

### <ins>Le brochage: </ins>
 
`R  |  G  |  B  | Masse(GND)`
               
Avec ce module [VMA-307](https://www.velleman.eu/products/view/module-rgb-led-compatible-arduino-2-pcs-vma307/?id=435528&lang=fr), c'est le brochage qui me correspond( *avantage du module : pas besoin de jouer avec des resistances* )
Sans vouloir faire de la pub, ils ont de supers produits : y compris d'excellents clones Arduino identifiés comme des *'Arduino natifs'* cad d'origine par PIO avec [l'Atmega 'broché'](https://www.velleman.eu/products/view/carte-de-developpement-atmega328-uno-wpb100/?id=459124) à l'ancienne :-)

Le VMA-307 : 
![Das Gross Scheme !](./rsc/vma307.jpg "Arduino Uno R3 Anode RGB Led")


*Avec une LED RGB standard, je pense que nous aurions plutot besoin des resistance suivantes :*

* *Rouge : 3V[5V-(1.8+2.2)/2]   / 0.02A[20mA] => 150Ω*
* *Vert  : 1.8V[5V-(3.2+3.4)/2] / 0.02A       =>  90Ω*
* *Bleu  : 1.8V[5V-(3.2+3.4)/2] / 0.02A       =>  90Ω*

*`Ce qui ajusterait grandement la précision des couleurs en Analogique.`*

## Côté Code - Morceaux choisis

* Des Classes *`'Broches'`* et *`'Couleurs'`*(une couleur a trois broches, RGB - Une couleur a 3 broches...ou une LED a besoin de 3 signaux pour generer une couleur, c'est purement sémantique)
* La Broche stocke GPIO, valeur pwm, seuils et méthodes pour influer dessus.
* La Couleur les combine et fait office d'interface avec l'Orchestre en influant sur les signaux et en faisant remonter l'etat (ex : fade-in atteint )
* La classe *`'Orchestre'`* :
  * Elle gere les interruptions et les enchainements une fois les actions atteintes.
  * Dans la boucle loop principale, seule la methode *'Upd()'* apparait. 
  * Orchestre s'appuie grandement sur Ticker.h via une référence sur pointeur(*Ticker*& t*)
  * In fine/a venir -> des sequences de codes jouées par la classe Orchestre( fade-in, fade-out, transition d'une couleur a une autre, etc...)
  
C'est un 'Work in Progress' pour le moment :-)


```cpp 
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
```
'Melodie' est la méthode passée comme fonction au timer Ticker et appelée toutes les 15ms. En fonction de la valeur de sa note elle fait 'jouer' telle ou telle méthode à la couleur.
Concrêtement, Melodie est encapsulée dans le Timer et elle oriente les actions a mener. L'action finie, un flag est renseigné. 
De son coté Upd() reagit à ce flag et joue la 'partition' avec l'action suivante.
L'exemple ci dessus, fait un 'fade-out', puis une fois celui ci atteint, declenche un 'fade-in' et inversement.

Coté main loop, seul Upd() apparait !

```cpp
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
```