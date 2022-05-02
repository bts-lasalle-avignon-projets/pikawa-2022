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

/**
 * @file preparation.h
 *
 * @brief Déclaration de la classe IHMPikawa
 * @author Anthony BRYCKAERT
 * @version 0.2
 */

#define TAILLE_INCONNUE  -1
#define TAILLE_RISTRETTO 30
#define TAILLE_ESPRESSO  60
#define TAILLE_LUNGO     110

class BaseDeDonnees;

#define NIVEAU_EAU_MAX      800
#define NIVEAU_EAU_MIN_CAFE 30

class Cafetiere;

/**
 * @class Preparation
 * @brief Gére la préparation d'un café
 */
class Preparation : public QObject
{
    Q_OBJECT
  private:
    Cafetiere*       cafetiere;           //!< instance d'un objet Cafetiere
    BaseDeDonnees*   baseDeDonneesPikawa; //!< instance d'un objet BaseDeDonnees
    QVector<QString> nomCapsules;         //!< liste des noms de capsules
    QVector<QString> nomLongueurs; //!< liste des longueurs de préparation
    bool capsulePresente; //!< au moins une capsule est présente dans le magasin
    bool bacPasPlein;     //!< le bac n'est pas complètement plein
    bool tassePresente;   //!< une tasse est détectée
    int  niveauEauNecessaire; //!< niveau d'eau minimum pour préparer un café

    void chargerNomCapsules();
    void chargerLongeurBoissons();
    void ouvrirBaseDeDonnees();

  public:
    Preparation(Cafetiere* cafetiere = nullptr);
    ~Preparation();

    QStringList getNomCapsules() const;
    QStringList getNomLongueurs() const;
    bool        getCapsulePresente() const;
    bool        getBacPasPlein() const;
    bool        getTassePresente() const;
    int         getNiveauEauNecessaire() const;
    int         getNiveauEauNecessaire(const int& longueurChoisie) const;
    void        setCapsulePresente(bool capsulePresente);
    void        setBacPasPlein(bool bacPasPlein);
    void        setTassePresente(bool tassePresente);
    bool        estPreparationPrete() const;
    void        setNiveauEauNecessaire(const int& longueurChoisie);

  public slots:

  signals:
    void preparationPasPrete(int  niveauEau,
                             bool bacPasPlein,
                             bool tassePresente,
                             bool capsulePresente);
};

#endif // PREPARATION_H
