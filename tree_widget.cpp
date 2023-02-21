#include <tree_widget.h>

tree_widget_user::tree_widget_user(QWidget* parent): QTreeWidget(parent)
{

}

void tree_widget_user::del_user()
{
    this->takeTopLevelItem(this->indexOfTopLevelItem(this->selectedItems().first()));
    emit del_success();
}

tree_widget_ticket::tree_widget_ticket(QWidget* parent): QTreeWidget(parent)
{

}

void tree_widget_ticket::del_ticket()
{
    this->takeTopLevelItem(this->indexOfTopLevelItem(this->selectedItems().first()));
    emit del_success();
}

tree_widget_order::tree_widget_order(QWidget* parent): QTreeWidget(parent)
{

}

void tree_widget_order::del_order()
{
    this->takeTopLevelItem(this->indexOfTopLevelItem(this->selectedItems().first()));
    emit del_success();
}
