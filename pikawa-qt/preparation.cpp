#include "preparation.h"
#include <QDebug>

Preparation::Preparation() :
    nomCapsules(0), nomBoissons(0), capsulePresente(false), tassePresente(false)
{
    qDebug() << Q_FUNC_INFO;
}

Preparation::~Preparation()
{
    qDebug() << Q_FUNC_INFO;
}
