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

Preparation::Preparation(Cafetiere* cafetiere) :
    QObject(cafetiere), cafetiere(cafetiere), baseDeDonneesPikawa(nullptr),
    nomCapsules(0), nomLongueurs(0), capsulePresente(false), bacVide(false),
    tassePresente(false), niveauEauNecessaire(0)
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

bool Preparation::getbacVide() const
{
    return bacVide;
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
}

void Preparation::setCapsulePresente(bool caspulePresente)
{
    this->capsulePresente = caspulePresente;
}

void Preparation::setbacVide(bool bacVide)
{
    this->bacVide = bacVide;
}

void Preparation::setTassePresente(bool tassePresente)
{
    this->tassePresente = tassePresente;
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
    qDebug() << Q_FUNC_INFO << "niveauEau" << cafetiere->getNiveauEau();
    qDebug() << Q_FUNC_INFO << "niveauEauNecessaire" << niveauEauNecessaire;
    qDebug() << Q_FUNC_INFO << "bacVide" << bacVide;
    qDebug() << Q_FUNC_INFO << "tassePresente" << tassePresente;
    qDebug() << Q_FUNC_INFO << "capsulePresente" << capsulePresente;

    if((cafetiere->getNiveauEau() - niveauEauNecessaire) < 0 || bacVide || !tassePresente || !capsulePresente)
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
