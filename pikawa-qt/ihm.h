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

    enum Page
    {
        Accueil     = 0,
        selectionCafe = 1,
        Information = 2,
        Entretien   = 3,
        Parametre   = 4,
        NbEcrans
    };

  private:
    Ui::IHMPikawa* ui; //!< la fenêtre graphique associée à cette classe
    BaseDeDonnees* baseDeDonnees; //!< instance d'un objet BaseDeDonnees
    Cafetiere*     cafetiere;     //!< instance d'un objet Cafetiere

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
    void activerBoutonConnecter(QString nom, QString adresse);
};

#endif // IHM_H
