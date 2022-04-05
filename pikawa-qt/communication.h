#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/**
 * @file communication.h
 *
 * @brief Déclaration de la classe Communication
 * @author
 * @version 0.2
 *
 */

#include <QObject>
#include <QtBluetooth>

/**
 * @def PREFIXE_NOM_CAFETIERE
 * @brief Le nom de l'appareil Bluetooth d'une cafetière doit contenir ce
 * préfixe
 */
#define PREFIXE_NOM_CAFETIERE "PIKAWA"

/**
 * @class Communication
 * @brief
 * @details
 */
class Communication : public QObject
{
    Q_OBJECT
  private:
    QBluetoothLocalDevice interfaceLocale; //!< l'interface Bluetooth locale
    QBluetoothDeviceDiscoveryAgent*
      agentDecouvreur; //!< pour découvrir des interfaces Bluetooth
    QBluetoothDeviceInfo
         pikawa;        //!< l'interface Bluetooth de la cafetière pikawa
    bool pikawaDetecte; //!< état de détection de l'interface pikawa
    QBluetoothSocket*
            socketBluetoothPikawa; //!< socket cliente de communication Bluetooth
    QString trameRecue;            //!< la trame reçue

    bool estBluetoothDisponible() const;
    void activerBluetooth();

  public:
    Communication(QObject* parent = nullptr);
    ~Communication();

    bool estConnecte() const;
    void envoyerTrame(QString trame);

  public slots:
    void activerLaDecouverte();
    void decouvrirCafetiere(const QBluetoothDeviceInfo& appareilBluetooth);
    void connecter();
    void deconnecter();
    void socketConnectee();
    void socketDeconnectee();
    void recevoir();
    void lireEtatSocket();

  signals:
    void cafetiereDetectee(QString nom, QString adresse);
    void cafetiereConnecte(QString nom, QString adresse);
    void cafetiereDeconnecte();
};

#endif // COMMUNICATION_H
