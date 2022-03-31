#ifndef CAFETIERE_H
#define CAFETIERE_H

/**
 * @file cafetiere.h
 *
 * @brief Déclaration de la classe Cafetiere
 * @author
 * @version 1.0
 *
 */

#include <QVector>
#include <QObject>

class IHMPikawa;
class Communication;
class Preparation;

/**
 * @class Cafetiere
 * @brief
 * @details
 */
class Cafetiere : public QObject
{
    Q_OBJECT
  private:
    IHMPikawa*     ihm;           //!< association avec la fenêtre graphique
    Communication* communication; //!<
    Preparation*   preparation;   //!<

    QVector<QString> nomCapsules;     //!<
    QVector<QString> nomBoissons;     //!<
    int              capsuleChoisie;  //!<
    int              boissonChoisie;  //!<
    int              niveauEau;       //!<
    bool             connectee;       //!<
    bool             activee;         //!<
    bool             capsulePresente; //!<
    bool             tassePresente;   //!<

  public:
    Cafetiere(IHMPikawa* ihm);
    virtual ~Cafetiere();

  public slots:
    void connecter();
};

#endif // CAFETIERE_H
