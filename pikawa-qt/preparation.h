#ifndef PREPARATION_H
#define PREPARATION_H

#include <QVector>

class Cafetiere;

class Preparation
{
  private:
    Cafetiere* cafetere;

    QVector<QString> nomCapsules;
    QVector<QString> nomBoissons;
    bool             capsulePresente;
    bool             tassePresente;

  public:
    Cafetiere* getCafetiere();
    void       setCafetiere(Cafetiere* cafetiere);

    Preparation();

    void chercherCafetiere();
};

#endif // PREPARATION_H
