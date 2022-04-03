#include "cafetiere.h"
#include "ihm.h"
#include "communication.h"
#include "preparation.h"
#include <QDebug>

/**
 * @file cafetiere.cpp
 *
 * @brief Définitionde la classe Cafetiere
 * @author
 * @version 1.0
 *
 */

Cafetiere::Cafetiere(IHMPikawa* ihm) :
    QObject(ihm), ihm(ihm), communication(new Communication(this)),
    preparation(new Preparation(this)), nomCapsules(0), nomBoissons(0),

    capsuleChoisie(0), boissonChoisie(0), niveauEau(0), connectee(false),
    activee(false), capsulePresente(false), tassePresente(false)
{
    qDebug() << Q_FUNC_INFO;
}

Cafetiere::~Cafetiere()
{
    qDebug() << Q_FUNC_INFO;
}

QStringList Cafetiere::getNomcapsules() const
{
    return nomCapsules;
}

QStringList Cafetiere::getNomBoissons() const
{
    return nomBoissons;
}

int Cafetiere::getCaspuleChoisie() const
{
    return capsuleChoisie;
}

int Cafetiere::getBoissonChoisie() const
{
    return boissonChoisie;
}

int Cafetiere::getNiveauEau() const
{
    return niveauEau;
}

bool Cafetiere::getConnectee() const
{
    return connectee;
}

bool Cafetiere::getActivee() const
{
    return activee;
}

bool Cafetiere::getCapsulePresente() const
{
    return capsulePresente;
}

bool Cafetiere::getTassePresente() const
{
    return tassePresente;
}

void Cafetiere::setCapsuleChoisie(const int& capsuleChoisie)
{
    this->capsuleChoisie = capsuleChoisie;
}

void Cafetiere::setBoissonChoisie(const int& boissonChoisie)
{
    this->boissonChoisie = boissonChoisie;
}
void Cafetiere::setNiveauEau(const int& niveauEau)
{
    this->niveauEau = niveauEau;
}

void Cafetiere::connecter()
{
    qDebug() << Q_FUNC_INFO;
}
