#ifndef CAFETIERE_H
#define CAFETIERE_H

/**
 * @file cafetiere.h
 *
 * @brief Déclaration de la classe Cafetiere
 * @author
 * @version 0.2
 *
 */

#include <QObject>
#include <QStringList>

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

    QStringList nomCapsules;     //!<
    QStringList nomBoissons;     //!<
    int         capsuleChoisie;  //!<
    int         longueurChoisie;  //!<
    int         niveauEau;       //!<
    bool        connectee;       //!<
    bool        activee;         //!<
    bool        capsulePresente; //!<
    bool        tassePresente;   //!<

    QStringList getNomcapsules() const;
    QStringList getNomBoissons() const;
    int         getCaspuleChoisie() const;
    int         getLongueurChoisie() const;
    int         getNiveauEau() const;
    bool        getConnectee() const;
    bool        getActivee() const;
    bool        getCapsulePresente() const;
    bool        getTassePresente() const;

  public:
    Cafetiere(IHMPikawa* ihm);
    virtual ~Cafetiere();

    void setCapsuleChoisie(const int& capsuleChoisie);
    void setLongueurChoisie(const int& boissonChoisie);
    void setNiveauEau(const int& niveauEau);

  public slots:
    void demarrer();
    void connecter();

  signals:
    void cafetiereDetectee(QString nom, QString adresse);
};

#endif // CAFETIERE_H
