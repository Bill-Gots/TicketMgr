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

const QString instruct_search = "在输入框内输入待查询的内容，点击查询按钮即可查询信息。依次单击表头可以设置内容的升序和降序排列。 点击下拉菜单可以更改查询信息的类别。";
class label_instruct:public QLabel
{
public:
    Q_OBJECT

public:
    label_instruct(const QString text, QWidget* parent = Q_NULLPTR);


public slots:
    void back();
};

class label_total:public QLabel
{
    Q_OBJECT

signals:
    void no_data();

public:
    int total = 0;
    QString usage;

    label_total(const QString text, const QString u, QWidget* parent = Q_NULLPTR);


public slots:
    void update_total(int t);
    void add_total();
    void minus_total();
};

#endif // LABEL_H
