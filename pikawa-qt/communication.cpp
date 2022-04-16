#include "communication.h"
#include "cafetiere.h"
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
    QObject(parent),cafetiere(nullptr),agentDecouvreur(nullptr), connecte(false),
    pikawaDetecte(false), socketBluetoothPikawa(nullptr)
{
    qDebug() << Q_FUNC_INFO << "Bluetooth" << interfaceLocale.isValid();
    activerBluetooth();
    activerLaDecouverte();

#ifdef TEST_TRAMES
    recevoir();
#endif
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

bool Communication::estTrameValide(QString trame)
{
    qDebug() << Q_FUNC_INFO << trame;
    /**
     * @todo
     * 1. doit commencer par $PIKAWA
     * 2. doit se terminer \r\n
     */

    return false;
}

QString Communication::extraireTypeTrame(QString trame)
{
    /**
     * @todo extraire et retourner le champ type (avec split)
     */
    qDebug() << Q_FUNC_INFO << trame.split(";", QString::SkipEmptyParts);
    return QString("");
}

bool Communication::traiterTrame(QString typeTrame, QString trame)
{
    qDebug() << Q_FUNC_INFO << typeTrame;
    /**
     * @todo extraire les champs en fonction du type de trame (avec split)
     * @todo signaler les données avec emit
     */
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
    qDebug() << Q_FUNC_INFO << "isOpen" << socketBluetoothPikawa->isOpen()
             << "connecte" << connecte;
    if(!socketBluetoothPikawa->isOpen())
        return false;
    return connecte;
}

bool Communication::estCafetiereDetectee() const
{
    return pikawaDetecte;
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
            connect(agentDecouvreur,
                    SIGNAL(finished()),
                    this,
                    SLOT(terminerRecherche()));
            pikawaDetecte = false;
            agentDecouvreur->start();
        }
    }
}

void Communication::desactiverLaDecouverte()
{
    qDebug() << Q_FUNC_INFO;
    if(agentDecouvreur != nullptr)
    {
        agentDecouvreur->start();
    }
}

void Communication::decouvrirCafetiere(
  const QBluetoothDeviceInfo& appareilBluetooth)
{
    qDebug() << Q_FUNC_INFO << "appareil Bluetooth" << appareilBluetooth.name()
             << '[' << appareilBluetooth.address().toString() << ']' << "rssi"
             << appareilBluetooth.rssi();

    if(appareilBluetooth.name().contains(PREFIXE_NOM_CAFETIERE) /*&&
       appareilBluetooth.rssi() != 0*/)
    {
        /**
         * @see systemctl restart bluetooth
         */
        qDebug() << Q_FUNC_INFO << "machine à café pikawa détectée"
                 << appareilBluetooth.name() << '['
                 << appareilBluetooth.address().toString() << ']';
        agentDecouvreur->stop();
        pikawa        = appareilBluetooth;
        pikawaDetecte = true;
        emit rechercheTerminee(pikawaDetecte);
        emit cafetiereDetectee(appareilBluetooth.name(),
                               appareilBluetooth.address().toString());
    }
}

void Communication::terminerRecherche()
{
    qDebug() << Q_FUNC_INFO << "pikawaDetecte" << pikawaDetecte;
    emit rechercheTerminee(pikawaDetecte);
}

/**
 * @brief Slot de connexion
 *
 * @fn void Communication::connecter()
 */
void Communication::connecter()
{
    qDebug() << Q_FUNC_INFO;

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
    connecte = true;
    emit cafetiereConnectee(socketBluetoothPikawa->peerName(),
                            socketBluetoothPikawa->peerAddress().toString());
}

void Communication::socketDeconnectee()
{
    qDebug() << Q_FUNC_INFO;
    connecte = false;
    emit cafetiereDeconnectee();
}

void Communication::recevoir()
{
#ifndef TEST_TRAMES
    QByteArray donnees;
    donnees = socketBluetoothPikawa->readAll();
    qDebug() << Q_FUNC_INFO << "donnees" << donnees;
    trameRecue += QString(donnees.data());
#else
    // on peut simuler des trames reçues
    trameRecue = "$PIKAWA;C;50;60;1;1;\r\n";
#endif
    qDebug() << Q_FUNC_INFO << "trameRecue" << trameRecue;
    /**
     * @todo 1. vérifier la validité de la trame
     * @todo 2. si trame valide, identifier le type de trame
     * @todo 3. si type de trame connue, traiter le type de trame (extraire les données) et signaler les données extraites avec emit
     */

}

void Communication::lireEtatSocket()
{
    qDebug() << Q_FUNC_INFO << socketBluetoothPikawa->state();
}
