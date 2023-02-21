#ifndef DT_H
#define DT_H
#include <QDateTime>

class Ticket
{
public:
    QString no, departure, destination;
    int day, price;
    QTime time_leave, time_arrive;
    Ticket *next;
};

class Order:public Ticket
{
public:
    QString no, name, id;
    QDate day_leave;
    QDateTime time;
    int num;
    Order *next;
};

class Customer
{
public:
    QString name, id, username, password, telephone;
    int discount_type;
    Order* orders;
    Customer *next;
};

#endif // DT_H
