#include "communication.h"

#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QString>
#include <QDebug>

Communication::Communication() : active(false), connecte(false)
{
    QBluetoothLocalDevice appareilLocal;
    QString               nomAppareilLocal;
}

Communication::~Communication()
{
}

void Communication::activerLaDecouverte()
{
    QBluetoothDeviceDiscoveryAgent* agentDecouvreur =
      new QBluetoothDeviceDiscoveryAgent(this);
    connect(agentDecouvreur,
            SIGNAL(estESPDecourverts(QBluetoothDeviceInfo)),
            this,
            SLOT(estESPDecourverts(QBluetoothDeviceInfo)));

    agentDecouvreur->start();
}

void Communication::estESPDecourverts(const QBluetoothDeviceInfo& esp)
{
    qDebug() << "Decouverte d'un nouvel appareil: " << esp.name() << '('
             << esp.address().toString() << ')';
}
