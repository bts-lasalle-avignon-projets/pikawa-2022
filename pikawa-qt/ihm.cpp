#include "ihm.h"
#include "ui_ihm.h"
#include <QDebug>

/**
 * @file ihm.cpp
 *
 * @brief Définition de la classe IHMPikawa
 * @author
 * @version 1.0
 *
 */

IHMPikawa::IHMPikawa(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHMPikawa)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

    ui->statusbar->showMessage(QString::fromUtf8("Pikawa 2022"));

#ifdef PLEIN_ECRAN
    showFullScreen();
// showMaximized();
#endif
}

IHMPikawa::~IHMPikawa()
{
    delete ui;
    qDebug() << Q_FUNC_INFO;
}
