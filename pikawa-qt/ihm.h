#ifndef IHM_H
#define IHM_H

/**
 * @file ihm.h
 *
 * @brief Déclaration de la classe IHMPikawa
 * @author
 * @version 0.2
 *
 */

#include <QtWidgets>
#include <QIcon>

class Cafetiere;

/**
 * @def NOM
 * @brief Le nom de l'application
 */
#define NOM "Pikawa"

/**
 * @def VERSION
 * @brief La version de l'application
 */
#define VERSION "0.1"

/**
 * @def PLEIN_ECRAN
 * @brief Pour le mode plein écran
 */
#define PLEIN_ECRAN
#define TAILLE_RISTRETO  30
#define TAILLE_ESPRESSO  60
#define TAILLE_LUNGO     110
#define TAILLE_RESERVOIR 800

QT_BEGIN_NAMESPACE
namespace Ui
{
class IHMPikawa;
}
QT_END_NAMESPACE

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
    BaseDeDonnees* baseDeDonnees; //!< instance d'un objet BaseDeDonnees
    Cafetiere*     cafetiere;     //!< instance d'un objet Cafetiere

    QIcon* iconeBoutonConnecte;
    QIcon* iconeBoutonDetectee;
    QIcon* iconeBoutonDeconnecte;

    QIcon* iconeCapsuleColombia;
    QIcon* iconeCapsuleIndonesia;
    QIcon* iconeCapsuleEthiopia;
    QIcon* iconeCapsuleVolluto;
    QIcon* iconeCapsuleCapriccio;
    QIcon* iconeCapsuleCosi;
    QIcon* iconeCapsuleScuro;
    QIcon* iconeCapsuleVanilla;

    QPixmap* iconeBacPlein;
    QPixmap* iconeBacVide;

    QVector<QPushButton*> boutonsCafes;

    void initialiserIcones();
    void initialiserIHM();
    void gererEvenements();
    void initialiserPreferences();

  public:
    IHMPikawa(QWidget* parent = nullptr);
    ~IHMPikawa();

    int convertirPourcentageEau(int reservoirEau);

    void chargerBoutonCafe();

    void ouvrirBaseDeDonnees();
    void afficherAvertissement(int  niveau,
                               bool bacPlein,
                               bool tassePresente,
                               bool capsulePresente);

  public slots:
    void afficherPage(IHMPikawa::Page page);
    void afficherPageAcceuil();
    void afficherPageInformations();
    void afficherPageEntretien();
    void afficherPageParametres();
    void afficherPageSelectionCafe();
    void activerboutonConnexionEtatDetecte(QString nom, QString adresse);
    void activerboutonConnexionEtatConnecte(QString nom, QString adresse);
    void activerboutonConnexionEtatDeconnecte();
    void rafraichirDecouverte();
    void terminerDecouverte(bool detecte);

    void gererLongueurPreparation(int longueurPreparation);
    void gererSelectionCafes();

    void selectionnerColombia();
    void selectionnerIndonesia();
    void selectionnerEthiopia();
    void selectionnerVolluto();
    void selectionnerCosi();
    void selectionnerScuro();
    void selectionnerVanilla();
    void selectionnerCapriccio();
    void afficherCafePret();
    void mettreAJourEtatCafetiere(int  reservoirEau,
                                  bool bacCapsules,
                                  bool etatCapsule,
                                  bool etatTasse);
    void mettreAJourMagasinIHM(QStringList caspulesDisponibles);
    void afficherCafetierePrete();
    void afficherCafetierePasPrete();
};

#endif // IHM_H
