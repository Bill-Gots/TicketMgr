#ifndef TREE_WIDGET_H
#define TREE_WIDGET_H

#include <QTreeWidget>

class tree_widget_user: public QTreeWidget
{
    Q_OBJECT

public:
    tree_widget_user(QWidget* parent = Q_NULLPTR);

};

#endif // TREE_WIDGET_H
