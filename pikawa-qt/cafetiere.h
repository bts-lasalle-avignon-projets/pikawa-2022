#ifndef PIKAWA_H
#define PIKAWA_H

#include <QVector>

class IHMPikawa;

class Cafetiere
{
  private:
    IHMPikawa* ihm;

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

    IHMPikawa* getIHMPikaw();
    void       setIHMPikawa(IHMPikawa ihm);
};

#endif // PIKAWA_H
