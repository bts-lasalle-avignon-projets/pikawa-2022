#ifndef PREPARATION_H
#define PREPARATION_H

#define NOM_BDD "pikawa.sqlite"

/**
 * @file preparation.h
 *
 * @brief Déclaration de la classe Preparation
 * @author
 * @version 0.2
 *
 */

#include <QObject>
#include <QStringList>

class BaseDeDonnees;

/**
 * @class Preparation
 * @brief
 * @details
 */
class Preparation : public QObject
{
    Q_OBJECT
  private:
    BaseDeDonnees* baseDeDonneesPikawa; //!< instance d'un objet BaseDeDonnees

    QStringList nomCapsules;
    QStringList nomBoissons;
    bool        capsulePresente;
    bool        tassePresente;

  public:
    Preparation(QObject *parent = nullptr);
    ~Preparation();
};

#endif // PREPARATION_H
