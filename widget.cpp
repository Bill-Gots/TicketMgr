#include "widget.h"
#include "ui_main_widget.h"

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
