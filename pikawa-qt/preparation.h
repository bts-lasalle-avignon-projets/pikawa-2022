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

#include <QStringList>

/**
 * @class Preparation
 * @brief
 * @details
 */
class Preparation
{
  private:
    QStringList nomCapsules;
    QStringList nomBoissons;
    bool        capsulePresente;
    bool        tassePresente;

  public:
    Preparation();
    ~Preparation();
};

#endif // PREPARATION_H
