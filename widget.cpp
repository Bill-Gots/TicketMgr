#include "widget.h"
#include "ui_main_widget.h"
#include "tree_widget.h"
#include "pages.h"
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
    for(int i = 0; i < 6; i++)
    {
        data << texts_input[i]->text();
    }
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

widget_add_ticket::widget_add_ticket(QWidget *parent): QWidget(parent)
{

}

widget_add_ticket::~widget_add_ticket()
{

}

void widget_add_ticket::add_ticket()
{
    for(int i = 0; i < 7; i++)
    {
        if(texts_input[i]->text().isEmpty())
        {
            emit empty_input();
            return;
        }
    }
    Ticket* new_ticket = new Ticket;
    new_ticket->no = texts_input[0]->text();
    new_ticket->departure = texts_input[1]->text();
    new_ticket->destination = texts_input[2]->text();
    new_ticket->day = texts_input[3]->text().toInt();
    new_ticket->price = texts_input[4]->text().toInt();
    new_ticket->time_leave = QTime::fromString(texts_input[5]->text(), "HH:MM");
    new_ticket->time_arrive = QTime::fromString(texts_input[5]->text(), "HH:MM");

    QStringList data;
    for(int i = 0; i < 7; i++)
    {
        data << texts_input[i]->text();
    }
    QTreeWidgetItem* new_item = new QTreeWidgetItem(list_ticket, data);
    list_ticket->addTopLevelItem(new_item);
    func_set_alignment_and_width(list_ticket, new_item);
    emit add_success();
}

widget_edit_ticket::widget_edit_ticket(QWidget *parent): QWidget(parent)
{

}

widget_edit_ticket::~widget_edit_ticket()
{

}

void widget_edit_ticket::show_info()
{
    for (int i = 0; i < 7; i++)
    {
        texts_input[i]->setText(list_ticket->selectedItems().first()->text(i));
    }
}

void widget_edit_ticket::edit_ticket()
{
    for(int i = 0; i < 7; i++)
    {
        if(texts_input[i]->text().isEmpty())
        {
            emit empty_input();
            return;
        }
    }
    Ticket* new_ticket = new Ticket;
    new_ticket->no = texts_input[0]->text();
    new_ticket->departure = texts_input[1]->text();
    new_ticket->destination = texts_input[2]->text();
    new_ticket->day = texts_input[3]->text().toInt();
    new_ticket->price = texts_input[4]->text().toInt();
    new_ticket->time_leave = QTime::fromString(texts_input[5]->text(), "HH:MM");
    new_ticket->time_arrive = QTime::fromString(texts_input[5]->text(), "HH:MM");

    for(int i = 0; i < 7; i++)
    {
        list_ticket->selectedItems().first()->setText(i, texts_input[i]->text());
    }

    emit edit_success();
}

widget_add_order::widget_add_order(QWidget *parent): QWidget(parent)
{

}

widget_add_order::~widget_add_order()
{

}

void widget_add_order::add_order()
{
    for(int i = 0; i < 7; i++)
    {
        if(texts_input[i]->text().isEmpty())
        {
            emit empty_input();
            return;
        }
    }
    Order* new_order = new Order;
    new_order->no = texts_input[0]->text();
    new_order->name = texts_input[1]->text();
    new_order->id = texts_input[2]->text();
    new_order->day_leave = QDate::fromString(texts_input[3]->text(), "YYYY-MM-DD");
    new_order->time = QDateTime::fromString(texts_input[4]->text(), "YYYY-MM-DD HH:MM:SS");
    new_order->num = texts_input[4]->text().toInt();

    QStringList data;
    for(int i = 0; i < 7; i++)
    {
        data << texts_input[i]->text();
    }
    QTreeWidgetItem* new_item = new QTreeWidgetItem(list_order, data);
    list_order->addTopLevelItem(new_item);
    func_set_alignment_and_width(list_order, new_item);
    emit add_success();
}

widget_edit_order::widget_edit_order(QWidget *parent): QWidget(parent)
{

}

widget_edit_order::~widget_edit_order()
{

}

void widget_edit_order::show_info()
{
    for (int i = 0; i < 7; i++)
    {
        texts_input[i]->setText(list_order->selectedItems().first()->text(i));
    }
}

void widget_edit_order::edit_order()
{
    for(int i = 0; i < 7; i++)
    {
        if(texts_input[i]->text().isEmpty())
        {
            emit empty_input();
            return;
        }
    }
    Order* new_order = new Order;
    new_order->no = texts_input[0]->text();
    new_order->name = texts_input[1]->text();
    new_order->id = texts_input[2]->text();
    new_order->day_leave = QDate::fromString(texts_input[3]->text(), "YYYY-MM-DD");
    new_order->time = QDateTime::fromString(texts_input[4]->text(), "YYYY-MM-DD HH:MM:SS");
    new_order->num = texts_input[4]->text().toInt();

    for(int i = 0; i < 7; i++)
    {
        list_order->selectedItems().first()->setText(i, texts_input[i]->text());
    }

    emit edit_success();
}


