#ifndef IMAGE_BOUTON_H
#define IMAGE_BOUTON_H

#include <QtWidgets>

class ImageBouton : public QLabel
{
    Q_OBJECT

  private:
    QString imageSource;

  public:
    ImageBouton(QWidget* parent = 0);
    ImageBouton(QString imageSource, QWidget* parent = 0);

    void mousePressEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);

  private slots:

  signals:
    void clicked();
    void doubleClicked();
};

#endif
