#include "communication.h"
#include <QDebug>

/**
 * @file communication.cpp
 *
 * @brief Définition de la classe Communication
 * @author
 * @version 0.2
 *
 */

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

void Communication::envoyerTrame(QString trame)
{
    qDebug() << Q_FUNC_INFO << trame;
    if(!estConnecte())
    {
        return;
    }
    if(!trame.endsWith("\r\n"))
        trame += "\r\n";
    socketBluetoothPikawa->write(trame.toLatin1());
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
 * @brief Slot de connexion
 *
 * @fn void Communication::connecter()
 */
void Communication::connecter()
{
    if(!estConnecte())
    {
        if(pikawaDetecte)
        {
            qDebug() << Q_FUNC_INFO << "connexion" << pikawa.name() << '['
                     << pikawa.address().toString() << ']';
            socketBluetoothPikawa =
              new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

            if(socketBluetoothPikawa != nullptr)
            {
                connect(socketBluetoothPikawa,
                        SIGNAL(stateChanged(QBluetoothSocket::SocketState)),
                        this,
                        SLOT(lireEtatSocket()));
                connect(socketBluetoothPikawa,
                        SIGNAL(connected()),
                        this,
                        SLOT(socketConnectee()));
                connect(socketBluetoothPikawa,
                        SIGNAL(disconnected()),
                        this,
                        SLOT(socketDeconnectee()));
                connect(socketBluetoothPikawa,
                        SIGNAL(readyRead()),
                        this,
                        SLOT(recevoir()));

                QBluetoothAddress adresse = QBluetoothAddress(pikawa.address());
                QBluetoothUuid    uuid =
                  QBluetoothUuid(QBluetoothUuid::SerialPort);

                socketBluetoothPikawa->connectToService(adresse, uuid);
                socketBluetoothPikawa->open(QIODevice::ReadWrite);
            }
            else
                qDebug() << Q_FUNC_INFO << "erreur création socket";
        }
        else
            qDebug() << Q_FUNC_INFO << "erreur pikawa non détecté";
    }
    qDebug() << Q_FUNC_INFO << estConnecte();
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

void Communication::socketConnectee()
{
    qDebug() << Q_FUNC_INFO << socketBluetoothPikawa->peerName()
             << socketBluetoothPikawa->peerAddress().toString();
    emit cafetiereConnecte(socketBluetoothPikawa->peerName(),
                           socketBluetoothPikawa->peerAddress().toString());
}

void Communication::socketDeconnectee()
{
    qDebug() << Q_FUNC_INFO;
    emit cafetiereDeconnecte();
}

void Communication::recevoir()
{
    QByteArray donnees;
    donnees = socketBluetoothPikawa->readAll();
    qDebug() << Q_FUNC_INFO << "donnees" << donnees;
    trameRecue += QString(donnees.data());
    qDebug() << Q_FUNC_INFO << "trameRecue" << trameRecue;

    /**
     * @todo Définir un protocole et le traiter ici
     */
}

void Communication::lireEtatSocket()
{
    qDebug() << Q_FUNC_INFO << socketBluetoothPikawa->state();
}
