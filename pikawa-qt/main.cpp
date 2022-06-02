#include "ihm.h"
#include <QApplication>

/**
 * @file main.cpp
 * @brief Programme principal
 * @details Crée et affiche la fenêtre principale de l'application Pikawa
 * @author Anthony BRYCKAERT
 * @version 1.1
 *
 * @param argc
 * @param argv[]
 * @return int
 *
 */

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QFile file(":/qss/pikawa.qss");
    if(file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);
    }

    IHMPikawa fenetrePikawa;

    return a.exec();
}

/**
 * @class QObject
 * @brief Classe mère de toutes les classes Qt
 */

/**
 * @class QMainWindow
 * @brief Classe permettant de créer des applications GUI
 */
