#ifndef TREE_WIDGET_H
#define TREE_WIDGET_H

#include <QTreeWidget>
#include <QPushButton>

class tree_widget_user: public QTreeWidget
{
    Q_OBJECT

signals:
    void del_success();

public:
    QAbstractButton* confirm_del_user;
    tree_widget_user(QWidget* parent = Q_NULLPTR);

public slots:
    void del_user();
};

#endif // TREE_WIDGET_H
