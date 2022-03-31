#include "communication.h"

#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QString>
#include <QDebug>

Communication::Communication() : active(false), connecte(false)
{
    QBluetoothLocalDevice localDevice;
    QString               localDeviceName;
    chercherCafetiere();
}

void Communication::chercherCafetiere()
{
    QBluetoothDeviceDiscoveryAgent* discoveryAgent =
      new QBluetoothDeviceDiscoveryAgent(this);
    connect(discoveryAgent,
            SIGNAL(estCafetiereDecourverte(QBluetoothDeviceInfo)),
            this,
            SLOT(estCafetiereDecourverte(QBluetoothDeviceInfo)));

    discoveryAgent->start();
}

bool Communication::estCafetiereDecourverte(const QBluetoothDeviceInfo& device)
{
    qDebug() << "Found new device:" << device.name() << '('
             << device.address().toString() << ')';
}
