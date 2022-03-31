#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QBluetoothDeviceDiscoveryAgent>

class Communication : public QObject
{
  private:
    bool active;
    bool connecte;

  public:
    Communication();
    ~Communication();

    void activerLaDecouverte();

  public slots:
    void estESPDecourverts(const QBluetoothDeviceInfo& esp);
};

#endif // COMMUNICATION_H
