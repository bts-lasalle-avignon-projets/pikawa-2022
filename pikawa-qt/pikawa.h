#ifndef PIKAWA_H
#define PIKAWA_H
#include <QVector>

using namespace std;

class Pikawa
{
  private:
    QVector<string> nomCapsules;
    QVector<string> nomBoissons;
    int             capsuleChoisie;
    int             boissonChoisie;
    int             niveauEau;
    bool            connectee;
    bool            activee;
    bool            capsulePresente;
    bool            tassePresente;

  public:
    Pikawa();
};

#endif // PIKAWA_H
