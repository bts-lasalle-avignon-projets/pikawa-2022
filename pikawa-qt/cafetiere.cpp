#include "cafetiere.h"
#include "ihm.h"
#include "protocole.h"
#include "communication.h"
#include "preparation.h"
#include "basededonnees.h"
#include <QDebug>

/**
 * @file cafetiere.cpp
 *
 * @brief Définitionde la classe Cafetiere
 * @author Anthony BRYCKAERT
 * @version 1.1
 */

Cafetiere::Cafetiere(IHMPikawa* ihm) :
    QObject(ihm), ihm(ihm), communication(new Communication(this)),
    preparation(new Preparation(this)), nomCapsules(0), nomLongueurs(0),
    capsuleChoisie(0), longueurChoisie(0), niveauEau(0), connectee(false),
    capsulePresente(false), tassePresente(false), cafeEnPreparation(false)
{
    // qDebug() << Q_FUNC_INFO << qApp->applicationFilePath();
    ouvrirBaseDeDonnees();
    gererEvenements();
    gererEvenementsCommunication();
    /**
     * @todo Gérer l'utilisateur connecté (identifiant ou badge) à cette
     * cafetière (cf. Etudiant IR 4)
     */
    chargerPreferences(IDENTIFIANT_UTILISATEUR);
    initialiserNomCapsules();
    initiatiserNomLongueurs();
}

