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
    int         boissonChoisie;  //!<
    int         niveauEau;       //!<
    bool        connectee;       //!<
    bool        activee;         //!<
    bool        capsulePresente; //!<
    bool        tassePresente;   //!<

    QStringList getNomcapsules() const;
    QStringList getNomBoissons() const;
    int         getCaspuleChoisie() const;
    int         getBoissonChoisie() const;
    int         getNiveauEau() const;
    bool        getConnectee() const;
    bool        getActivee() const;
    bool        getCapsulePresente() const;
    bool        getTassePresente() const;

    void setCapsuleChoisie(const int& capsuleChoisie);
    void setBoissonChoisie(const int& boissonChoisie);
    void setNiveauEau(const int& niveauEau);

  public:
    Cafetiere(IHMPikawa* ihm);
    virtual ~Cafetiere();

  public slots:
    void demarrerDecouverte();
    void arreterDecouverte();
    void rafraichirDecouverte();
    void gererConnexion();

  signals:
    void cafetiereDetectee(QString nom, QString adresse);
    void cafetiereConnectee(QString nom, QString adresse);
    void cafetiereDeconnectee();
    void rechercheTerminee(bool detecte);
};

#endif // CAFETIERE_H
