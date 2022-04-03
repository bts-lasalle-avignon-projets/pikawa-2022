#include "communication.h"
#include <unistd.h>

/**
 * @file communication.cpp
 *
 * @brief Définition de la classe Communication
 * @author
 * @version 1.0
 *
 */

#include <QBluetoothDeviceDiscoveryAgent>
 #include <QBluetoothSocket>
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

bool Communication::estBluetoothDisponible() const
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

void Communication::socketConnectee()
{
    qDebug() << Q_FUNC_INFO;
    QString message = QString::fromUtf8("Périphérique connecté ") + socketBluetoothPikawa->peerName() + " [" + socketBluetoothPikawa->peerAddress().toString() + "]";
    qDebug() << message;
}

void Communication::socketDeconnectee()
{
    qDebug() << Q_FUNC_INFO;
    QString message = QString::fromUtf8("Périphérique déconnecté ");
    qDebug() << message;
}

void Communication::socketPretALire()
{
    qDebug() << Q_FUNC_INFO;
    QByteArray donnees;

    while (socketBluetoothPikawa->bytesAvailable())
    {
        donnees += socketBluetoothPikawa->readAll();
        usleep(150000); // cf. timeout
    }

    qDebug() << QString::fromUtf8("Données reçues : ") << QString(donnees);
}


void Communication::connecter()
{
    if(!estConnecte())
    {
        socketBluetoothPikawa = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

        connect(socketBluetoothPikawa, SIGNAL(connected()), this, SLOT(socketConnectee()));
        connect(socketBluetoothPikawa, SIGNAL(disconnected()), this, SLOT(socketDeconnectee()));
        connect(socketBluetoothPikawa, SIGNAL(readyRead()), this, SLOT(socketPretALire()));

        QBluetoothAddress adresse = QBluetoothAddress(pikawa.address());
        QBluetoothUuid uuid = QBluetoothUuid(QBluetoothUuid::SerialPort);

        socketBluetoothPikawa->connectToService(adresse, uuid);
        socketBluetoothPikawa->open(QIODevice::ReadWrite);

    }
}


void Communication::envoyerTrame(QString trame)
{
    qDebug() << Q_FUNC_INFO;
    if (socketBluetoothPikawa == NULL || !socketBluetoothPikawa->isOpen())
    {
        return;
    }
    trame += "\r\n";
    socketBluetoothPikawa->write(trame.toLatin1());
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
