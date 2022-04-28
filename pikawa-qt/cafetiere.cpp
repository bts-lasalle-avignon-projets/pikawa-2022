#include "cafetiere.h"
#include "ihm.h"
#include "communication.h"
#include "preparation.h"
#include "basededonnees.h"
#include <QDebug>

/**
 * @file cafetiere.cpp
 *
 * @brief Définitionde la classe Cafetiere
 * @author
 * @version 0.2
 *
 */

Cafetiere::Cafetiere(IHMPikawa* ihm) :
    QObject(ihm), ihm(ihm), communication(new Communication(this)),
    preparation(new Preparation(this)), nomCapsules(0), nomLongueurs(0),
    capsuleChoisie(0), longueurChoisie(0), niveauEau(0), niveauEauNecessaire(0),
    connectee(false), activee(false), capsulePresente(false),
    tassePresente(false), estCafeEnPreparation(false)
{
    // qDebug() << Q_FUNC_INFO << qApp->applicationFilePath();
    ouvrirBaseDeDonnees();
    gererEvenements();
    gererEvenementsCommunication();
    /**
     * @todo Gérer l'utilisateur connecté (identifiant ou badge) à cette
     * cafetière
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

void Cafetiere::initialiserNomCapsules()
{
    this->nomCapsules = preparation->getNomCapsules();
}

void Cafetiere::initiatiserNomLongueurs()
{
    this->nomLongueurs = preparation->getNomLongueurs();
}

void Cafetiere::ouvrirBaseDeDonnees()
{
    baseDeDonneesPikawa = BaseDeDonnees::getInstance();
    baseDeDonneesPikawa->ouvrir(NOM_BDD);
}

void Cafetiere::chargerPreferences(QString identifiantUtilisateur)
{
    qDebug() << Q_FUNC_INFO << identifiantUtilisateur;
    QString requete =
      "SELECT Preferences.idPreferences, Utilisateur.idUtilisateur, "
      "Utilisateur.nom, Utilisateur.prenom, Capsule.idCapsule, "
      "Capsule.designation, Capsule.libelle, TypeBoisson.idTypeBoisson, "
      "TypeBoisson.type FROM Preferences INNER JOIN Utilisateur ON "
      "Utilisateur.idUtilisateur=Preferences.idUtilisateur INNER JOIN Capsule "
      "ON Capsule.idCapsule=Preferences.capsuleActuelle INNER JOIN TypeBoisson "
      "ON TypeBoisson.idTypeBoisson=Preferences.typeBoissonActuelle WHERE "
      "Utilisateur.identifiant='" +
      identifiantUtilisateur + "';";
    baseDeDonneesPikawa->recuperer(requete, preferences);
    qDebug() << Q_FUNC_INFO << preferences;
}

void Cafetiere::gererEvenements()
{
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
    return niveauEauNecessaire;
}

bool Cafetiere::getConnectee() const
{
    return connectee;
}

bool Cafetiere::getActivee() const
{
    return activee;
}

bool Cafetiere::getCapsulePresente() const
{
    return capsulePresente;
}

bool Cafetiere::getTassePresente() const
{
    return tassePresente;
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

void Cafetiere::setCapsuleChoisie(const int& capsuleChoisie)
{
    if(this->capsuleChoisie != capsuleChoisie)
    {
        this->capsuleChoisie = capsuleChoisie;
        QString requete      = "UPDATE Preferences SET capsuleActuelle='" +
                          QString::number(capsuleChoisie + 1) +
                          "' WHERE Preferences.idUtilisateur='" +
                          IDENTIFIANT_UTILISATEUR_ID + "'";
        baseDeDonneesPikawa->executer(requete);
    }
}

void Cafetiere::setLongueurChoisie(const int& longueurChoisie)
{
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

void Cafetiere::setNiveauEauNecessaire(const int& niveauEauNecessaire)
{
    this->niveauEauNecessaire = niveauEauNecessaire;
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
        communication->deconnecter();
    else
        communication->connecter();
}

bool Cafetiere::estPrete()
{
    qDebug() << Q_FUNC_INFO;
    if(preparation->estPreparationPrete() && communication->estConnecte() &&
       !estCafeEnPreparation && estCapsuleChoisieDisponible())
    {
        emit cafetierePrete();
        return true;
    }
    else
    {
        emit cafetierePasPrete();
        return false;
    }
}

void Cafetiere::mettreAJourConnexion(QString nom, QString adresse)
{
    emit cafetiereConnectee(nom, adresse);
    recupererEtatCafetiere();
    recupererEtatMagasin();
}

void Cafetiere::recupererEtatCafetiere()
{
    communication->envoyerTrame("$PIKAWA;ETAT;C;\r\n");
}

void Cafetiere::recupererEtatMagasin()
{
    communication->envoyerTrame("$PIKAWA;ETAT;M;\r\n");
}

void Cafetiere::mettreAJourEtatCafetiere(int  reservoirEau,
                                         bool bacCapsules,
                                         bool etatCapsule,
                                         bool etatTasse)
{
    qDebug() << Q_FUNC_INFO << reservoirEau << bacCapsules << etatCapsule
             << etatTasse;

    preparation->setNiveauEau(reservoirEau);
    preparation->setBacPlein(!bacCapsules);
    preparation->setCapsulePresente(etatCapsule);
    preparation->setTassePresente(etatTasse);

    qDebug() << Q_FUNC_INFO << estPrete();

    emit etatCafetiere(reservoirEau, bacCapsules, etatCapsule, etatTasse);
}

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
    emit etatMagasinIHM(caspulesDisponibles);
    estPrete();
}

void Cafetiere::gererEtatPreparationCafe(int preparationCafe)
{
    qDebug() << Q_FUNC_INFO << preparationCafe;
    if(preparationCafe == CAFE_PRET)
    {
        this->estCafeEnPreparation = false;
        emit cafePret();
    }

    else if(preparationCafe == CAFE_EN_PREPARATION)
    {
        this->estCafeEnPreparation = true;
    }

    else
    {
        this->estCafeEnPreparation = false;
        emit erreurPreparation();
    }
}

void Cafetiere::lancerLaPreparationCafe()
{
    communication->envoyerTramePreparation(capsuleChoisie, longueurChoisie);
    /**
     * @todo Est-ce vraiment utile ? Les trames d'états sont envoyées
     * automatiquement par la cafetière !
     */
    recupererEtatCafetiere();
    recupererEtatMagasin();
}

QStringList Cafetiere::getDisponibiliteCapsules() const
{
    QString     requete = "SELECT quantite FROM StockMagasin";
    QStringList caspuleDisponibles;
    baseDeDonneesPikawa->recuperer(requete, caspuleDisponibles);
    return caspuleDisponibles;
}

bool Cafetiere::estCapsuleChoisieDisponible()
{
    QString requete = "SELECT quantite FROM StockMagasin WHERE rangee = " +
                      QString::number(capsuleChoisie + 1);
    QString reponseQuantite = "";

    baseDeDonneesPikawa->recuperer(requete, reponseQuantite);
    qDebug() << Q_FUNC_INFO << "cafeChoisie" << capsuleChoisie
             << "reponseQuantite " << reponseQuantite;
    if(reponseQuantite.toInt() <= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
