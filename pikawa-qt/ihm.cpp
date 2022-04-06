#include "ihm.h"
#include "ui_ihm.h"
#include "basededonnees.h"
#include "cafetiere.h"
#include <QDebug>
#include <QIcon>

/**
 * @file ihm.cpp
 *
 * @brief Définition de la classe IHMPikawa
 * @author
 * @version 0.2
 *
 */

/**
 * @brief Constructeur de la classe IHMPikawa
 *
 * @fn IHMPikawa::IHMPikawa
 * @param parent L'adresse de l'objet parent, si nullptr IHMPikawa sera la
 * fenêtre principale de l'application
 */
IHMPikawa::IHMPikawa(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHMPikawa), iconeBoutonConnecte(nullptr),
    iconeBoutonDetectee(nullptr), iconeBoutonDeconnecte(nullptr)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

    baseDeDonnees = BaseDeDonnees::getInstance();
    baseDeDonnees->ouvrir(NOM_BDD);

    cafetiere = new Cafetiere(this);

    gererEvenements();

    initialiserIHM();

    cafetiere->demarrer();

#ifdef PLEIN_ECRAN
    showFullScreen();
// showMaximized();
#endif
}

/**
 * @brief Destructeur de la classe IHMPikawa
 *
 * @fn IHMPikawa::~IHMPikawa
 * @details Libère les ressources de l'application
 */

IHMPikawa::~IHMPikawa()
{
    delete ui;
    delete iconeBoutonDetectee;
    delete iconeBoutonConnecte;
    delete iconeBoutonDeconnecte;
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

void IHMPikawa::initialiserIHM()
{
    ui->statusbar->showMessage(QString::fromUtf8(NOM) + " " +
                               QString::fromUtf8(VERSION));

    iconeBoutonDetectee   = new QIcon(":/images/cafetiere-rouge.png");
    iconeBoutonConnecte   = new QIcon(":/images/cafetiere-verte.png");
    iconeBoutonDeconnecte = new QIcon(":/images/cafetiere-noire.png");

    ui->boutonConnecter->setIcon(*iconeBoutonDeconnecte);
    ui->labelEtatConnexion->setText("Cafetière déconnectée");

    ui->selectionLongueurPreparation->setValue(LongueurCafe::Court);
    afficherLongueurPreparation(LongueurCafe::Court);

    afficherPageAcceuil();
}

void IHMPikawa::gererEvenements()
{
    connect(ui->selectionLongueurPreparation,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(afficherLongueurPreparation(int)));

    connect(ui->boutonInformationsAccueil,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageInformations()));

    connect(ui->boutonEntretienAccueil,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageEntretien()));

    connect(ui->boutonParametresAccueil,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageParametres()));

    connect(ui->boutonAcceuilInformation,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageAcceuil()));

    connect(ui->boutonEntretienInformation,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageEntretien()));

    connect(ui->boutonParametresInformation,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageParametres()));

    connect(ui->boutonConnecter,
            SIGNAL(clicked()),
            cafetiere,
            SLOT(connecter()));
    ui->boutonConnecter->setEnabled(false);

    connect(cafetiere,
            SIGNAL(cafetiereDetectee(QString, QString)),
            this,
            SLOT(activerBoutonConnecter(QString, QString)));

    connect(ui->bontonChangerCafe,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageSelectionCafe()));

    connect(ui->boutonAcceuilSelectionCafe,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageAcceuil()));

    connect(cafetiere,
            SIGNAL(cafetiereConnectee(QString, QString)),
            this,
            SLOT(activerBoutonDeconnecter(QString, QString)));
    connect(cafetiere,
            SIGNAL(cafetiereDeconnectee(QString, QString)),
            this,
            SLOT(desactiverBoutonConnecter(QString, QString)));
}

void IHMPikawa::afficherLongueurPreparation(int longueurPreparation)
{
    QStringList labelsLongueurPreparation;
    labelsLongueurPreparation << "Court"
                              << "Moyen"
                              << "Long";

    qDebug() << Q_FUNC_INFO << "longueurPreparation" << longueurPreparation;
    ui->labelLongueurPreparation->setText(
      labelsLongueurPreparation.at(longueurPreparation));
}

void IHMPikawa::afficherPage(IHMPikawa::Page page)
{
    qDebug() << Q_FUNC_INFO << "page" << page;
    ui->ecrans->setCurrentIndex(page);
}

void IHMPikawa::afficherPageAcceuil()
{
    afficherPage(IHMPikawa::Page::Accueil);
}

void IHMPikawa::afficherPageInformations()
{
    afficherPage(IHMPikawa::Page::Information);
}

void IHMPikawa::afficherPageEntretien()
{
    afficherPage(IHMPikawa::Page::Entretien);
}

void IHMPikawa::afficherPageParametres()
{
    afficherPage(IHMPikawa::Page::Parametres);
}

void IHMPikawa::afficherPageSelectionCafe()
{
    afficherPage(IHMPikawa::Page::SelectionCafe);
}

void IHMPikawa::activerBoutonConnecter(QString nom, QString adresse)
{
    qDebug() << Q_FUNC_INFO << nom << adresse;
    // si une cafetère pikawa a été détectée
    ui->boutonConnecter->setEnabled(true);
    ui->boutonConnecter->setIcon(*iconeBoutonDetectee);
    ui->labelEtatConnexion->setText("Cafetière détectée");
}

void IHMPikawa::activerBoutonDeconnecter(QString nom, QString adresse)
{
    qDebug() << Q_FUNC_INFO << nom << adresse;
    // si une cafetère pikawa a été connectée
    ui->boutonConnecter->setEnabled(true);
    ui->boutonConnecter->setIcon(*iconeBoutonDeconnecte);
    ui->labelEtatConnexion->setText("Cafetière connectée");
}

void IHMPikawa::desactiverBoutonDeconnecter()
{
    qDebug() << Q_FUNC_INFO;
    // si une cafetère pikawa a été déconnectée
    ui->boutonConnecter->setEnabled(false);
    ui->boutonConnecter->setIcon(*iconeBoutonConnecte);
    ui->labelEtatConnexion->setText("Cafetière déconnectée");
}
