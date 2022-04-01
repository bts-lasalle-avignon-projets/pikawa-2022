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
#include <QBluetoothLocalDevice>

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
    QBluetoothLocalDevice interfaceLocale;
    bool                  active;
    bool                  connecte;

    bool estBluetoothDisponible();
    void activerBluetooth();

  public:
    Communication(QObject* parent = nullptr);
    ~Communication();

  public slots:
    void activerLaDecouverte();
    void decouvrirCafetiere(const QBluetoothDeviceInfo& appareilBluetooth);
};

#endif // COMMUNICATION_H
