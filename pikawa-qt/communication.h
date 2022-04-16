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
#define DELIMITEUR ';'
#define ETAT_CAFETIERE 'C'
#define ETAT_MAGASIN 'M'
#define ETAT_PREPARATION 'P'

#define TEST_TRAMES

class Cafetiere;

/**
 * @class Communication
 * @brief
 * @details
 */

class Communication : public QObject
{
    Q_OBJECT
  private:

    Cafetiere*     cafetiere;     //!< instance d'un objet Cafetiere
    QBluetoothLocalDevice interfaceLocale; //!< l'interface Bluetooth locale
    QBluetoothDeviceDiscoveryAgent*
      agentDecouvreur; //!< pour découvrir des interfaces Bluetooth
    QBluetoothDeviceInfo
         pikawa;        //!< l'int erface Bluetooth de la cafetière pikawa
    bool connecte;      //!< l'état de connexion de la socket Bluetooth
    bool pikawaDetecte; //!< état de détection de l'interface pikawa
    QBluetoothSocket*
            socketBluetoothPikawa; //!< socket cliente de communication Bluetooth
    QString trameRecue;            //!< la trame reçue

    bool estBluetoothDisponible() const;
    void activerBluetooth();
    bool estTrameValide(QString trame);
    bool estTypeTrameValide(QString typeTrame);
    QString extraireTypeTrame(QString trame);
    bool traiterTrame(QString typeTrame, QString trame);


  public:
    Communication(QObject* parent = nullptr);
    ~Communication();

    bool estConnecte() const;
    bool estCafetiereDetectee() const;
    void envoyerTrame(QString trame);

  public slots:
    void activerLaDecouverte();
    void desactiverLaDecouverte();
    void decouvrirCafetiere(const QBluetoothDeviceInfo& appareilBluetooth);
    void terminerRecherche();
    void connecter();
    void deconnecter();
    void socketConnectee();
    void socketDeconnectee();
    void recevoir();
    void lireEtatSocket();

  signals:
    void cafetiereDetectee(QString nom, QString adresse);
    void cafetiereConnectee(QString nom, QString adresse);
    void cafetiereDeconnectee();
    void rechercheTerminee(bool detecte);
    void etatCafetiere(int reservoirEau, int bacCapsules, bool etatCapsule, bool etatTasse);
    void etatMagasin(bool colombiaPresent, bool indonesiaPresent, bool ethiopiaPresent,
                     bool volutoPresent, bool capriccioPresent, bool cosiPresent, bool scuroPresent, bool vanillaPresent);

    void cafeEnPreparation(bool preparationCafe);



};

#endif // COMMUNICATION_H
