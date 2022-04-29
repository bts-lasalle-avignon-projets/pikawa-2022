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
#define DELIMITEUR            ';'
#define ETAT_CAFETIERE        "C"
#define ETAT_MAGASIN          "M"
#define ETAT_PREPARATION      "P"
#define TRAME_ERREUR          "ERREUR"
#define CHAMP_TYPE_TRAME      1

// Code erreur
#define ERREUR_PROTOCOLE      1
#define ERREUR_NB_PARAMETRES  2
#define ERREUR_TRAME_INCONNUE 3
#define ERREUR_TYPE_CAFE      4
#define ERREUR_LONGUEUR_CAFE  5

/**
 * @def TEST_TRAMES
 * @brief Pour les tests de trames
 */
//#define TEST_TRAMES

/**
 * @enum TypeTrame
 * @brief Les différents types de trame
 */
enum TypeTrame
{
    Inconnue = -1,
    EtatCafetiere,
    EtatMagasin,
    EtatPreparation,
    ErreurPreparation,
    NbTrames
};

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
         pikawa;        //!< l'int erface Bluetooth de la cafetière pikawa
    bool connecte;      //!< l'état de connexion de la socket Bluetooth
    bool pikawaDetecte; //!< état de détection de l'interface pikawa
    QBluetoothSocket*
            socketBluetoothPikawa; //!< socket cliente de communication Bluetooth
    QString trameRecue;            //!< la trame reçue

    bool      estBluetoothDisponible() const;
    void      activerBluetooth();
    bool      estTrameValide(QString trame);
    TypeTrame extraireTypeTrame(QString trame);
    bool      traiterTrame(TypeTrame typeTrame, QString trame);

  public:
    Communication(QObject* parent = nullptr);
    ~Communication();

    bool estConnecte() const;
    bool estCafetiereDetectee() const;
    void envoyerTrame(QString trame);
    void envoyerTramePreparation(int nomCafe, int longueur);

    /**
     * @enum ChampEtatCafetiere
     * @brief Les différents champs de la trame EtatCafetiere
     */
    enum ChampEtatCafetiere
    {
        NiveauEau = 2,
        NiveauBac,
        CaspulePresente,
        TassePresente,
        NbChampsEtatCafetiere
    };
    /**
     * @enum ChampEtatMagasin
     * @brief Les différents champs de la trame EtatMagasin
     */
    enum ChampEtatMagasin
    {
        Colombia = 2,
        Indonesia,
        Ethiopia,
        Volluto,
        Capriccio,
        Cosi,
        Scuro,
        Vanilla,
        NbChampsEtatMagasin
    };
    /**
     * @enum ChampEtatPreparation
     * @brief Les différents champs de la trame EtatPreparation
     */
    enum ChampEtatPreparation
    {
        Cafe = 2,
        NbChampsEtatPreparation
    };

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
    void etatCafetiere(int  reservoirEau,
                       bool bacPlein,
                       bool etatCapsule,
                       bool etatTasse);
    void etatMagasin(QStringList caspulesDisponibles);
    void cafeEnPreparation(int preparationCafe);
    void erreurPreparationCafe(int codeErreur);
};

#endif // COMMUNICATION_H
