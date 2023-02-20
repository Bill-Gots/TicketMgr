#include "label.h"

label_system_time::label_system_time(QWidget* parent): QLabel(parent)
{

}

void label_system_time::update_time()
{
    this->setText(QDateTime::currentDateTime().toString("系统时间：yyyy年M月d日 dddd  HH:mm:ss"));
}

label_total::label_total(const QString text, const QString u, QWidget* parent): QLabel(text, parent)
{
    usage = u;
}

void label_total::update_total(int t)
{
    this->setText("现有" + usage + "信息总数：" + QString::number(t));
}

void label_total::add_total()
{
    total++;
    this->setText("现有" + usage + "信息总数：" + QString::number(total));
}
