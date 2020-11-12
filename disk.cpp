#include "disk.h"

Disk::Disk(const QColor &color)
{
    this->setShape(QCPScatterStyle::ssDisc);
    this->setPen(QPen(color));
    this->setBrush(Qt::white);
    this->setSize(10);
}
