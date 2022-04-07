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

Preparation::Preparation(QObject* parent) : QObject(parent), baseDeDonneesPikawa(nullptr), capsulePresente(false), tassePresente(false)
{
    qDebug() << Q_FUNC_INFO;
    baseDeDonneesPikawa = BaseDeDonnees::getInstance();
    baseDeDonneesPikawa->ouvrir(NOM_BDD);
}

Preparation::~Preparation()
{
    qDebug() << Q_FUNC_INFO;
}
