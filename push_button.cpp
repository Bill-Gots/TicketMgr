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

push_button_search_user::push_button_search_user(const QString text, QWidget* parent): QPushButton(text, parent)
{

}

void push_button_search_user::change_text()
{
    this->setText(search_type_group->checkedAction()->text());
}

push_button_switch_search_user::push_button_switch_search_user(QWidget* parent): QPushButton(parent)
{

}

push_button_add_user::push_button_add_user(const QString text, QWidget* parent): QPushButton(text, parent)
{

}

void push_button_add_user::set_enabled()
{
    this->QPushButton::setEnabled(true);
}

void push_button_add_user::set_disabled()
{
    this->QPushButton::setDisabled(true);
}

push_button_edit_user::push_button_edit_user(const QString text, QWidget* parent): QPushButton(text, parent)
{

}

void push_button_edit_user::set_enabled()
{
    this->QPushButton::setEnabled(true);
}

void push_button_edit_user::set_disabled()
{
    this->QPushButton::setDisabled(true);
}

push_button_del_user::push_button_del_user(const QString text, QWidget* parent): QPushButton(text, parent)
{

}

void push_button_del_user::set_enabled()
{
    this->QPushButton::setEnabled(true);
}

void push_button_del_user::set_disabled()
{
    this->QPushButton::setDisabled(true);
}

push_button_search_ticket::push_button_search_ticket(const QString text, QWidget* parent): QPushButton(text, parent)
{

}

void push_button_search_ticket::change_text()
{
    this->setText(search_type_group->checkedAction()->text());
}

push_button_switch_search_ticket::push_button_switch_search_ticket(QWidget* parent): QPushButton(parent)
{

}

push_button_add_ticket::push_button_add_ticket(const QString text, QWidget* parent): QPushButton(text, parent)
{

}

void push_button_add_ticket::set_enabled()
{
    this->QPushButton::setEnabled(true);
}

void push_button_add_ticket::set_disabled()
{
    this->QPushButton::setDisabled(true);
}

push_button_edit_ticket::push_button_edit_ticket(const QString text, QWidget* parent): QPushButton(text, parent)
{

}

void push_button_edit_ticket::set_enabled()
{
    this->QPushButton::setEnabled(true);
}

void push_button_edit_ticket::set_disabled()
{
    this->QPushButton::setDisabled(true);
}

push_button_del_ticket::push_button_del_ticket(const QString text, QWidget* parent): QPushButton(text, parent)
{

}

void push_button_del_ticket::set_enabled()
{
    this->QPushButton::setEnabled(true);
}

void push_button_del_ticket::set_disabled()
{
    this->QPushButton::setDisabled(true);
}

push_button_search_order::push_button_search_order(const QString text, QWidget* parent): QPushButton(text, parent)
{

}

void push_button_search_order::change_text()
{
    this->setText(search_type_group->checkedAction()->text());
}

push_button_switch_search_order::push_button_switch_search_order(QWidget* parent): QPushButton(parent)
{

}

push_button_add_order::push_button_add_order(const QString text, QWidget* parent): QPushButton(text, parent)
{

}

void push_button_add_order::set_enabled()
{
    this->QPushButton::setEnabled(true);
}

void push_button_add_order::set_disabled()
{
    this->QPushButton::setDisabled(true);
}

push_button_edit_order::push_button_edit_order(const QString text, QWidget* parent): QPushButton(text, parent)
{

}

void push_button_edit_order::set_enabled()
{
    this->QPushButton::setEnabled(true);
}

void push_button_edit_order::set_disabled()
{
    this->QPushButton::setDisabled(true);
}

push_button_del_order::push_button_del_order(const QString text, QWidget* parent): QPushButton(text, parent)
{

}

void push_button_del_order::set_enabled()
{
    this->QPushButton::setEnabled(true);
}

void push_button_del_order::set_disabled()
{
    this->QPushButton::setDisabled(true);
}


push_button_back::push_button_back(const QString text, QWidget* parent): QPushButton(text, parent)
{

}
