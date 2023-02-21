#include <pages.h>

const QString str_discount_type[4] = {"成人", "儿童","学生", "残军"};

void page_user::create_page()
{
    list_user = create_tree_widget_user(w);
    label_instruct_search = create_label_instruct_search(w);
    text_search = create_text_search(w);
    button_search_user = create_button_search_user(w);
    button_switch_search_user = create_button_switch_search_user(w);
    button_back_user = create_button_back(w);
    button_add_user = create_button_add_user(w);
    button_edit_user = create_button_edit_user(w);
    button_del_user = create_button_del_user(w);
    label_total_user = create_label_total_user(w);
    window_add_user = create_window_add_user(list_user, label_total_user);
    window_edit_user = create_window_edit_user(list_user);
    QObject::connect(list_user, tree_widget_user::itemClicked, button_edit_user, push_button_edit_user::set_enabled);
    QObject::connect(list_user, tree_widget_user::itemClicked, button_del_user, push_button_del_user::set_enabled);
}

void page_user::create_list_widget(Customer* head)
{
    Customer* t = head;
    QStringList data;
    while(t->next != NULL)
    {
        t = t->next;
        data << t->name << t->id << t->username << t->password << t->telephone << str_discount_type[t->discount_type];
        QTreeWidgetItem* new_item = new QTreeWidgetItem(list_user, data);
        list_user->addTopLevelItem(new_item);
        func_set_alignment_and_width(list_user, new_item);
        data.clear();

        load_progress_bar->setValue(load_progress_bar->value() + 1);
        double progress = double(load_progress_bar->value() - load_progress_bar->minimum()) * 100 / double(load_progress_bar->maximum() - load_progress_bar->minimum());
        load_progress_bar->setFormat("车次信息加载中……" + QString::number(progress, 'f', 1) + "%");
    }
}


void page_user::func_switch_search_type()
{
    button_switch_search_user->search_type_group = new QActionGroup(button_switch_search_user);
    button_switch_search_user->search_type_group->setExclusive(true);

    QMenu* menu_search = new QMenu(button_search_user);
    button_switch_search_user->menu = menu_search;
    QAction** action_search = new QAction*[6];
    for(int i = 0; i < 6; i = i + 1)
    {
        action_search[i] = new QAction(menu_search);
        action_search[i]->setText(search_type_user[i]);
        action_search[i]->setCheckable(true);
        menu_search->addAction(action_search[i]);
        button_switch_search_user->search_type_group->addAction(action_search[i]);
    }
    button_switch_search_user->setMenu(menu_search);
    button_search_user->action_search = action_search;

    button_search_user->search_type_group = button_switch_search_user->search_type_group;
    QObject::connect(button_switch_search_user->search_type_group, &QActionGroup::triggered, button_search_user, &push_button_search_user::change_text);
    action_search[0]->trigger();
}

void page_user::func_open_window_add_and_edit_user()
{
    QObject::connect(button_add_user, &push_button_add_user::clicked, window_add_user, &widget_add_user::show);
    QObject::connect(button_edit_user, &push_button_edit_user::clicked, window_edit_user, &widget_edit_user::show);
    QObject::connect(button_edit_user, &push_button_edit_user::clicked, window_edit_user, &widget_edit_user::show_info);
}

void page_user::show()
{
    list_user->show();
    label_instruct_search->show();
    text_search->show();
    button_search_user->show();
    button_switch_search_user->show();
    button_back_user->show();
    button_add_user->show();
    button_edit_user->show();
    button_del_user->show();
    label_total_user->show();
}

void page_user::set_hidden()
{
    list_user->setHidden(true);
    label_instruct_search->setHidden(true);
    text_search->setHidden(true);
    button_search_user->setHidden(true);
    button_switch_search_user->setHidden(true);
    button_back_user->setHidden(true);
    button_add_user->setHidden(true);
    button_edit_user->setHidden(true);
    button_del_user->setHidden(true);
    label_total_user->setHidden(true);
}

void page_user::func_del_user()
{
    QMessageBox* box_del_user = new QMessageBox;
    box_del_user->setWindowTitle("删除用户");
    box_del_user->setText("确认删除该用户信息吗？");
    box_del_user->addButton("确定", QMessageBox::AcceptRole);
    box_del_user->addButton("取消", QMessageBox::RejectRole);
    box_del_user->setFont(QFont("Microsoft YaHei UI", 10));
    box_del_user->setWindowIcon(QIcon(":/ico/PTM.ico"));
    box_del_user->setIcon(QMessageBox::Question);
    box_del_user->setWindowModality(Qt::ApplicationModal);

    QObject::connect(button_del_user, &push_button_del_user::clicked, box_del_user, &QMessageBox::show);

    list_user->confirm_del_user = box_del_user->buttons().first();
    QObject::connect(box_del_user, &QMessageBox::buttonClicked, list_user, &tree_widget_user::del_user);

    QMessageBox* box_del_success = new QMessageBox;
    box_del_success->setWindowTitle("删除成功");
    box_del_success->setText("删除用户信息成功。");
    box_del_success->addButton("确定", QMessageBox::AcceptRole);
    box_del_success->setFont(QFont("Microsoft YaHei UI", 10));
    box_del_success->setWindowIcon(QIcon(":/ico/PTM.ico"));
    box_del_success->setIcon(QMessageBox::Information);
    box_del_success->setWindowModality(Qt::ApplicationModal);
    QObject::connect(list_user, &tree_widget_user::del_success, box_del_success, &QMessageBox::show);
    QObject::connect(list_user, &tree_widget_user::del_success, button_edit_user, &push_button_edit_user::set_disabled);
    QObject::connect(list_user, &tree_widget_user::del_success, label_total_user, &label_total::minus_total);
    QObject::connect(label_total_user, &label_total::no_data, button_del_user, &push_button_del_user::set_disabled);
}

void page_user::search_user()
{
    QString search_type;
    for(int i = 0; i < 6; i++)
    {
        if(button_search_user->search_type_group->checkedAction() == button_search_user->action_search[i])
        {
            //search_type = list_user->headerDaa;
        }
    }

    QString seach_text = text_search->text();
}
