#ifndef THREADAVANCEMENTCAFE_H
#define THREADAVANCEMENTCAFE_H

#include <QThread>
#include <QObject>

class IHMPikawa;

class threadAvancementCafe : public QObject
{
    Q_OBJECT
public:
     threadAvancementCafe(QObject *parent = nullptr);
     void run(); // le code du thread
private:
     IHMPikawa* ihm;

signals:

};

#endif // THREADAVANCEMENTCAFE_H
