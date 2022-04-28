#include "preparation.h"
#include "basededonnees.h"
#include "cafetiere.h"
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
    QObject(parent), cafetiere(nullptr), baseDeDonneesPikawa(nullptr),
    nomCapsules(0), nomLongueurs(0), capsulePresente(false), bacPlein(false),
    tassePresente(false), niveauEau(0)
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

bool Preparation::getCapsulePresente() const
{
    return capsulePresente;
}

bool Preparation::getBacPlein() const
{
    return bacPlein;
}

bool Preparation::getTassePresente() const
{
    return tassePresente;
}

int Preparation::getNiveauEau() const
{
    return niveauEau;
}

void Preparation::setCapsulePresente(bool caspulePresente)
{
    this->capsulePresente = caspulePresente;
}

void Preparation::setBacPlein(bool bacPlein)
{
    this->bacPlein = bacPlein;
}

void Preparation::setTassePresente(bool tassePresente)
{
    this->tassePresente = tassePresente;
}

void Preparation::setNiveauEau(int niveauEau)
{
    this->niveauEau = niveauEau;
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

bool Preparation::estPreparationPrete() const
{
    /**
     * @todo A reparer
     * int niveauEau = cafetiere->getniveauEauNecessaire();
    qDebug() << Q_FUNC_INFO << "niveau Eau cafetiere" << niveauEau;
    //(niveauEau - cafetiere->getniveauEauNecessaire()) <= 0 &&
    */
    qDebug() << Q_FUNC_INFO << "bacPlein" << bacPlein;
    qDebug() << Q_FUNC_INFO << "tassePresente" << tassePresente;
    qDebug() << Q_FUNC_INFO << "capsulePresente" << capsulePresente;

    if(bacPlein || !tassePresente || !capsulePresente)
    {
        return false;
    }

    else
    {
        return true;
    }
}

/** Cafetiere* Preparation::getCafetiere() const
{
    return cafetiere;
}

void Preparation::setCafetiere(Cafetiere* cafetiere)
{
    this->cafetiere = cafetiere;
}
*/
