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
//#define PLEIN_ECRAN

QT_BEGIN_NAMESPACE
namespace Ui
{
class IHMPikawa;
}
QT_END_NAMESPACE

/**
 * @class IHMPikawa
 * @brief Déclaration de la classe IHMPikawa
 * @details Cette classe s'occupe de l'affichage sur l'écran de la Raspeberry Pi
 */
class IHMPikawa : public QMainWindow
{
    Q_OBJECT

  public:
    IHMPikawa(QWidget* parent = nullptr);
    ~IHMPikawa();

  private:
    Ui::IHMPikawa* ui; //!< la fenêtre graphique associée à cette classe
};

#endif // IHM_H
