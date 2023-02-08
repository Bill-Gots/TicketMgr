#include <QTime>
#include <QDateTime>


class Ticket
{
public:
    QString no, departure, destination;
    int day, price;
    QTime time_leave, time_arrive;
};

class Order:public Ticket
{
public:
    QString order, name, id;
    QDate day_leave;
    QDateTime time;
    int num;
};

class Customer
{
public:
    QString name, id, username, password, telephone;
    int discount_type;
    Order* orders;
};
