#ifndef PREPARATION_H
#define PREPARATION_H

/**
 * @file preparation.h
 *
 * @brief Déclaration de la classe Preparation
 * @author
 * @version 1.0
 *
 */

#include <QObject>
#include <QStringList>


/**
 * @class Preparation
 * @brief
 * @details
 */
class Preparation : public QObject
{
  private:
    QStringList nomCapsules;
    QStringList nomBoissons;
    bool        capsulePresente;
    bool        tassePresente;

  public:
    Preparation(QObject* parent);
    ~Preparation();
};

#endif // PREPARATION_H
