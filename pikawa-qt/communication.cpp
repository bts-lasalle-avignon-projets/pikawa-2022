#include "communication.h"

#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QString>
#include <QDebug>

Communication::Communication(QObject* parent) :
    QObject(parent), active(false), connecte(false)
{
    qDebug() << Q_FUNC_INFO;
}

Communication::~Communication()
{
    qDebug() << Q_FUNC_INFO;
}

void Communication::activerLaDecouverte()
{
    QBluetoothDeviceDiscoveryAgent* agentDecouvreur =
      new QBluetoothDeviceDiscoveryAgent(this);
    connect(agentDecouvreur,
            SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this,
            SLOT(decouvrirCafetiere(QBluetoothDeviceInfo)));

    agentDecouvreur->start();
}

void Communication::decouvrirCafetiere(
  const QBluetoothDeviceInfo& appareilBluetooth)
{
    qDebug() << Q_FUNC_INFO << "appareil Bluettoth" << appareilBluetooth.name()
             << '[' << appareilBluetooth.address().toString() << ']';
    /**
     * @todo Vérifier que le nom de l'appareil Bluetooth contient l'identifiant
     * PIKAWA, si c'est le cas conserver cet appareil
     */
}
