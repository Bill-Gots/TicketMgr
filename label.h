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

#endif // LABEL_H
