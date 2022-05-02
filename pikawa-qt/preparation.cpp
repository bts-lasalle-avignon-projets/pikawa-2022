#include "preparation.h"
#include "basededonnees.h"
#include "cafetiere.h"
#include <QDebug>

/**
 * @file preparation.cpp
 *
 * @brief Définition de la classe Preparation
 * @author Anthony BRYCKAERT
 * @version 0.2
 */

Preparation::Preparation(Cafetiere* cafetiere) :
    QObject(cafetiere), cafetiere(cafetiere), baseDeDonneesPikawa(nullptr),
    nomCapsules(0), nomLongueurs(0), capsulePresente(false), bacPasPlein(false),
    tassePresente(false), niveauEauNecessaire(0)
{
    qDebug() << Q_FUNC_INFO;
    ouvrirBaseDeDonnees();
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

bool Preparation::getBacPasPlein() const
{
    return bacPasPlein;
}

bool Preparation::getTassePresente() const
{
    return tassePresente;
}

int Preparation::getNiveauEauNecessaire() const
{
    return niveauEauNecessaire;
}

int Preparation::getNiveauEauNecessaire(const int& longueurChoisie) const
{
    switch(longueurChoisie)
    {
        case 0:
            return TAILLE_RISTRETTO;
        case 1:
            return TAILLE_ESPRESSO;
        case 2:
            return TAILLE_LUNGO;
    }
    return TAILLE_INCONNUE;
}

void Preparation::setCapsulePresente(bool caspulePresente)
{
    this->capsulePresente = caspulePresente;
}

void Preparation::setBacPasPlein(bool bacPasPlein)
{
    this->bacPasPlein = bacPasPlein;
}

void Preparation::setTassePresente(bool tassePresente)
{
    this->tassePresente = tassePresente;
}

bool Preparation::estPreparationPrete() const
{
    qDebug() << Q_FUNC_INFO << "niveauEau" << cafetiere->getNiveauEau();
    qDebug() << Q_FUNC_INFO << "niveauEauNecessaire" << niveauEauNecessaire;
    qDebug() << Q_FUNC_INFO << "bacPasPlein" << bacPasPlein;
    qDebug() << Q_FUNC_INFO << "tassePresente" << tassePresente;
    qDebug() << Q_FUNC_INFO << "capsulePresente" << capsulePresente;

    if((cafetiere->getNiveauEau() - niveauEauNecessaire) < 0 || !bacPasPlein ||
       !tassePresente || !capsulePresente)
    {
        qDebug() << Q_FUNC_INFO << "Pas prête";
        return false;
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Prête";
        return true;
    }
}

void Preparation::setNiveauEauNecessaire(const int& longueurChoisie)
{
    this->niveauEauNecessaire = getNiveauEauNecessaire(longueurChoisie);
    qDebug() << Q_FUNC_INFO << niveauEauNecessaire;
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

void Preparation::ouvrirBaseDeDonnees()
{
    baseDeDonneesPikawa = BaseDeDonnees::getInstance();
    baseDeDonneesPikawa->ouvrir(NOM_BDD);
}
