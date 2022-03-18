#include "ihm.h"
#include <QApplication>

/**
 * @file main.cpp
 * @brief Programme principal
 * @details Crée et affiche la fenêtre principale de l'application Pikawa
 * @author
 * @version 1.0
 *
 * @param argc
 * @param argv[]
 * @return int
 *
 */

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  IHMPikawa w;

  w.show();

  return a.exec();
}
