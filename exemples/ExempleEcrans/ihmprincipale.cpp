#include "ihmprincipale.h"
#include "ui_ihmprincipale.h"
#include <QDebug>

/**
 * @file ihmprincipale.cpp
 *
 * @brief Définition de la classe IHMPrincipale
 * @author Thierry Vaira <tvaira@free.fr>
 * @version 1.0
 *
 */

/**
 * @brief Constructeur de la classe IHMPrincipale
 *
 * @fn IHMPrincipale::IHMPrincipale
 * @param parent L'adresse de l'objet parent, si nullptr IHMPrincipale sera la
 * fenêtre principale de l'application
 */

IHMPrincipale::IHMPrincipale(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHMPrincipale), nbChangementsEcran(0)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

    retourEcran2 = new ImageBouton(":precedent.png");
    ui->layoutBas->addWidget(retourEcran2);
    connect(retourEcran2,
            SIGNAL(clicked()),
            this,
            SLOT(afficherEcranPrecedent()));

#ifdef TEST_IHMPRINCIPALE
    fixerRaccourcisClavier();
#endif

    afficherEcranAccueil();

#ifdef PLEIN_ECRAN
    showFullScreen();
// showMaximized();
#endif
}

/**
 * @brief Destructeur de la classe IHMPrincipale
 *
 * @fn IHMPrincipale::~IHMPrincipale
 * @details Libère les ressources de l'application
 */
IHMPrincipale::~IHMPrincipale()
{
    delete ui;
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Méthode qui affiche l'écran d'accueil
 *
 * @fn IHMPrincipale::afficherEcranAccueil
 */
void IHMPrincipale::afficherEcranAccueil()
{
    afficherEcran(IHMPrincipale::Accueil);
}

/**
 * @brief Méthode qui permet d'afficher un numéro d'écran de la pile
 * QStackedWidget
 *
 * @fn IHMPrincipale::afficherEcran
 * @param ecran le numéro d'écran à afficher
 */
void IHMPrincipale::afficherEcran(IHMPrincipale::Ecran ecran)
{
    qDebug() << Q_FUNC_INFO << "ecran" << ecran;
    ui->ecrans->setCurrentIndex(ecran);
    ++nbChangementsEcran;
    if(ecran == IHMPrincipale::Ecran2)
        ui->labelNbChangements->setText(QString::number(nbChangementsEcran));
}

/**
 * @brief Méthode qui permet d'afficher l'écran suivant dans la pile
 * QStackedWidget
 *
 * @fn IHMPrincipale::afficherEcranSuivant
 */
void IHMPrincipale::afficherEcranSuivant()
{
    int ecranCourant = IHMPrincipale::Ecran(ui->ecrans->currentIndex());
    int ecranSuivant = (ecranCourant + 1) % int(IHMPrincipale::NbEcrans);
    afficherEcran(IHMPrincipale::Ecran(ecranSuivant));
}

/**
 * @brief Méthode qui permet d'afficher l'écran précédent dans la pile
 * QStackedWidget
 *
 * @fn IHMPrincipale::afficherEcranPrecedent
 */
void IHMPrincipale::afficherEcranPrecedent()
{
    int ecranCourant   = ui->ecrans->currentIndex();
    int ecranPrecedent = (ecranCourant - 1) % int(IHMPrincipale::NbEcrans);
    if(ecranPrecedent == -1)
        ecranPrecedent = int(IHMPrincipale::NbEcrans) - 1;
    afficherEcran(IHMPrincipale::Ecran(ecranPrecedent));
}

/**
 * @brief Méthode qui permet de fermer la fenêtre principale de l'application
 *
 * @fn IHMPrincipale::fermerApplication
 */
void IHMPrincipale::fermerApplication()
{
    this->close();
    qDebug() << Q_FUNC_INFO;
}

#ifdef TEST_IHMPRINCIPALE
/**
 * @brief Méthode qui initialise les raccourcis clavier
 *
 * @fn IHMPrincipale::fixerRaccourcisClavier
 */
void IHMPrincipale::fixerRaccourcisClavier()
{
    // Ctrl-Q pour quitter
    QAction* quitter = new QAction(this);
    quitter->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    addAction(quitter);
    connect(quitter, SIGNAL(triggered()), this, SLOT(fermerApplication()));

    // Flèche droite pour écran suivant
    QAction* actionAllerDroite = new QAction(this);
    actionAllerDroite->setShortcut(QKeySequence(Qt::Key_Right));
    addAction(actionAllerDroite);
    connect(actionAllerDroite,
            SIGNAL(triggered()),
            this,
            SLOT(afficherEcranSuivant()));

    // Flèche gauche pour écran précédent
    QAction* actionAllerGauche = new QAction(this);
    actionAllerGauche->setShortcut(QKeySequence(Qt::Key_Left));
    addAction(actionAllerGauche);
    connect(actionAllerGauche,
            SIGNAL(triggered()),
            this,
            SLOT(afficherEcranPrecedent()));
}
#endif
