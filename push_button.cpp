#include "push_button.h"

push_button_login::push_button_login(QLineEdit* text_user, QLineEdit* text_password, QLineEdit* text_sql_name, QLineEdit* text_port,
                                     const QString text, QWidget* parent): QPushButton(text, parent)
{
    user = text_user;
    password = text_password;
    sql_name = text_sql_name;
    port = text_port;
}

void push_button_login::login()
{
    emit login_success();
}
