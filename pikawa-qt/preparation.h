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
    QStringList nomLongueurs;
    bool        capsulePresente;
    bool        tassePresente;

    void chargerNomCapsules();
    void chargerLongeurBoissons();

  public:
    Preparation(QObject *parent = nullptr);
    ~Preparation();

    QStringList getNomCapsules() const;
    QStringList getNomLongueurs() const;
};

#endif // PREPARATION_H
