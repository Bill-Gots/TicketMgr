#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QDateTime>

class label_system_time:public QLabel
{
public:
    Q_OBJECT

public:
    label_system_time(QWidget* parent = Q_NULLPTR);


public slots:
    void update_time();
};

class label_total:public QLabel
{
public:
    Q_OBJECT

public:
    int total = 0;
    QString usage;

    label_total(const QString text, const QString u, QWidget* parent = Q_NULLPTR);


public slots:
    void update_total(int t);
};

#endif // LABEL_H
