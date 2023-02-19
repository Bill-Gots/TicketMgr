#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include <QPushButton>
#include <QLineEdit>

class push_button_login: public QPushButton
{
    Q_OBJECT

signals:
    void login_success();
    void login_failed();

public:
    QLineEdit* user, * password, * sql_name, * port;

    push_button_login(QLineEdit* text_user, QLineEdit* text_password, QLineEdit* text_sql_name, QLineEdit* text_port,
                      const QString text = "", QWidget* parent = Q_NULLPTR);


public slots:
    void login();
};

class push_button_search_user: public QPushButton
{
    Q_OBJECT

signals:

public:

    push_button_search_user(const QString text = "", QWidget* parent = Q_NULLPTR);


public slots:

};

class push_button_switch_search_user: public QPushButton
{
    Q_OBJECT

signals:

public:

    push_button_switch_search_user(QWidget* parent = Q_NULLPTR);


public slots:

};

class push_button_add_user: public QPushButton
{
    Q_OBJECT

signals:

public:

    push_button_add_user(const QString text = "", QWidget* parent = Q_NULLPTR);


public slots:

};

class push_button_edit_user: public QPushButton
{
    Q_OBJECT

signals:

public:

    push_button_edit_user(const QString text = "", QWidget* parent = Q_NULLPTR);


public slots:

};

class push_button_del_user: public QPushButton
{
    Q_OBJECT

signals:

public:

    push_button_del_user(const QString text = "", QWidget* parent = Q_NULLPTR);


public slots:

};

class push_button_back: public QPushButton
{
    Q_OBJECT

signals:

public:

    push_button_back(const QString text = "", QWidget* parent = Q_NULLPTR);


public slots:

};

#endif // PUSH_BUTTON_H
