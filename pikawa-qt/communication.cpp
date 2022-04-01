#include "communication.h"

/**
 * @file communication.cpp
 *
 * @brief Définition de la classe Communication
 * @author
 * @version 1.0
 *
 */

#include <QBluetoothDeviceDiscoveryAgent>
#include <QString>
#include <QDebug>

Communication::Communication(QObject* parent) :
    QObject(parent), active(false), connecte(false)
{
    qDebug() << Q_FUNC_INFO << "Bluetooth" << interfaceLocale.isValid();
}

Communication::~Communication()
{
    qDebug() << Q_FUNC_INFO;
}

bool Communication::estBluetoothDisponible()
{
    return interfaceLocale.isValid();
}

void Communication::activerBluetooth()
{
    if(estBluetoothDisponible())
    {
        interfaceLocale.powerOn();
        this->active = true;
    }
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
    qDebug() << Q_FUNC_INFO << "appareil Bluetooth" << appareilBluetooth.name()
             << '[' << appareilBluetooth.address().toString() << ']';
    /**
     * @todo Vérifier que le nom de l'appareil Bluetooth contient l'identifiant
     * PIKAWA, si c'est le cas conserver cet appareil
     */
}
