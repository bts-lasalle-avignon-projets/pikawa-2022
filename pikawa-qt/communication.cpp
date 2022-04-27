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
    QObject(parent), cafetiere(nullptr), agentDecouvreur(nullptr),
    connecte(false), pikawaDetecte(false), socketBluetoothPikawa(nullptr)
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
    qDebug() << Q_FUNC_INFO << trame
             << (trame.startsWith("$PIKAWA") && trame.endsWith("\r\n"));
    return trame.startsWith("$PIKAWA") && trame.endsWith("\r\n");
}

TypeTrame Communication::extraireTypeTrame(QString trame)
{
    QStringList champs = trame.split(QLatin1Char(';'), QString::SkipEmptyParts);
    QString     type   = champs[CHAMP_TYPE_TRAME];
    qDebug() << Q_FUNC_INFO << type;

    if(type == ETAT_CAFETIERE)
        return TypeTrame::EtatCafetiere;
    else if(type == ETAT_MAGASIN)
        return TypeTrame::EtatMagasin;
    else if(type == ETAT_PREPARATION)
        return TypeTrame::EtatPreparation;
    else
        return TypeTrame::Inconnue;

    return TypeTrame::Inconnue;
}

bool Communication::traiterTrame(TypeTrame typeTrame, QString trame)
{
    if(typeTrame == TypeTrame::Inconnue)
        return false;
    QStringList champs = trame.split(QLatin1Char(';'), QString::SkipEmptyParts);
    qDebug() << Q_FUNC_INFO << typeTrame << champs;
    int     niveauEau;
    bool    caspulePresente, tassePresente, bacPlein;
    QString colombiaPresent, indonesiaPresent, ethiopiaPresent, vollutoPresent,
      capriccioPresent, cosiPresent, scuroPresent, vanillaPresent;
    int preparationCafe;

    QStringList caspulesDisponibles;

    switch(typeTrame)
    {
        case TypeTrame::EtatCafetiere:
            niveauEau = champs[ChampEtatCafetiere::NiveauEau].toInt();
            bacPlein = (champs[ChampEtatCafetiere::NiveauBac] == '1');
            caspulePresente =
              (champs[ChampEtatCafetiere::CaspulePresente] == '1');
            tassePresente = (champs[ChampEtatCafetiere::TassePresente] == '1');
            emit etatCafetiere(niveauEau,
                               bacPlein,
                               caspulePresente,
                               tassePresente);
            return true;
            // break;
        case TypeTrame::EtatMagasin:
            for(int i = ChampEtatMagasin::Colombia;
                i < ChampEtatMagasin::NbChampsEtatMagasin;
                ++i)
            {
                caspulesDisponibles << champs.at(i);
            }
            qDebug() << Q_FUNC_INFO << " capulesDisponibles "
                     << caspulesDisponibles;

            emit etatMagasin(caspulesDisponibles);

            return true;
            // break;
        case TypeTrame::EtatPreparation:
            preparationCafe = champs[ChampEtatPreparation::Cafe].toInt();
            emit cafeEnPreparation(preparationCafe);
            return true;
            // break;
    }
    return false;
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
    // trameRecue = "$PIKAWA;C;50;60;1;1;\r\n";
    trameRecue = "$PIKAWA;M;0;1;1;0;1;0;1;0;\r\n";
    // trameRecue = "$PIKAWA;P;1;\r\n";
    // trameRecue = "$PIKAWA;W;50;60;1;1;\r\n"; // trame invalide
#endif
    qDebug() << Q_FUNC_INFO << "trameRecue" << trameRecue;
    if(estTrameValide(trameRecue))
    {
        TypeTrame typeTrame = extraireTypeTrame(trameRecue);
        if(traiterTrame(typeTrame, trameRecue))
        {
            trameRecue.clear();
        }
        else
        {
            qDebug() << Q_FUNC_INFO << "erreur traitement";
        }
    }
}

void Communication::lireEtatSocket()
{
    qDebug() << Q_FUNC_INFO << socketBluetoothPikawa->state();
}

void Communication::envoyerTramePreparation(int nomCafe, int longueur)
{
    envoyerTrame("$PIKAWA;P; " + QString::number(nomCafe) + " ; " + QString::number(longueur) + ";\r\n");
    qDebug() << Q_FUNC_INFO;
}

