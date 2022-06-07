#ifndef IHM_H
#define IHM_H

/**
 * @file ihm.h
 *
 * @brief Déclaration de la classe IHMPikawa
 * @author Anthony BRYCKAERT
 * @version 1.1
 */

#include <QtWidgets>
#include <QIcon>

class Cafetiere;

/**
 * @def NOM
 * @brief Le nom de l'application
 */
#define NOM                                        "Pikawa"
#define NOMBRE_CAFE_AVANT_DETARTRAGE               75
#define NOMBRE_CAFE_DEPUIS_DETARTRAGE_REINITIALISE 0
#define INTENSITE_MAX                              12
#define GRAIN_INTENSITE_MAX                        5
#define RISTRETTO                                  0
#define PAS_RISTRETTO                              7
#define ESPRESSO                                   1
#define PAS_ESPRESSO                               4
#define LUNGO                                      2
#define PAS_LUNGO                                  2
#define TEMPS_ACTUALISATION_BAR_PROGRESSION        500
#define TIME_OUT_PREPARATION                       20000
#define BAC_VIDE                                   0
#define BAC_NIVEAU_1                               1
#define BAC_NIVEAU_2                               2
#define BAC_NIVEAU_3                               3
#define BAC_NIVEAU_4                               4

/**
 * @def VERSION
 * @brief La version de l'application
 */
#define VERSION "1.1"

/**
 * @def PLEIN_ECRAN
 * @brief Pour le mode plein écran
 */
#define PLEIN_ECRAN

namespace Ui
{
class IHMPikawa;
}

class BaseDeDonnees;
class threadAvancementCafe;

/**
 * @class IHMPikawa
 * @brief Déclaration de la classe IHMPikawa
 * @details Cette classe s'occupe de l'affichage sur l'écran de la Raspeberry Pi
 */
class IHMPikawa : public QMainWindow
{
    Q_OBJECT

    /**
     * @enum Page
     * @brief Les différentes pages de l'application
     */
    enum Page
    {
        Accueil,
        SelectionCafe,
        Information,
        Entretien,
        Parametres,
        NbEcrans
    };

    enum BoutonCafe
    {
        boutonColombia = 0,
        boutonIndonesia,
        boutonEthiopia,
        boutonVolluto,
        boutonCapriccio,
        boutonCosi,
        boutonScuro,
        boutonVanilla,
        nbCafe
    };

  private:
    Ui::IHMPikawa* ui; //!< la fenêtre graphique associée à cette classe
    BaseDeDonnees* baseDeDonneesPikawa; //!< instance d'un objet BaseDeDonnees
    Cafetiere*     cafetiere;           //!< instance d'un objet Cafetiere
    QTimer*        timerPreparation;
    QTimer*        timeOutPreparation;
    // GUI
    QIcon*   iconeBoutonConnecte;
    QIcon*   iconeBoutonDetectee;
    QIcon*   iconeBoutonDeconnecte;
    QIcon*   iconeCapsuleColombia;
    QIcon*   iconeCapsuleIndonesia;
    QIcon*   iconeCapsuleEthiopia;
    QIcon*   iconeCapsuleVolluto;
    QIcon*   iconeCapsuleCapriccio;
    QIcon*   iconeCapsuleCosi;
    QIcon*   iconeCapsuleScuro;
    QIcon*   iconeCapsuleVanilla;
    QPixmap* iconeBacPlein;
    QPixmap* iconeBacNiveau4;
    QPixmap* iconeBacNiveau3;
    QPixmap* iconeBacNiveau2;
    QPixmap* iconeBacNiveau1;
    QPixmap* iconeBacPasPlein;
    QPixmap* capsulePresente;
    QPixmap* capsuleAbsente;
    QPixmap* intensite1;
    QPixmap* intensite2;
    QPixmap* intensite3;
    QPixmap* intensite4;
    QPixmap* intensite5;

    QVector<QPushButton*> boutonsCafes;
    QVector<QLabel*>      labelsEtatCafe;
    QVector<QLabel*>      labelsDescriptions;
    QVector<QLabel*>      labelsintensitesCafes;

    void initialiserIcones();
    void initialiserIHM();
    void gererEvenements();
    void gererEvenementsBoutons();
    void gererEvenementsCafetiere();
    void initialiserPreferences();
    int  convertirPourcentageEau(int reservoirEau);
    void chargerBoutonsCafe();
    void chargerLabelsEtatCafe();
    void chargerlabelsDescriptions();
    void ouvrirBaseDeDonnees();
    void afficherAvertissement(int  niveau,
                               bool bacPasPlein,
                               bool tassePresente,
                               bool capsulePresente);
    void afficherMessage(QString message, QString couleur);
    void afficherMessageEtatCafe(QString message, QString couleur);
    void initialiserCafetiere();
    void initialiserPageEntretien();
    void chargerDescription();
    void chargerLabelsIntensiteCafe();
    void chargerIntensite();
    void afficherIntensiteDoux(int i);
    void afficherIntensite1(int i);
    void afficherIntensite2(int i);
    void afficherIntensite3(int i);
    void afficherIntensite4(int i);
    void afficherIntensite5(int i);
    void afficherIntensiteAccueil(int idCapsule);

  public:
    IHMPikawa(QWidget* parent = nullptr);
    ~IHMPikawa();

    void afficherNiveauBac();

  public slots:
    void afficherPage(IHMPikawa::Page page);
    void afficherPageAcceuil();
    void afficherPageInformations();
    void afficherPageEntretien();
    void afficherPageParametres();
    void afficherPageSelectionCafe();
    void activerBoutonConnexionEtatDetecte(QString nom, QString adresse);
    void activerBoutonConnexionEtatConnecte(QString nom, QString adresse);
    void activerBoutonConnexionEtatDeconnecte();
    void rafraichirDecouverte();
    void terminerDecouverte(bool detecte);
    void gererLongueurPreparation(int longueurPreparation);
    void gererSelectionCafes();
    void afficherCapsuleChoisie(int idCapsule);
    void selectionnerColombia();
    void selectionnerIndonesia();
    void selectionnerEthiopia();
    void selectionnerVolluto();
    void selectionnerCosi();
    void selectionnerScuro();
    void selectionnerVanilla();
    void selectionnerCapriccio();
    void afficherCafePret();
    void afficherCafeEnCours();
    void afficherErreurPreparation();
    void mettreAJourEtatCafetiere(int  reservoirEau,
                                  bool bacPasPlein,
                                  bool etatCapsule,
                                  bool etatTasse);
    void mettreAJourMagasinIHM(QStringList caspulesDisponibles);
    void afficherCafetierePrete();
    void afficherCafetierePasPrete();
    void mettreAJourNombreCafeTotal(QString nombreCafeIncremente);
    void reinitialiserDetartrage();
    void mettreAJourNombreCafeAvantDetartrage(QString nombreCafeDecremente);
    void afficherErreurAccesBaseDeDonnees();
    void afficherProgressionPrepration();
    void mettreAJourNombreCafeDepuisDetartrage(
      QString nombreCafeDepuisDernierDetartrage);
    void timeOutAfficherPret();
    void afficherCaspuleAbsente();
  signals:
    void detartrageReinitialise();
};

#endif // IHM_H
