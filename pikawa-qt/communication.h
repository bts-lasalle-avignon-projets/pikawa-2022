#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QBluetoothDeviceInfo>

class Communication : public QObject
{
    Q_OBJECT
  private:
    bool active;
    bool connecte;

  public:
    Communication(QObject* parent = nullptr);
    ~Communication();

  public slots:
    void activerLaDecouverte();
    void decouvrirCafetiere(const QBluetoothDeviceInfo& esp);
};

#endif // COMMUNICATION_H
