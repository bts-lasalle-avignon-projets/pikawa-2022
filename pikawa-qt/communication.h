#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/**
 * @file communication.h
 *
 * @brief Déclaration de la classe Communication
 * @author
 * @version 1.0
 *
 */

#include <QObject>
#include <QBluetoothDeviceInfo>

/**
 * @def PREFIXE_NOM_CAFETIERE
 * @brief Le nom de l'appareil Bluetooth d'une cafetière doit contenir ce
 * préfixe
 */
#define PREFIXE_NOM_CAFETIERE "PIKAWA"

/**
 * @class Communication
 * @brief
 * @details
 */
class Communication : public QObject
{
    Q_OBJECT
  private:
    bool active;
    bool connecte;

  public:
    Communication(QObject* parent = nullptr);
    ~Communication();

  public slots:
    void activerLaDecouverte();
    void decouvrirCafetiere(const QBluetoothDeviceInfo& appareilBluetooth);
};

#endif // COMMUNICATION_H
