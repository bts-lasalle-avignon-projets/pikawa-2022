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
    Cafetiere();
    ~Cafetiere();

    IHMPikawa* getIHMPikaw();
    void       setIHMPikawa(IHMPikawa* ihm);

    Communication* getCommunication();
    void           setCommunication(Communication* communication);

    Preparation* getPreparation();
    void         setPreparation(Preparation* preparation);
    void         activerLaDecouverte();
};

#endif // CAFETIERE_H
