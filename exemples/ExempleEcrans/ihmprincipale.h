#ifndef IHMPRINCIPALE_H
#define IHMPRINCIPALE_H

/**
 * @file ihmprincipale.h
 *
 * @brief Déclaration de la classe IHMPrincipale
 * @author Thierry Vaira <tvaira@free.fr>
 * @version 1.0
 *
 */

#include <QtWidgets>
#include "ImageBouton.h"

/**
 * @def TEST_IHMPRINCIPALE
 * @brief Pour le mode test (raccourcis clavier)
 */
#define TEST_IHMPRINCIPALE

/**
 * @def PLEIN_ECRAN
 * @brief Pour le mode kiosque
 */
#define PLEIN_ECRAN

QT_BEGIN_NAMESPACE
namespace Ui
{
class IHMPrincipale;
}
QT_END_NAMESPACE

/**
 * @class IHMPrincipale
 * @brief Déclaration de la classe IHMPrincipale
 * @details Cette classe s'occupe de l'affichage sur l'écran
 */
class IHMPrincipale : public QMainWindow
{
    Q_OBJECT

  public:
    IHMPrincipale(QWidget* parent = nullptr);
    ~IHMPrincipale();

  private:
    Ui::IHMPrincipale* ui;  //!< la fenêtre graphique associée à cette classe
    int nbChangementsEcran; //!< pour compter le nombre de changements d'écrans
    ImageBouton* retourEcran2;

    /**
     * @enum Ecran
     * @brief Définit les différents écrans de l'IHM
     *
     */
    enum Ecran
    {
        Accueil = 0,
        Ecran1,
        Ecran2,
        NbEcrans
    };

#ifdef TEST_IHMPRINCIPALE
    void fixerRaccourcisClavier();
#endif

  public slots:
    void afficherEcranAccueil();
    void afficherEcran(IHMPrincipale::Ecran ecran);
    void afficherEcranPrecedent();
    void afficherEcranSuivant();
    void fermerApplication();
};

#endif // IHMPRINCIPALE_H
