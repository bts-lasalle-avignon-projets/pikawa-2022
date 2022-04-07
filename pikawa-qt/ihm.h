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
 * @def NOM_BDD
 * @brief Le nom de la base de données SQLite
 */
#define NOM_BDD "pikawa.sqlite"

/**
 * @def PLEIN_ECRAN
 * @brief Pour le mode plein écran
 */
#define PLEIN_ECRAN

QT_BEGIN_NAMESPACE
namespace Ui
{
class IHMPikawa;
}
QT_END_NAMESPACE

class BaseDeDonnees;

/**
 * @enum LongueurPreparation
 * @brief Long, Moyen ou Court
 */
enum LongueurCafe
{
    Court = 0,
    Moyen = 1,
    Long  = 2
};

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

  private:
    Ui::IHMPikawa* ui; //!< la fenêtre graphique associée à cette classe
    BaseDeDonnees* baseDeDonnees; //!< instance d'un objet BaseDeDonnees
    Cafetiere*     cafetiere;     //!< instance d'un objet Cafetiere

    QIcon* iconeBoutonConnecte;
    QIcon* iconeBoutonDetectee;
    QIcon* iconeBoutonDeconnecte;

    void initialiserIHM();
    void gererEvenements();

  public:
    IHMPikawa(QWidget* parent = nullptr);
    ~IHMPikawa();

  public slots:
    void afficherLongueurPreparation(int longueurPreparation);
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
};

#endif // IHM_H