Cafetiere::~Cafetiere()
{
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

QStringList Cafetiere::getNomcapsules() const
{
    return nomCapsules;
}

QStringList Cafetiere::getNomLongueurs() const
{
    return nomLongueurs;
}

int Cafetiere::getCaspuleChoisie() const
{
    return capsuleChoisie;
}

int Cafetiere::getLongueurChoisie() const
{
    return longueurChoisie;
}

int Cafetiere::getNiveauEau() const
{
    return niveauEau;
}

int Cafetiere::getNiveauEauNecessaire() const
{
    return preparation->getNiveauEauNecessaire();
}

bool Cafetiere::estConnectee() const
{
    return connectee;
}

bool Cafetiere::getCapsulePresente() const
{
    return capsulePresente;
}

bool Cafetiere::getTassePresente() const
{
    return tassePresente;
}

bool Cafetiere::estCafeEnPreparation() const
{
    return cafeEnPreparation;
}

int Cafetiere::getIdCapsule(QString nomCapsule) const
{
    if(nomCapsules.isEmpty() || nomCapsule.isEmpty())
        return -1;
    return nomCapsules.indexOf(nomCapsule);
}

QStringList Cafetiere::getPreferences() const
{
    return preferences;
}

QString Cafetiere::getCapsulePreferee() const
{
    if(!preferences.isEmpty())
    {
        qDebug() << Q_FUNC_INFO
                 << preferences.at(Cafetiere::ChampsTablePreferences::
                                     COLONNE_PREFERENCES_DESIGNATION_CAPSULE);
        return preferences.at(Cafetiere::ChampsTablePreferences::
                                COLONNE_PREFERENCES_DESIGNATION_CAPSULE);
    }
    return QString();
}

QString Cafetiere::getLongueurPreferee() const
{
    if(!preferences.isEmpty())
    {
        qDebug() << Q_FUNC_INFO
                 << preferences.at(Cafetiere::ChampsTablePreferences::
                                     COLONNE_PREFERENCES_TYPE_BOISSON);
        return preferences.at(
          Cafetiere::ChampsTablePreferences::COLONNE_PREFERENCES_TYPE_BOISSON);
    }
    return QString();
}

/**
 * @fn Cafetiere::setCapsuleChoisie(const int& capsuleChoisie)
 * @brief Met à jour dans la base de données la caspule préférée de
 * l'utilisateur
 * @details Table concernée Preferences
 */
void Cafetiere::setCapsuleChoisie(const int& capsuleChoisie)
{
    if(this->capsuleChoisie != capsuleChoisie)
    {
        if(estCapsuleChoisieDisponible(capsuleChoisie))
        {
            this->capsuleChoisie = capsuleChoisie;
            QString requete      = "UPDATE Preferences SET capsuleActuelle='" +
                              QString::number(capsuleChoisie + 1) +
                              "' WHERE Preferences.idUtilisateur='" +
                              IDENTIFIANT_UTILISATEUR_ID + "'";
            baseDeDonneesPikawa->executer(requete);
        }
    }
}
/**

 * @fn Cafetiere::setLongueurChoisie(const int& longueurChoisie)
 * @brief Met à jour dans la base de données la longueur préférée de
 * l'utilisateur
 * @details Table concernée Preferences
 */
void Cafetiere::setLongueurChoisie(const int& longueurChoisie)
{
    preparation->setNiveauEauNecessaire(longueurChoisie);
    this->longueurChoisie = longueurChoisie;
    if(this->longueurChoisie != capsuleChoisie)
    {
        this->longueurChoisie = longueurChoisie;
        QString requete       = "UPDATE Preferences SET typeBoissonActuelle='" +
                          QString::number(longueurChoisie + 1) +
                          "' WHERE Preferences.idUtilisateur='" +
                          IDENTIFIANT_UTILISATEUR_ID + "'";
        baseDeDonneesPikawa->executer(requete);
    }
}

void Cafetiere::setNiveauEau(const int& niveauEau)
{
    this->niveauEau = niveauEau;
}

/**
 * @fn Cafetiere::preparerCafetiere()
 * @brief Verifie si il est possible de lancer un café et prepare la cafetiere.
 */
bool Cafetiere::preparerCafetiere()
{
    qDebug() << Q_FUNC_INFO << "estPreparationPrete"
             << preparation->estPreparationPrete() << "estCafeEnPreparation"
             << cafeEnPreparation << "estCapsuleChoisieDisponible"
             << estCapsuleChoisieDisponible();
    if(preparation->estPreparationPrete() && communication->estConnecte() &&
       !cafeEnPreparation && estCapsuleChoisieDisponible())
    {
        /**
         * Cafetiere prête :
         * envoie d'un signal pour activer le bouton GO
         */
        emit cafetierePrete();
        qDebug() << Q_FUNC_INFO << "Prête";
        emit etatCafetiere(niveauEau,
                           preparation->getBacPasPlein(),
                           preparation->getCapsulePresente(),
                           preparation->getTassePresente());
        return true;
    }
    else
    {
        /**
         * Cafetiere pas prête :
         * envoie d'un signal pour désactiver le bouton GO
         */
        emit cafetierePasPrete();
        emit etatCafetiere(niveauEau,
                           preparation->getBacPasPlein(),
                           preparation->getCapsulePresente(),
                           preparation->getTassePresente());
        qDebug() << Q_FUNC_INFO << "Pas prête";
        return false;
    }
}

/**
 * @fn Cafetiere::getDisponibiliteCapsules() const
 * @brief Récupère dans la base de données la présence des capsules
 */
QStringList Cafetiere::getDisponibiliteCapsules() const
{
    QString     requete = "SELECT quantite FROM StockMagasin";
    QStringList caspuleDisponibles;
    baseDeDonneesPikawa->recuperer(requete, caspuleDisponibles);
    return caspuleDisponibles;
}

/**
 * @fn Cafetiere::estCapsuleChoisieDisponible()
 * @brief Récupère dans la base de données la présence de la capsule choisie
 */
bool Cafetiere::estCapsuleChoisieDisponible()
{
    QString requete = "SELECT quantite FROM StockMagasin WHERE rangee = " +
                      QString::number(capsuleChoisie + 1);
    QString reponseQuantite = "";

    baseDeDonneesPikawa->recuperer(requete, reponseQuantite);
    qDebug() << Q_FUNC_INFO << "capsuleChoisie" << capsuleChoisie
             << "reponseQuantite " << reponseQuantite;
    if(reponseQuantite.toInt() >= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @fn Cafetiere::estCapsuleChoisieDisponible(int capsule)
 * @brief Récupère dans la base de données la présence de la capsule passée en
 * argument en paramètre
 */
bool Cafetiere::estCapsuleChoisieDisponible(int capsule)
{
    QString requete = "SELECT quantite FROM StockMagasin WHERE rangee = " +
                      QString::number(capsule + 1);
    QString reponseQuantite = "";

    baseDeDonneesPikawa->recuperer(requete, reponseQuantite);
    qDebug() << Q_FUNC_INFO << "capsule" << capsule << "reponseQuantite "
             << reponseQuantite;
    if(reponseQuantite.toInt() >= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Cafetiere::demarrerDecouverte()
{
    qDebug() << Q_FUNC_INFO;
    communication->activerLaDecouverte();
}

void Cafetiere::arreterDecouverte()
{
    qDebug() << Q_FUNC_INFO;
    communication->desactiverLaDecouverte();
}

void Cafetiere::rafraichirDecouverte()
{
    qDebug() << Q_FUNC_INFO;
    communication->desactiverLaDecouverte();
    communication->activerLaDecouverte();
}

void Cafetiere::gererConnexion()
{
    qDebug() << Q_FUNC_INFO;
    if(communication->estConnecte())
    {
        communication->deconnecter();
        preparerCafetiere();
    }
    else
    {
        communication->connecter();
    }
}

/**
 * @fn Cafetiere::mettreAJourConnexion(QString nom, QString adresse)
 * @brief Met à jour l'état de connexion
 * des trames d'états
 */
void Cafetiere::mettreAJourConnexion(QString nom, QString adresse)
{
    this->connectee = true;
    emit cafetiereConnectee(nom, adresse);
    recupererEtatCafetiere();
    recupererEtatMagasin();
}

/**
 * @fn Cafetiere::recupererEtatCafetiere()
 * @brief Envoie d'une trame d'état cafetiere
 * @details $PIKAWA;ETAT;C;\r\n
 */
void Cafetiere::recupererEtatCafetiere()
{
    communication->envoyerTrame(TRAME_DEMANDE_ETAT_CAFETIERE);
}

/**
 * @fn Cafetiere::recupererEtatMagasin()
 * @brief Envoie d'une trame d'état magasin
 * @details $PIKAWA;ETAT;M;\r\n
 */
void Cafetiere::recupererEtatMagasin()
{
    communication->envoyerTrame(TRAME_DEMANDE_ETAT_MAGASIN);
}

/**
 * @fn Cafetiere::mettreAJourEtatCafetiere(int  reservoirEau,
                                         bool bacPasPlein,
                                         bool etatCapsule,
                                         bool etatTasse)
 * @brief Slot qui met à jour les états de la cafetiere
 * @details Le signal passe les états de la cafetiere sous forme de parametres
 */
void Cafetiere::mettreAJourEtatCafetiere(int  reservoirEau,
                                         bool bacPasPlein,
                                         bool etatCapsule,
                                         bool etatTasse)
{
    qDebug() << Q_FUNC_INFO << reservoirEau << bacPasPlein << etatCapsule
             << etatTasse;

    this->setNiveauEau(reservoirEau);
    preparation->setBacPasPlein(bacPasPlein);
    preparation->setCapsulePresente(etatCapsule);
    preparation->setTassePresente(etatTasse);

    preparerCafetiere();
    emit etatCafetiere(reservoirEau, bacPasPlein, etatCapsule, etatTasse);
}

/**
 * @fn Cafetiere::mettreAJourMagasin(QStringList caspulesDisponibles)
 * @brief Slot qui met à jour les champs de la table magasin dans la base de
 * données
 * @details Requête UPDATE
 */
void Cafetiere::mettreAJourMagasin(QStringList caspulesDisponibles)
{
    qDebug() << Q_FUNC_INFO << caspulesDisponibles;
    QString requete;
    for(int i = 0; i < caspulesDisponibles.size(); ++i)
    {
        requete =
          "UPDATE StockMagasin SET quantite=" + caspulesDisponibles.at(i) +
          " WHERE rangee=" + QString::number((i + 1));
        baseDeDonneesPikawa->executer(requete);
    }

    /**
     * Envoie des disponibilités des capsules à l'IHM
     */
    emit etatMagasinIHM(caspulesDisponibles);
    bool pret = preparerCafetiere();
    qDebug() << Q_FUNC_INFO << pret;
}

void Cafetiere::gererEtatPreparationCafe(int preparationCafe)
{
    qDebug() << Q_FUNC_INFO << preparationCafe;
    /**
     * @brief Changement d'état :
     * EnAttente -> EnCours -> Pret
     * EnAttente -> Impossible -> EnAttente
     * Remarque : l'état Pret passera EnAttente pour un prochain café puisque la
     * tasse sera détectée
     */
    if(preparationCafe == CAFE_PRET)
    {
        this->cafeEnPreparation = false;
        emit cafePret();
    }
    else if(preparationCafe == CAFE_EN_PREPARATION)
    {
        this->cafeEnPreparation = true;
        emit cafeEnCours();
        incrementerNombreCafeJour();
        incrementerNombreCafeDepuisDetartrage();
        recupererEtatMagasin();
        decrementerNombreCafeAvantDetartrage();
    }
    else
    {
        this->cafeEnPreparation = false;
        emit erreurPreparation();
    }
}

/**
 * @fn Cafetiere::lancerLaPreparationCafe()
 * @brief Envoie une trame de préparation
 * @details Exemple PIKAWA;7;2;\r\n
 */
void Cafetiere::lancerLaPreparationCafe()
{
    communication->envoyerTramePreparation(capsuleChoisie, longueurChoisie);
    // recupererEtatCafetiere();
    // recupererEtatMagasin();
}

void Cafetiere::initialiserNomCapsules()
{
    this->nomCapsules = preparation->getNomCapsules();
}

void Cafetiere::initiatiserNomLongueurs()
{
    this->nomLongueurs = preparation->getNomLongueurs();
}

/**
 * @fn Cafetiere::chargerPreferences(QString identifiantUtilisateur)
 * @brief Récupère dans la base de données la dernière capsule choisie et
 * longueur de l'utilisateur
 * @details Selectionne des champs de plusieurs tables grâce à INNER JOIN
 */
void Cafetiere::chargerPreferences(QString identifiantUtilisateur)
{
    qDebug() << Q_FUNC_INFO << identifiantUtilisateur;
    QString requete =
      "SELECT Preferences.idPreferences, Utilisateur.idUtilisateur, "
      "Utilisateur.nom, Utilisateur.prenom, Capsule.idCapsule, "
      "Capsule.designation, Capsule.description, "
      "TypeBoisson.idTypeBoisson,typeBoisson.type FROM Preferences INNER JOIN "
      "Utilisateur ON Utilisateur.idUtilisateur=Preferences.idUtilisateur "
      "INNER JOIN Capsule ON Capsule.idCapsule=Preferences.capsuleActuelle "
      "INNER JOIN TypeBoisson ON "
      "TypeBoisson.idTypeBoisson=Preferences.typeBoissonActuelle WHERE "
      "Utilisateur.identifiant='" +
      identifiantUtilisateur + "';";
    baseDeDonneesPikawa->recuperer(requete, preferences);
    qDebug() << Q_FUNC_INFO << preferences;
}

void Cafetiere::gererEvenements()
{
    connect(ihm,
            SIGNAL(detartrageReinitialise()),
            this,
            SLOT(reinitialiserDetartrageBaseDeDonnees()));
}

void Cafetiere::gererEvenementsCommunication()
{
    connect(communication,
            SIGNAL(cafetiereDetectee(QString, QString)),
            this,
            SIGNAL(cafetiereDetectee(QString, QString)));
    connect(communication,
            SIGNAL(cafetiereConnectee(QString, QString)),
            this,
            SLOT(mettreAJourConnexion(QString, QString)));
    connect(communication,
            SIGNAL(cafetiereDeconnectee()),
            this,
            SIGNAL(cafetiereDeconnectee()));

    connect(communication,
            SIGNAL(cafetiereDeconnectee()),
            this,
            SLOT(setDeconnectee())),

      connect(communication,
              SIGNAL(rechercheTerminee(bool)),
              this,
              SIGNAL(rechercheTerminee(bool)));
    connect(communication,
            SIGNAL(etatCafetiere(int, bool, bool, bool)),
            this,
            SLOT(mettreAJourEtatCafetiere(int, bool, bool, bool)));
    connect(communication,
            SIGNAL(etatMagasin(QStringList)),
            this,
            SLOT(mettreAJourMagasin(QStringList)));
    connect(communication,
            SIGNAL(cafeEnPreparation(int)),
            this,
            SLOT(gererEtatPreparationCafe(int)));
}

void Cafetiere::ouvrirBaseDeDonnees()
{
    baseDeDonneesPikawa = BaseDeDonnees::getInstance();
    baseDeDonneesPikawa->ouvrir(NOM_BDD);
}

/**
 * @fn Cafetiere::incrementerNombreCafeJour()
 * @brief Effectue une requête dans la base de données pour incrémenter le
 * nombre de café
 * @details Table concernée Entretien
 */
void Cafetiere::incrementerNombreCafeJour()
{
    QString requete        = "SELECT nombreCafeTotal FROM Entretien";
    QString nombreCafeJour = "";
    bool    retour = baseDeDonneesPikawa->recuperer(requete, nombreCafeJour);
    if(!retour)
    {
        emit erreurAccesBaseDeDonnees();
    }
    else
    {
        QString nombreCafeJourIncremente =
          QString::number(nombreCafeJour.toInt() + 1);
        requete =
          "UPDATE Entretien SET nombreCafeTotal = " + nombreCafeJourIncremente;
        qDebug() << Q_FUNC_INFO << requete;
        baseDeDonneesPikawa->executer(requete);
        emit nombreCafesTotal(nombreCafeJourIncremente);
    }
}

/**
 * @fn Cafetiere::decrementerNombreCafeAvantDetartrage()
 * @brief Effectue une requête dans la base de données pour décrémenter le
 * nombre de café
 * @details Table concernée Entretien
 */
void Cafetiere::decrementerNombreCafeAvantDetartrage()
{
    QString requete = "SELECT nombreCafeAvantDetartrage FROM Entretien";
    QString nombreCafeAvantDetartrage;
    bool    retour =
      baseDeDonneesPikawa->recuperer(requete, nombreCafeAvantDetartrage);
    if(!retour)
    {
        emit erreurAccesBaseDeDonnees();
    }
    else if(nombreCafeAvantDetartrage.toInt() > 0)
    {
        qDebug() << Q_FUNC_INFO << "nombreCafeAvantDetartrage "
                 << nombreCafeAvantDetartrage;
        QString nombreCafeJourDecremente =
          QString::number(nombreCafeAvantDetartrage.toInt() - 1);
        requete = "UPDATE Entretien SET nombreCafeAvantDetartrage = " +
                  nombreCafeJourDecremente;
        qDebug() << Q_FUNC_INFO << "requete de decrementation" << requete;
        baseDeDonneesPikawa->executer(requete);
        emit nombreCafesAvantDetartrage(nombreCafeJourDecremente);
    }
}

/**
 * @fn Cafetiere::getNombreCafeJour() const
 * @brief Effectue une requête dans la base de données pour recuperer le nombre
 * de café effectué
 * @details Table concernée Entretien
 */
QString Cafetiere::getNombreCafeJour() const
{
    QString requete        = "SELECT nombreCafeTotal FROM Entretien";
    QString nombreCafeJour = "";
    baseDeDonneesPikawa->recuperer(requete, nombreCafeJour);
    return nombreCafeJour;
}

/**
 * @fn Cafetiere::getNombreCafeAvantDetartrage() const
 * @brief Effectue une requête dans la base de données pour recuperer le nombre
 * de café avant le prochain détartrage
 * @details Table concernée Entretien
 */
QString Cafetiere::getNombreCafeAvantDetartrage() const
{
    QString requete = "SELECT nombreCafeAvantDetartrage FROM Entretien";
    QString nombreCafeAvantDetartrage = "";
    baseDeDonneesPikawa->recuperer(requete, nombreCafeAvantDetartrage);
    return nombreCafeAvantDetartrage;
}

void Cafetiere::reinitialiserDetartrageBaseDeDonnees()
{
    QString requete = "UPDATE Entretien SET nombreCafeAvantDetartrage = " +
                      QString::number(NOMBRE_CAFE_AVANT_DETARTRAGE);
    baseDeDonneesPikawa->executer(requete);
    requete = "UPDATE Entretien SET nombreCafeDepuisDetartrage = " +
              QString::number(NOMBRE_CAFE_DEPUIS_DETARTRAGE_REINITIALISE);
    baseDeDonneesPikawa->executer(requete);
}

void Cafetiere::setDeconnectee()
{
    this->connectee = false;
}

void Cafetiere::incrementerNombreCafeDepuisDetartrage()
{
    QString requete = "SELECT nombreCafeDepuisDetartrage FROM Entretien";
    QString nombreCafeDepuisDetartrage;
    baseDeDonneesPikawa->recuperer(requete, nombreCafeDepuisDetartrage);
    requete = "UPDATE Entretien SET nombreCafeDepuisDetartrage = " +
              QString::number(nombreCafeDepuisDetartrage.toInt() + 1);
    baseDeDonneesPikawa->executer(requete);
    emit nombreDeCafeDepuisDetartrage(
      QString::number(nombreCafeDepuisDetartrage.toInt() + 1));
}

QString Cafetiere::getNombreCafeDepuisDetartrage() const
{
    QString requete = "SELECT nombreCafeDepuisDetartrage FROM Entretien";
    QString nombreCafeDepuisDetartrage;
    baseDeDonneesPikawa->recuperer(requete, nombreCafeDepuisDetartrage);
    return nombreCafeDepuisDetartrage;
}
