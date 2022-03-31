#include "cafetiere.h"
#include "communication.h"

#include <QVector>

Cafetiere::Cafetiere() :
    nomCapsules(0), nomBoissons(0), capsuleChoisie(0), boissonChoisie(0),
    niveauEau(0), connectee(false), activee(false), capsulePresente(false),
    tassePresente(false)
{
}

Cafetiere::~Cafetiere()
{
}

void Cafetiere::activerLaDecouverte()
{
    communication->activerLaDecouverte();
}
