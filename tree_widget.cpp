#include <tree_widget.h>

tree_widget_user::tree_widget_user(QWidget* parent): QTreeWidget(parent)
{

}

void tree_widget_user::del_user()
{
    this->takeTopLevelItem(this->indexOfTopLevelItem(this->selectedItems().first()));
    emit del_success();
}

