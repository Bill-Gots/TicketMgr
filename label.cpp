#include "label.h"

label_system_time::label_system_time(QWidget* parent): QLabel(parent)
{

}

void label_system_time::update_time()
{
    this->setText(QDateTime::currentDateTime().toString("系统时间：yyyy年M月d日 dddd  HH:mm:ss"));
}
