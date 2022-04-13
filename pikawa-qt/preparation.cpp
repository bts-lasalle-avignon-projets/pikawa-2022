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

Preparation::Preparation(QObject* parent) :
    QObject(parent), baseDeDonneesPikawa(nullptr), nomCapsules(0),
    nomLongueurs(0), capsulePresente(false), tassePresente(false)
{
    qDebug() << Q_FUNC_INFO;
    baseDeDonneesPikawa = BaseDeDonnees::getInstance();
    baseDeDonneesPikawa->ouvrir(NOM_BDD);
    chargerNomCapsules();
    chargerLongeurBoissons();
}

Preparation::~Preparation()
{
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

QStringList Preparation::getNomCapsules() const
{
    QStringList listeNomCapsules;
    for(int i = 0; i < nomCapsules.size(); ++i)
        listeNomCapsules << nomCapsules.at(i);
    qDebug() << Q_FUNC_INFO << listeNomCapsules;
    return listeNomCapsules;
}

QStringList Preparation::getNomLongueurs() const
{
    QStringList listeNomLongueurs;
    for(int i = 0; i < nomLongueurs.size(); ++i)
        listeNomLongueurs << nomLongueurs.at(i);
    qDebug() << Q_FUNC_INFO << listeNomLongueurs;
    return listeNomLongueurs;
}

void Preparation::chargerNomCapsules()
{
    qDebug() << Q_FUNC_INFO;
    baseDeDonneesPikawa->recuperer("SELECT designation FROM Capsule;",
                                   nomCapsules);
}

void Preparation::chargerLongeurBoissons()
{
    qDebug() << Q_FUNC_INFO;
    baseDeDonneesPikawa->recuperer("SELECT type FROM TypeBoisson;",
                                   nomLongueurs);
}
