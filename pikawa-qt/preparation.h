#ifndef PREPARATION_H
#define PREPARATION_H

/**
 * @file preparation.h
 *
 * @brief Déclaration de la classe Preparation
 * @author
 * @version 0.2
 *
 */

#include <QObject>
#include <QVector>
#include <QString>
#include <QStringList>

#define TAILLE_RISTRETTO 30
#define TAILLE_ESPRESSO  60
#define TAILLE_LUNGO     110

class BaseDeDonnees;

/**
 * @class Preparation
 * @brief
 * @details
 */

#define NIVEAU_EAU_MAX      800
#define NIVEAU_EAU_MIN_CAFE 30

class Cafetiere;

class Preparation : public QObject
{
    Q_OBJECT
  private:
    Cafetiere*       cafetiere;           //!< instance d'un objet Cafetiere
    BaseDeDonnees*   baseDeDonneesPikawa; //!< instance d'un objet BaseDeDonnees
    QVector<QString> nomCapsules;
    QVector<QString> nomLongueurs;
    bool             capsulePresente;
    bool             bacVide;
    bool             tassePresente;
    int              niveauEauNecessaire; //!<

    void chargerNomCapsules();
    void chargerLongeurBoissons();

  public:
    Preparation(Cafetiere* cafetiere = nullptr);
    ~Preparation();

    QStringList getNomCapsules() const;
    QStringList getNomLongueurs() const;
    bool        getCapsulePresente() const;
    bool        getbacVide() const;
    bool        getTassePresente() const;
    int         getNiveauEauNecessaire() const;
    int         getNiveauEauNecessaire(const int& longueurChoisie) const;
    void        setCapsulePresente(bool capsulePresente);
    void        setbacVide(bool bacVide);
    void        setTassePresente(bool tassePresente);
    bool        estPreparationPrete() const;
    void        setNiveauEauNecessaire(const int& longueurChoisie);

  public slots:

  signals:
    void preparationPasPrete(int  niveauEau,
                             bool bacVide,
                             bool tassePresente,
                             bool capsulePresente);
};

#endif // PREPARATION_H
