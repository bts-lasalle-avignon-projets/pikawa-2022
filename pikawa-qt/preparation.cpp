#include "preparation.h"
#include "basededonnees.h"
#include <QDebug>

/**
 * @file preparation.cpp
 *
 * @brief Définition de la classe Preparation
 * @author
 * @version 0.2
 *
 */

Preparation::Preparation(QObject* parent) : QObject(parent), baseDeDonneesPikawa(nullptr), nomCapsules(0), nomLongueurs(0),capsulePresente(false), tassePresente(false)
{
    qDebug() << Q_FUNC_INFO;
    baseDeDonneesPikawa = BaseDeDonnees::getInstance();
    baseDeDonneesPikawa->ouvrir(NOM_BDD);
    chargerNomCapsules();
    chargerLongeurBoissons();
}

Preparation::~Preparation()
{
    qDebug() << Q_FUNC_INFO;
}

QStringList Preparation::getNomCapsules() const
{
    return nomCapsules;
}

QStringList Preparation::getNomLongueurs() const
{
    return nomLongueurs;
}


void Preparation::chargerNomCapsules()
{
    baseDeDonneesPikawa->recuperer("SELECT designation FROM Capsule", nomCapsules);
}

void Preparation::chargerLongeurBoissons()
{
    baseDeDonneesPikawa->recuperer("SELECT type FROM TypeBoisson", nomLongueurs);
}
