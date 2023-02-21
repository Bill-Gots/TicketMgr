#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <dt.h>
#include "line_edit.h"
#include "tree_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class main_widget; class login_widget;}
QT_END_NAMESPACE

class main_widget: public QWidget
{
    Q_OBJECT

public:
    QAbstractButton* button_confirm_exit;

    main_widget(QWidget *parent = nullptr);
    ~main_widget();

public slots:
    void confirm_exit(QAbstractButton* clicked_button);

private:
    Ui::main_widget *ui;
};

class login_widget: public QWidget
{
    Q_OBJECT

public:
    login_widget(QWidget *parent = nullptr);
    ~login_widget();

};

class widget_add_user: public QWidget
{
    Q_OBJECT

signals:
    void empty_input();
    void add_success();

public:
    tree_widget_user* list_user;
    QLabel** labels_input;
    line_edit_add** texts_input;
    Customer* adding_user;

    widget_add_user(QWidget *parent = nullptr);
    ~widget_add_user();

public slots:
    void add_user();


};

class widget_edit_user: public QWidget
{
    Q_OBJECT
signals:
    void empty_input();
    void edit_success();

public:
    tree_widget_user* list_user;
    QLabel** labels_input;
    line_edit_edit** texts_input;
    Customer* adding_user;

    widget_edit_user(QWidget *parent = nullptr);
    ~widget_edit_user();

public slots:
    void show_info();
    void edit_user();
};

class widget_add_ticket: public QWidget
{
    Q_OBJECT

signals:
    void empty_input();
    void add_success();

public:
    tree_widget_ticket* list_ticket;
    QLabel** labels_input;
    line_edit_add** texts_input;
    Customer* adding_ticket;

    widget_add_ticket(QWidget *parent = nullptr);
    ~widget_add_ticket();

public slots:
    void add_ticket();


};

class widget_edit_ticket: public QWidget
{
    Q_OBJECT
signals:
    void empty_input();
    void edit_success();

public:
    tree_widget_ticket* list_ticket;
    QLabel** labels_input;
    line_edit_edit** texts_input;
    Customer* adding_ticket;

    widget_edit_ticket(QWidget *parent = nullptr);
    ~widget_edit_ticket();

public slots:
    void show_info();
    void edit_ticket();
};

class widget_add_order: public QWidget
{
    Q_OBJECT

signals:
    void empty_input();
    void add_success();

public:
    tree_widget_order* list_order;
    QLabel** labels_input;
    line_edit_add** texts_input;
    Customer* adding_order;

    widget_add_order(QWidget *parent = nullptr);
    ~widget_add_order();

public slots:
    void add_order();


};

class widget_edit_order: public QWidget
{
    Q_OBJECT
signals:
    void empty_input();
    void edit_success();

public:
    tree_widget_order* list_order;
    QLabel** labels_input;
    line_edit_edit** texts_input;
    Customer* adding_order;

    widget_edit_order(QWidget *parent = nullptr);
    ~widget_edit_order();

public slots:
    void show_info();
    void edit_order();
};


#endif // WIDGET_H
