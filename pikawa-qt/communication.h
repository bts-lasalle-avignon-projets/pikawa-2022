#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QBluetoothDeviceDiscoveryAgent>

class Cafetiere;

class Communication : public QObject
{
  private:
    bool active;
    bool connecte;

    Cafetiere* cafetiere;

  public:
    Cafetiere* getCafetiere();
    void       setCafetiere(Cafetiere* cafetere);

    Communication();

    void chercherCafetiere();

  public slots:
    bool estCafetiereDecourverte(const QBluetoothDeviceInfo& device);
};

#endif // COMMUNICATION_H
