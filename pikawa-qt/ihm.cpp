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
 * @version 1.0
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
    QMainWindow(parent), ui(new Ui::IHMPikawa)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

    baseDeDonnees = BaseDeDonnees::getInstance();
    baseDeDonnees->ouvrir(NOM_BDD);

    QIcon bouttonConnecte(":/images/cafetiere-on.png");
    QIcon bouttonDeconnecte(":/images/cafetiere-off.png");

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
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

void IHMPikawa::initialiserIHM()
{
    ui->statusbar->showMessage(QString::fromUtf8(NOM) + " " +
                               QString::fromUtf8(VERSION));

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

    connect(ui->bouttonInformations,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageInformations()));

    connect(ui->bouttonEntretien,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageEntretien()));

    connect(ui->bouttonParametres,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageParametres()));

    connect(ui->bouttonAcceuilInformation,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageAcceuil()));

    connect(ui->bouttonEntretienInformation,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageEntretien()));

    connect(ui->bouttonParametresInformation,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageParametres()));

    connect(ui->bouttonConnecter,
            SIGNAL(clicked()),
            cafetiere,
            SLOT(connecter()));
    ui->bouttonConnecter->setEnabled(false);
    connect(cafetiere,
            SIGNAL(cafetiereDetectee(QString, QString)),
            this,
            SLOT(activerBoutonConnecter(QString, QString)));
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
    afficherPage(IHMPikawa::Page(0));
}

void IHMPikawa::afficherPageInformations()
{
    afficherPage(IHMPikawa::Page(1));
}

void IHMPikawa::afficherPageEntretien()
{
    afficherPage(IHMPikawa::Page(2));
}

void IHMPikawa::afficherPageParametres()
{
    afficherPage(IHMPikawa::Page(3));
}

void IHMPikawa::activerBoutonConnecter(QString nom, QString adresse)
{
    qDebug() << Q_FUNC_INFO << nom << adresse;
    // si une cafetère pikawa a été détectée
    ui->bouttonConnecter->setEnabled(true);
    setBouttonConnecte();
    ui->labelEtatConnexion->setText("Cafetiere connectée");
}

void IHMPikawa::setBouttonConnecte()
{
    ui->bouttonConnecter->setIcon(bouttonConnecte);
}

void IHMPikawa::setBouttonDeconnecte()
{
    ui->bouttonConnecter->setIcon(bouttonDeconnecte);
}

