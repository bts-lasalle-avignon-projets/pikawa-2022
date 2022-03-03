#include "ImageBouton.h"
#include <QDebug>

ImageBouton::ImageBouton(QWidget* parent /*= 0*/) : QLabel(parent)
{
}

ImageBouton::ImageBouton(QString imageSource, QWidget* parent /*= 0*/) :
    QLabel(parent), imageSource(imageSource)
{
    setPixmap(QPixmap(imageSource));
}

void ImageBouton::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
}

void ImageBouton::mouseDoubleClickEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit doubleClicked();
    }
}
