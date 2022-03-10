#ifndef IHM_H
#define IHM_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ihm; }
QT_END_NAMESPACE

class ihm : public QMainWindow
{
    Q_OBJECT

public:
    ihm(QWidget *parent = nullptr);
    ~ihm();

private:
    Ui::ihm *ui;
};
#endif // IHM_H
