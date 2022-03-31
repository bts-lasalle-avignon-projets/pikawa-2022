#ifndef PREPARATION_H
#define PREPARATION_H

#include <QVector>
#include <QString>

class Preparation
{
  private:
    QVector<QString> nomCapsules;
    QVector<QString> nomBoissons;
    bool             capsulePresente;
    bool             tassePresente;

  public:
    Preparation();
    ~Preparation();

    void chercherESP();
};

#endif // PREPARATION_H
