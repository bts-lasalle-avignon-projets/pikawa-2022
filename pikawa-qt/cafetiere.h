#ifndef PIKAWA_H
#define PIKAWA_H
#include <QVector>

class Cafetiere
{
  private:
    QVector<QString> nomCapsules;
    QVector<QString> nomBoissons;
    int              capsuleChoisie;
    int              boissonChoisie;
    int              niveauEau;
    bool             connectee;
    bool             activee;
    bool             capsulePresente;
    bool             tassePresente;

  public:
    Cafetiere();
};

#endif // PIKAWA_H
