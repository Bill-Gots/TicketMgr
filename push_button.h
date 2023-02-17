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



#endif // PUSH_BUTTON_H
