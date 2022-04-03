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
    QObject(parent), agentDecouvreur(nullptr), pikawaDetecte(false),
    socketBluetoothPikawa(nullptr)
{
    qDebug() << Q_FUNC_INFO << "Bluetooth" << interfaceLocale.isValid();
    activerBluetooth();
}

Communication::~Communication()
{
    deconnecter();
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
        qDebug() << Q_FUNC_INFO << interfaceLocale.name();
        interfaceLocale.powerOn();

        activerLaDecouverte();
    }
    else
        qDebug() << Q_FUNC_INFO << "Pas de bluetooh !";
}

/**
 * @brief
 *
 * @fn bool Communication::estConnecte()
 */
bool Communication::estConnecte() const
{
    if(!estBluetoothDisponible())
        return false;
    if(socketBluetoothPikawa == nullptr)
        return false;
    qDebug() << Q_FUNC_INFO << socketBluetoothPikawa->isOpen();
    return socketBluetoothPikawa->isOpen();
}

void Communication::activerLaDecouverte()
{
    if(estBluetoothDisponible())
    {
        qDebug() << Q_FUNC_INFO;
        agentDecouvreur = new QBluetoothDeviceDiscoveryAgent(this);
        if(agentDecouvreur != nullptr)
        {
            connect(agentDecouvreur,
                    SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
                    this,
                    SLOT(decouvrirCafetiere(QBluetoothDeviceInfo)));

            pikawaDetecte = false;
            agentDecouvreur->start();
        }
    }
}

void Communication::decouvrirCafetiere(
  const QBluetoothDeviceInfo& appareilBluetooth)
{
    qDebug() << Q_FUNC_INFO << "appareil Bluetooth" << appareilBluetooth.name()
             << '[' << appareilBluetooth.address().toString() << ']';

    if(appareilBluetooth.name().contains(PREFIXE_NOM_CAFETIERE))
    {
        qDebug() << Q_FUNC_INFO << "machine à café pikawa détectée"
                 << appareilBluetooth.name() << '['
                 << appareilBluetooth.address().toString() << ']';
        agentDecouvreur->stop();
        pikawa        = appareilBluetooth;
        pikawaDetecte = true;
        emit cafetiereDetectee(appareilBluetooth.name(),
                               appareilBluetooth.address().toString());
    }
}

/**
 * @brief Slot de déconnexion
 *
 * @fn void Communication::deconnecter()
 */
void Communication::deconnecter()
{
    if(!estBluetoothDisponible())
        return;
    if(socketBluetoothPikawa == nullptr)
        return;
    if(socketBluetoothPikawa->isOpen())
    {
        qDebug() << Q_FUNC_INFO;
        socketBluetoothPikawa->close();
    }
}
