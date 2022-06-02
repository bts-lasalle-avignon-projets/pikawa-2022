#ifndef CAFETIERE_H
#define CAFETIERE_H

/**
 * @file cafetiere.h
 *
 * @brief Déclaration de la classe Cafetiere
 * @author Anthony BRYCKAERT
 * @version 1.1
 */

#include <QObject>
#include <QStringList>

// Pour les tests
#define IDENTIFIANT_UTILISATEUR    "abryckaert"
#define IDENTIFIANT_UTILISATEUR_ID "3"

#define TAILLE_RESERVOIR 800

#define CAFE_PRET                    0
#define CAFE_EN_PREPARATION          1
#define ERREUR_PREPARATION_CAFE      2
#define NOMBRE_CAFE_AVANT_DETARTRAGE 75

class IHMPikawa;
class Communication;
class Preparation;
class BaseDeDonnees;

/**
 * @class Cafetiere
 * @brief Parmet de gérer la machine à café PIKAWA
 */
class Cafetiere : public QObject
{
    Q_OBJECT
  private:
    IHMPikawa*     ihm;           //!< association avec la fenêtre graphique
    Communication* communication; //!< relation avec Communication
    Preparation*   preparation;   //!< relation avec Preparation
    BaseDeDonnees* baseDeDonneesPikawa; //!< instance d'un objet BaseDeDonnees
    QStringList    nomCapsules;         //!< liste des noms de capsules
    QStringList    nomLongueurs;        //!< liste des longueurs de préparation
    QStringList    preferences;    //!< liste des préférences de l'utilisateur
    int            capsuleChoisie; //!< id de la capsule sélectionnée
    int  longueurChoisie; //!< la longueur de préparation sélectionnée
    int  niveauEau;       //!< le niveau d'eau dans la cafetière
    bool connectee;       //!< état de connexion de la cafetière
    bool capsulePresente; //!< au moins une capsule est présente dans le magasin
    bool tassePresente;   //!< une tasse est détectée
    bool cafeEnPreparation; //!< un café en préparation

    void initialiserNomCapsules();
    void initiatiserNomLongueurs();
    void chargerPreferences(QString identifiantUtilisateur);
    void gererEvenements();
    void gererEvenementsCommunication();
    void ouvrirBaseDeDonnees();

  public:
    Cafetiere(IHMPikawa* ihm);
    virtual ~Cafetiere();

    QStringList getNomcapsules() const;
    QStringList getNomLongueurs() const;
    int         getCaspuleChoisie() const;
    int         getLongueurChoisie() const;
    int         getNiveauEau() const;
    int         getNiveauEauNecessaire() const;
    bool        estConnectee() const;
    bool        getCapsulePresente() const;
    bool        getTassePresente() const;
    bool        estCafeEnPreparation() const;
    int         getIdCapsule(QString nomCapsule) const;
    QStringList getPreferences() const;
    QString     getCapsulePreferee() const;
    QString     getLongueurPreferee() const;
    QString     getNiveauBac() const;
    QString     getNombreCafeDepuisDetartrage() const;
    void        setCapsuleChoisie(const int& capsuleChoisie);
    void        setLongueurChoisie(const int& boissonChoisie);
    void        setNiveauEau(const int& niveauEau);
    bool        preparerCafetiere();
    QStringList getDisponibiliteCapsules() const;
    bool        estCapsuleChoisieDisponible();
    bool        estCapsuleChoisieDisponible(int capsule);
    void        incrementerNombreCafeJour();
    void        incrementerNombreCafeDepuisDetartrage();
    void        decrementerNombreCafeAvantDetartrage();
    QString     getNombreCafeJour() const;
    QString     getNombreCafeAvantDetartrage() const;
    void        incrementerNiveauBac();
    void        reinitialiserNiveauBac();

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
        COLONNE_PREFERENCES_DESIGNATION_CAPSULE, //!< désignation de la
                                                 //!< capsule
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
    void mettreAJourConnexion(QString nom, QString adresse);
    void recupererEtatCafetiere();
    void recupererEtatMagasin();
    void mettreAJourEtatCafetiere(int  reservoirEau,
                                  bool bacPasPlein,
                                  bool etatCapsule,
                                  bool etatTasse);
    void mettreAJourMagasin(QStringList caspulesDisponibles);
    void gererEtatPreparationCafe(int preparation);
    void lancerLaPreparationCafe();
    void reinitialiserDetartrageBaseDeDonnees();
    void setDeconnectee();

  signals:
    void cafetiereDetectee(QString nom, QString adresse);
    void cafetiereConnectee(QString nom, QString adresse);
    void cafetiereDeconnectee();
    void rechercheTerminee(bool detecte);
    void cafePret();
    void cafeEnCours();
    void erreurPreparation();
    void etatCafetiere(int  reservoirEau,
                       bool bacPasPlein,
                       bool etatCapsule,
                       bool etatTasse);
    void cafetierePrete();
    void cafetierePasPrete();
    void etatMagasinIHM(QStringList caspulesDisponibles);
    void nombreCafesTotal(QString nombreCafeJourIncremente);
    void nombreCafesAvantDetartrage(QString nombreCafeJourDecremente);
    void erreurAccesBaseDeDonnees();
    void nombreDeCafeDepuisDetartrage(QString nombreCafeDepuisDetartrage);
};

#endif // CAFETIERE_H
