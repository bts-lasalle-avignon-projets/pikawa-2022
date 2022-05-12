#ifndef IHM_H
#define IHM_H

/**
 * @file ihm.h
 *
 * @brief Déclaration de la classe IHMPikawa
 * @author Anthony BRYCKAERT
 * @version 0.2
 */

#include <QtWidgets>
#include <QIcon>

class Cafetiere;

/**
 * @def NOM
 * @brief Le nom de l'application
 */
#define NOM                          "Pikawa"
#define NOMBRE_CAFE_AVANT_DETARTRAGE 75
#define INTENSITE_MAX                12
#define GRAIN_INTENSITE_MAX          5
/**
 * @def VERSION
 * @brief La version de l'application
 */
#define VERSION "0.2"

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

/**
 * @class IHMPikawa
 * @brief Déclaration de la classe IHMPikawa
 * @details Cette classe s'occupe de l'affichage sur l'écran de la Raspeberry Pi
 */
class IHMPikawa : public QMainWindow
{
    Q_OBJECT

    /**
     * @todo Revoir COMPLETEMENT la mise en page de l'IHM
     */
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
    void initialiserCafetiere();
    void initialiserPageEntretien();
    void mettreAJourNombreCafeDepuisDetartrage();
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

  signals:
    void detartrageReinitialise();
};

#endif // IHM_H
