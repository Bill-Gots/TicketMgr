#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include <QPushButton>
#include <QLineEdit>
#include <QActionGroup>

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

const QString search_type_user[6] = {"查询姓名", "查询身份证", "查询用户名", "查询密码", "查询联系电话", "查询优惠类型"};
class push_button_search_user: public QPushButton
{
    Q_OBJECT

signals:

public:
    QActionGroup* search_type_group;

    push_button_search_user(const QString text = "", QWidget* parent = Q_NULLPTR);

public slots:
    void change_text();

};

class push_button_switch_search_user: public QPushButton
{
    Q_OBJECT

signals:

public:
    QActionGroup* search_type_group;
    QMenu* menu;

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
