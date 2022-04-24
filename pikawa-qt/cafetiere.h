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

// Pour les tests
#define IDENTIFIANT_UTILISATEUR    "tvaira"
#define IDENTIFIANT_UTILISATEUR_ID "1"

class IHMPikawa;
class Communication;
class Preparation;
class BaseDeDonnees;

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
    BaseDeDonnees* baseDeDonneesPikawa; //!< instance d'un objet BaseDeDonnees
    QStringList    nomCapsules;         //!<
    QStringList    nomLongueurs;        //!<
    QStringList
         preferences;    //!< liste des préférences de l'utilisateur connecté
    int  capsuleChoisie; //!<
    int  longueurChoisie;     //!<
    int  niveauEau;           //!<
    int  niveauEauNecessaire; //!<
    bool connectee;           //!<
    bool activee;             //!<
    bool capsulePresente;     //!<
    bool tassePresente;       //!<

    void initialiserNomCapsules();
    void initiatiserNomLongueurs();
    void chargerPreferences(QString identifiantUtilisateur);

  public:
    Cafetiere(IHMPikawa* ihm);
    virtual ~Cafetiere();

    QStringList getNomcapsules() const;
    QStringList getNomLongueurs() const;
    int         getCaspuleChoisie() const;
    int         getLongueurChoisie() const;
    int         getNiveauEau() const;
    bool        getConnectee() const;
    bool        getActivee() const;
    bool        getCapsulePresente() const;
    bool        getTassePresente() const;
    int         getIdCapsule(QString nomCapsule) const;
    int         getniveauEauNecessaire() const;
    QStringList getPreferences() const;
    QString     getCapsulePreferee() const;
    QString     getLongueurPreferee() const;

    void setCapsuleChoisie(const int& capsuleChoisie);
    void setLongueurChoisie(const int& boissonChoisie);
    void setNiveauEau(const int& niveauEau);
    void setNiveauEauNecessaire(const int& niveauEauNecessaire);
    bool estPret();

    /**
     * @enum ChampsTablePreferences
     * @brief Les différentes colonne de la table Preferences
     */
    enum ChampsTablePreferences
    {
        COLONNE_PREFERENCES_ID,                  //!< id
        COLONNE_PREFERENCES_ID_UTILISATEUR,      //!< id de l'utilisateur
        COLONNE_PREFERENCES_NOM_UTILISATEUR,     //!< nom de l'utilisateur
        COLONNE_PREFERENCES_PRENOM_UTILISATEUR,  //!< prénom de l'utilisateur
        COLONNE_PREFERENCES_ID_CAPSULE,          //!< id de la capsule
        COLONNE_PREFERENCES_DESIGNATION_CAPSULE, //!< désignation de la capsule
        COLONNE_PREFERENCES_LIBELLE_CAPSULE,     //!< libellé de la capsule
        COLONNE_PREFERENCES_ID_TYPEBOISSON,      //!< id du type de boisson
        COLONNE_PREFERENCES_TYPE_BOISSON,        //!< type de boisson
        NB_COLONNES_PREFERENCES
    };

    /**
     * @enum NomCaspule
     * @brief Les différents noms de capsule connus
     */
    enum NomCaspule
    {
        Colombia,
        Indonesia,
        Ethiopia,
        Volluto,
        Capriccio,
        Cosi,
        Scuro,
        Vanilla,
        NbCapsules
    };

  public slots:
    void demarrerDecouverte();
    void arreterDecouverte();
    void rafraichirDecouverte();
    void gererConnexion();
    void mettreAJourEtatCafetiere(int  reservoirEau,
                                  int  bacCapsules,
                                  bool etatCapsule,
                                  bool etatTasse);
    void mettreAJourMagasin(QStringList caspulesDisponibles);
    void mettreAJourPreparationCafe(int preparationCafe);

  signals:
    void cafetiereDetectee(QString nom, QString adresse);
    void cafetiereConnectee(QString nom, QString adresse);
    void cafetiereDeconnectee();
    void rechercheTerminee(bool detecte);
};

#endif // CAFETIERE_H
