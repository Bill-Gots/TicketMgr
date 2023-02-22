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
    QAction** action_search;

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
    void set_enabled();
    void set_disabled();

};

class push_button_edit_user: public QPushButton
{
    Q_OBJECT

signals:

public:

    push_button_edit_user(const QString text = "", QWidget* parent = Q_NULLPTR);


public slots:
    void set_enabled();
    void set_disabled();

};

class push_button_del_user: public QPushButton
{
    Q_OBJECT

signals:

public:

    push_button_del_user(const QString text = "", QWidget* parent = Q_NULLPTR);


public slots:
    void set_enabled();
    void set_disabled();

};

const QString search_type_ticket[7] = {"查询车次", "查询始发站", "查询终点站", "查询始发时间", "查询终到时间", "查询天数", "查询票价"};
class push_button_search_ticket: public QPushButton
{
    Q_OBJECT

signals:

public:
    QActionGroup* search_type_group;
    QAction** action_search;

    push_button_search_ticket(const QString text = "", QWidget* parent = Q_NULLPTR);

public slots:
    void change_text();

};

class push_button_switch_search_ticket: public QPushButton
{
    Q_OBJECT

signals:

public:
    QActionGroup* search_type_group;
    QMenu* menu;

    push_button_switch_search_ticket(QWidget* parent = Q_NULLPTR);

public slots:

};

class push_button_add_ticket: public QPushButton
{
    Q_OBJECT

signals:

public:

    push_button_add_ticket(const QString text = "", QWidget* parent = Q_NULLPTR);

public slots:
    void set_enabled();
    void set_disabled();

};

class push_button_edit_ticket: public QPushButton
{
    Q_OBJECT

signals:

public:

    push_button_edit_ticket(const QString text = "", QWidget* parent = Q_NULLPTR);


public slots:
    void set_enabled();
    void set_disabled();

};

class push_button_del_ticket: public QPushButton
{
    Q_OBJECT

signals:

public:

    push_button_del_ticket(const QString text = "", QWidget* parent = Q_NULLPTR);

public slots:
    void set_enabled();
    void set_disabled();

};

const QString search_type_order[7] = {"查询订单编号", "查询姓名", "查询身份证号码", "查询车次", "查询发车时间", "查询订票时间", "查询订票数量"};
class push_button_search_order: public QPushButton
{
    Q_OBJECT

signals:

public:
    QActionGroup* search_type_group;
    QAction** action_search;

    push_button_search_order(const QString text = "", QWidget* parent = Q_NULLPTR);

public slots:
    void change_text();

};

class push_button_switch_search_order: public QPushButton
{
    Q_OBJECT

signals:

public:
    QActionGroup* search_type_group;
    QMenu* menu;

    push_button_switch_search_order(QWidget* parent = Q_NULLPTR);

public slots:

};

class push_button_add_order: public QPushButton
{
    Q_OBJECT

signals:

public:
    push_button_add_order(const QString text = "", QWidget* parent = Q_NULLPTR);

public slots:
    void set_enabled();
    void set_disabled();

};

class push_button_edit_order: public QPushButton
{
    Q_OBJECT

signals:

public:
    push_button_edit_order(const QString text = "", QWidget* parent = Q_NULLPTR);

public slots:
    void set_enabled();
    void set_disabled();

};

class push_button_del_order: public QPushButton
{
    Q_OBJECT

signals:

public:
    push_button_del_order(const QString text = "", QWidget* parent = Q_NULLPTR);

public slots:
    void set_enabled();
    void set_disabled();

};



class push_button_back: public QPushButton
{
    Q_OBJECT

public:

    push_button_back(const QString text = "", QWidget* parent = Q_NULLPTR);


public slots:

};

#endif // PUSH_BUTTON_H
