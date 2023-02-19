#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "line_edit.h"

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

public:
    QLabel** labels_input;
    line_edit_add** texts_input;

    widget_add_user(QWidget *parent = nullptr);
    ~widget_add_user();

};

class widget_edit_user: public QWidget
{
    Q_OBJECT

public:
    QLabel** labels_input;
    line_edit_edit** texts_input;

    widget_edit_user(QWidget *parent = nullptr);
    ~widget_edit_user();

};

#endif // WIDGET_H
