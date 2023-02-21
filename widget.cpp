#include "widget.h"
#include "ui_main_widget.h"
#include "tree_widget.h"
#include "utils.h"

const QString str_discount_type[4] = {"成人", "儿童","学生", "残军"};

main_widget::main_widget(QWidget *parent): QWidget(parent), ui(new Ui::main_widget)
{
    ui->setupUi(this);
}

main_widget::~main_widget()
{
    delete ui;
}

void main_widget::confirm_exit(QAbstractButton* clicked_button)
{
    if(clicked_button == button_confirm_exit)
    {
        this->close();
    }
}

login_widget::login_widget(QWidget *parent): QWidget(parent)
{

}

login_widget::~login_widget()
{

}

widget_add_user::widget_add_user(QWidget *parent): QWidget(parent)
{

}

widget_add_user::~widget_add_user()
{

}

void widget_add_user::add_user()
{
    for(int i = 0; i < 6; i++)
    {
        if(texts_input[i]->text().isEmpty())
        {
            emit empty_input();
            return;
        }
    }
    Customer* new_user = new Customer;
    new_user->name = texts_input[0]->text();
    new_user->id = texts_input[1]->text();
    new_user->username = texts_input[2]->text();
    new_user->password = texts_input[3]->text();
    new_user->telephone = texts_input[4]->text();
    for (int i = 0;i < 4; i++)
    {
        if(texts_input[5]->text() == str_discount_type[i])
        {
            new_user->discount_type = i;
        }
    }

    QStringList data;
    data << new_user->name << new_user->id << new_user->username << new_user->password << new_user->telephone << str_discount_type[new_user->discount_type];
    QTreeWidgetItem* new_item = new QTreeWidgetItem(list_user, data);
    list_user->addTopLevelItem(new_item);
    func_set_alignment_and_width(list_user, new_item);
    emit add_success();
}

widget_edit_user::widget_edit_user(QWidget *parent): QWidget(parent)
{

}

widget_edit_user::~widget_edit_user()
{

}

void widget_edit_user::show_info()
{
    for (int i = 0; i < 6; i++)
    {
        texts_input[i]->setText(list_user->selectedItems().first()->text(i));
    }
}

void widget_edit_user::edit_user()
{
    for(int i = 0; i < 6; i++)
    {
        if(texts_input[i]->text().isEmpty())
        {
            emit empty_input();
            return;
        }
    }
    Customer* new_user = new Customer;
    new_user->name = texts_input[0]->text();
    new_user->id = texts_input[1]->text();
    new_user->username = texts_input[2]->text();
    new_user->password = texts_input[3]->text();
    new_user->telephone = texts_input[4]->text();
    for(int i = 0; i < 4; i++)
    {
        if(texts_input[5]->text() == str_discount_type[i])
        {
            new_user->discount_type = i;
        }
    }

    for(int i = 0; i < 6; i++)
    {
        list_user->selectedItems().first()->setText(i, texts_input[i]->text());
    }

    emit edit_success();
}

