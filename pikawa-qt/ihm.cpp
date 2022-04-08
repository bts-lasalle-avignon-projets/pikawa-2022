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
    gererSelectionCafes();

    initialiserIHM();

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

    activerboutonConnexionEtatDeconnecte();

    ui->selectionLongueurPreparation->setValue(LongueurCafe::Court);
    gererLongueurPreparation(LongueurCafe::Court);
    /**
     * @todo selectionner le café préféré et disponible
     */
    selectionnerColombia();
    afficherPageAcceuil();
}

void IHMPikawa::gererSelectionCafes()
{
    connect(ui->boutonColombia,
            SIGNAL(clicked()),
            this,
            SLOT(selectionnerColombia()));

    connect(ui->boutonIndonesia,
            SIGNAL(clicked()),
            this,
            SLOT(selectionnerIndonesia()));

    connect(ui->boutonEthiopia,
            SIGNAL(clicked()),
            this,
            SLOT(selectionnerEthiopia()));

    connect(ui->boutonVolluto,
            SIGNAL(clicked()),
            this,
            SLOT(selectionnerVolluto()));

    connect(ui->boutonCosi, SIGNAL(clicked()), this, SLOT(selectionnerCosi()));

    connect(ui->boutonScuro,
            SIGNAL(clicked()),
            this,
            SLOT(selectionnerScuro()));

    connect(ui->boutonVanilla,
            SIGNAL(clicked()),
            this,
            SLOT(selectionnerVanilla()));

    connect(ui->boutonCapriccio,
            SIGNAL(clicked()),
            this,
            SLOT(selectionnerCapriccio()));
}

void IHMPikawa::gererEvenements()
{
    connect(ui->selectionLongueurPreparation,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(gererLongueurPreparation(int)));

    connect(ui->boutonInformations,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageInformations()));

    connect(ui->boutonEntretien,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageEntretien()));

    connect(ui->boutonParametres,
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

    connect(ui->boutonConnexion,
            SIGNAL(clicked()),
            cafetiere,
            SLOT(gererConnexion()));

    connect(ui->bontonChangerCafe,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageSelectionCafe()));

    connect(ui->boutonAcceuilSelectionCafe,
            SIGNAL(clicked()),
            this,
            SLOT(afficherPageAcceuil()));

    connect(cafetiere,
            SIGNAL(cafetiereDetectee(QString, QString)),
            this,
            SLOT(activerboutonConnexionEtatDetecte(QString, QString)));
    connect(cafetiere,
            SIGNAL(cafetiereConnectee(QString, QString)),
            this,
            SLOT(activerboutonConnexionEtatConnecte(QString, QString)));
    connect(cafetiere,
            SIGNAL(cafetiereDeconnectee()),
            this,
            SLOT(activerboutonConnexionEtatDeconnecte()));

    connect(ui->boutonRafraichir,
            SIGNAL(clicked()),
            this,
            SLOT(rafraichirDecouverte()));
    connect(cafetiere,
            SIGNAL(rechercheTerminee(bool)),
            this,
            SLOT(terminerDecouverte(bool)));
}

void IHMPikawa::gererLongueurPreparation(int longueurPreparation)
{
    QStringList labelsLongueurPreparation;
    labelsLongueurPreparation << "Court"
                              << "Moyen"
                              << "Long";

    qDebug() << Q_FUNC_INFO << "longueurPreparation" << longueurPreparation;
    ui->labelLongueurPreparation->setText(
      labelsLongueurPreparation.at(longueurPreparation));
    cafetiere->setLongueurChoisie(longueurPreparation);
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

void IHMPikawa::activerboutonConnexionEtatDetecte(QString nom, QString adresse)
{
    qDebug() << Q_FUNC_INFO << nom << adresse;
    // si une cafetère pikawa a été détectée
    ui->boutonConnexion->setEnabled(true);
    ui->boutonConnexion->setIcon(*iconeBoutonDetectee);
    ui->labelEtatConnexion->setText("Cafetière détectée");
}

/**
 * @todo revoir la gestion de la connexion/déconnexion
 */
void IHMPikawa::activerboutonConnexionEtatConnecte(QString nom, QString adresse)
{
    qDebug() << Q_FUNC_INFO << nom << adresse;
    // si une cafetère pikawa a été connectée
    ui->boutonConnexion->setEnabled(true);
    ui->boutonConnexion->setIcon(*iconeBoutonConnecte);
    ui->labelEtatConnexion->setText("Cafetière connectée");
    ui->boutonRafraichir->setEnabled(false);
}

void IHMPikawa::activerboutonConnexionEtatDeconnecte()
{
    qDebug() << Q_FUNC_INFO;
    // si une cafetère pikawa a été déconnectée
    ui->boutonConnexion->setEnabled(true);
    ui->boutonConnexion->setIcon(*iconeBoutonDeconnecte);
    ui->labelEtatConnexion->setText("Cafetière déconnectée");
    ui->boutonRafraichir->setEnabled(true);
}

void IHMPikawa::rafraichirDecouverte()
{
    qDebug() << Q_FUNC_INFO;
    ui->boutonRafraichir->setEnabled(false);
    cafetiere->demarrerDecouverte();
}

void IHMPikawa::terminerDecouverte(bool detecte)
{
    qDebug() << Q_FUNC_INFO << "detecte" << detecte;
    ui->boutonRafraichir->setEnabled(true);
}

void IHMPikawa::selectionnerColombia()
{
    ui->capsuleChoisie->setText("Colombia");
    cafetiere->setCapsuleChoisie(Colombia);
    afficherPageAcceuil();
}

void IHMPikawa::selectionnerIndonesia()
{
    ui->capsuleChoisie->setText("Indonesia");
    cafetiere->setCapsuleChoisie(Indonesia);
    afficherPageAcceuil();
}

void IHMPikawa::selectionnerEthiopia()
{
    ui->capsuleChoisie->setText("Ethiopia");
    cafetiere->setCapsuleChoisie(Ethiopia);
    afficherPageAcceuil();
}

void IHMPikawa::selectionnerVolluto()
{
    ui->capsuleChoisie->setText("Volluto");
    cafetiere->setCapsuleChoisie(Volluto);
    afficherPageAcceuil();
}

void IHMPikawa::selectionnerCosi()
{
    ui->capsuleChoisie->setText("Cosi");
    cafetiere->setCapsuleChoisie(Cosi);
    afficherPageAcceuil();
}

void IHMPikawa::selectionnerScuro()
{
    ui->capsuleChoisie->setText("Scuro");
    cafetiere->setCapsuleChoisie(Scuro);
    afficherPageAcceuil();
}

void IHMPikawa::selectionnerVanilla()
{
    ui->capsuleChoisie->setText("Vanilla");
    cafetiere->setCapsuleChoisie(Vanilla);
    afficherPageAcceuil();
}

void IHMPikawa::selectionnerCapriccio()
{
    ui->capsuleChoisie->setText("Capriccio");
    cafetiere->setCapsuleChoisie(Capriccio);
    afficherPageAcceuil();
}
