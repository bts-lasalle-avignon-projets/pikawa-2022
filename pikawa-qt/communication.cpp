#include "communication.h"

#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QString>
#include <QDebug>

Communication::Communication() : active(false), connecte(false)
{
    QBluetoothLocalDevice appareilLocal;
    QString               nomAppareilLocal;
    chercherCafetiere();
}

void Communication::chercherCafetiere()
{
    QBluetoothDeviceDiscoveryAgent* agentDecouvreur =
      new QBluetoothDeviceDiscoveryAgent(this);
    connect(agentDecouvreur,
            SIGNAL(estCafetiereDecourverte(QBluetoothDeviceInfo)),
            this,
            SLOT(estCafetiereDecourverte(QBluetoothDeviceInfo)));

    agentDecouvreur->start();
}

bool Communication::estCafetiereDecourverte(const QBluetoothDeviceInfo& device)
{
    qDebug() << "Decouverte d'un nouvel appareil:" << device.name() << '('
             << device.address().toString() << ')';
}
