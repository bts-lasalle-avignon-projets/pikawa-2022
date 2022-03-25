#ifndef IHM_H
#define IHM_H

/**
 * @file ihm.h
 *
 * @brief Déclaration de la classe IHMPikawa
 * @author
 * @version 1.0
 *
 */

#include <QtWidgets>

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

    enum Ecran
    {
        Accueil     = 0,
        Information = 1,
        Entretien   = 2,
        Parametre   = 3,
        NbEcrans
    };

  public:
    IHMPikawa(QWidget* parent = nullptr);
    ~IHMPikawa();

  private:
    Ui::IHMPikawa* ui; //!< la fenêtre graphique associée à cette classe

    void initialiserIHM();
    void gererEvenements();

  public slots:
    void afficherLongueurPreparation(int longueurPreparation);
    void afficherEcran(IHMPikawa::Ecran ecran);
    void afficherEcranSuivant();
};

#endif // IHM_H
