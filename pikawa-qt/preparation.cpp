#include "preparation.h"
#include <QDebug>

/**
 * @file preparation.cpp
 *
 * @brief Définition de la classe Preparation
 * @author
 * @version 1.0
 *
 */

Preparation::Preparation(QObject* parent) : QObject(parent), capsulePresente(false), tassePresente(false)
{
    qDebug() << Q_FUNC_INFO;
}

Preparation::~Preparation()
{
    qDebug() << Q_FUNC_INFO;
}
