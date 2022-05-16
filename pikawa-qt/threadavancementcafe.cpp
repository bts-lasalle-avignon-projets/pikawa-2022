#include "threadavancementcafe.h"

threadAvancementCafe::threadAvancementCafe(QObject *parent) : QObject(parent), ihm(ihm)
{

}

void threadAvancementCafe::run()
{
    for(int i = 0; i <= 99; ++i)
    {
        IHMPikawa::ui->avancementPreparation->setValue(i+1);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}


