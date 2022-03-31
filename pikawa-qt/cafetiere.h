#ifndef CAFETIERE_H
#define CAFETIERE_H

#include <QVector>
#include <QObject>

class IHMPikawa;
class Communication;
class Preparation;

class Cafetiere : public QObject
{
    Q_OBJECT
  private:
    IHMPikawa*     ihm;
    Communication* communication;
    Preparation*   preparation;

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
    Cafetiere(IHMPikawa* ihm);
    virtual ~Cafetiere();

  public slots:
    void connecter();
};

#endif // CAFETIERE_H
