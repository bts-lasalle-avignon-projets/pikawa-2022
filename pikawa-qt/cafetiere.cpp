#include "cafetiere.h"
#include "ihm.h"
#include "communication.h"
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
    QObject(ihm), ihm(ihm), communication(nullptr), preparation(nullptr),
    nomCapsules(0), nomBoissons(0), capsuleChoisie(0), boissonChoisie(0),
    niveauEau(0), connectee(false), activee(false), capsulePresente(false),
    tassePresente(false)
{
    qDebug() << Q_FUNC_INFO;
    /**
     * @todo Instancier les objets preparation et communication
     */
}

Cafetiere::~Cafetiere()
{
    qDebug() << Q_FUNC_INFO;
}

QVector<QString> Cafetiere::getNomcapsules() const
{
    return nomCapsules;
}

QVector<QString> Cafetiere::getNomBoissons() const
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

void Cafetiere::setCapsuleChoisie(int& capsuleChoisie)
{
    this->capsuleChoisie = capsuleChoisie;
}

void Cafetiere::setBoissonChoisie(int& boissonChoisie)
{
    this->boissonChoisie = boissonChoisie;
}
void Cafetiere::setNiveauEau(int& niveauEau)
{
    this->niveauEau = niveauEau;
}

void Cafetiere::connecter()
{
    qDebug() << Q_FUNC_INFO;
}
