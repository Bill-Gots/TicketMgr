#include <pages.h>

const QString str_discount_type[4] = {"成人", "儿童","学生", "残军"};

void func_set_alignment_and_width(QTreeWidget* list, QTreeWidgetItem* item, int width)
{
    for(int i = 0; i <= list->columnCount(); i = i + 1)
    {
        item->setTextAlignment(i, Qt::AlignCenter);
        list->setColumnWidth(i, 215);
    }
}

tree_widget_user* page_user::create_tree_widget_user(main_widget* w)
{
    QStringList header_user;
    header_user << "姓名" << "身份证号码" << "用户名" << "密码" << "联系电话" << "优惠类型" << "";
    tree_widget_user* list_user = new tree_widget_user(w);
    list_user->resize(1567, 680);
    list_user->move(353, 298);
    list_user->setColumnCount(7);
    list_user->setHeaderLabels(header_user);
    list_user->setFont(QFont("Microsoft YaHei UI", 14));
    list_user->setUniformRowHeights(false);\
    list_user->header()->setDefaultAlignment(Qt::AlignCenter);
    list_user->setSortingEnabled(true);
    return list_user;
}

const QString instruct_search = "在输入框内输入待查询的内容，点击查询按钮即可查询信息。依次单击表头可以设置内容的升序和降序排列。 点击下拉菜单可以更改查询信息的类别。";

QLabel* page_user::create_label_instruct_search_user(main_widget* w)
{
    QLabel* label_instruct_search = new QLabel(instruct_search, w);
    label_instruct_search->resize(725, 100);
    label_instruct_search->move(520, 195);
    label_instruct_search->setText(instruct_search);
    label_instruct_search->setFont(QFont("Microsoft YaHei UI", 12));
    label_instruct_search->setWordWrap(true);
    return label_instruct_search;
}

line_edit_search* page_user::create_text_search_user(main_widget* w)
{
    line_edit_search* text_search = new line_edit_search("", w);
    text_search->resize(440, 60);
    text_search->move(1260, 215);
    text_search->setFont(QFont("Microsoft YaHei UI", 16));
    text_search->setClearButtonEnabled(true);
    text_search->setMaxLength(40);
    return text_search;
}

push_button_search_user* page_user::create_button_search_user(main_widget* w)
{
    push_button_search_user* button_search_user = new push_button_search_user("搜索", w);
    button_search_user->resize(170, 60);
    button_search_user->move(1710, 215);
    button_search_user->setIcon(QIcon(":/new/search/btnSearch.png"));
    button_search_user->setIconSize(QSize(25, 25));
    button_search_user->setFont(QFont("Microsoft YaHei UI", 12));
    return button_search_user;
}

push_button_switch_search_user* page_user::create_button_switch_search_user(main_widget* w)
{
    push_button_switch_search_user* button_switch_search_user = new push_button_switch_search_user(w);
    button_switch_search_user->resize(20, 60);
    button_switch_search_user->move(1880, 215);
    return button_switch_search_user;
}

push_button_back* page_user::create_button_back_user(main_widget* w)
{
    push_button_back* button_back_user = new push_button_back("返回", w);
    button_back_user->resize(120, 60);
    button_back_user->move(375, 215);
    button_back_user->setFont(QFont("Microsoft YaHei UI", 14));
    button_back_user->setIcon(QIcon(":/new/back/btnBack.png"));
    button_back_user->setIconSize(QSize(20, 20));
    button_back_user->setDisabled(true);
    return button_back_user;
}

const QFont font_button_bottom("Microsoft YaHei UI", 12);
push_button_add_user* page_user::create_button_add_user(main_widget* w)
{
    push_button_add_user* button_add_user = new push_button_add_user("添加用户信息", w);
    button_add_user->resize(150, 40);
    button_add_user->move(375, 985);
    button_add_user->setFont(font_button_bottom);
    return button_add_user;
}

push_button_edit_user* page_user::create_button_edit_user(main_widget* w)
{
    push_button_edit_user* button_edit_user = new push_button_edit_user("编辑用户信息", w);
    button_edit_user->resize(150, 40);
    button_edit_user->move(560, 985);
    button_edit_user->setFont(font_button_bottom);
    button_edit_user->set_disabled();
    return button_edit_user;
}

push_button_del_user* page_user::create_button_del_user(main_widget* w)
{
    push_button_del_user* button_del_user = new push_button_del_user("删除用户信息", w);
    button_del_user->resize(150, 40);
    button_del_user->move(745, 985);
    button_del_user->setFont(font_button_bottom);
    button_del_user->set_disabled();
    return button_del_user;
}

label_total* page_user::create_label_total_user(main_widget* w)
{
    label_total* label_total_user = new label_total("现有用户信息总数：", "用户", w);
    label_total_user->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label_total_user->resize(350, 40);
    label_total_user->move(1550, 985);
    label_total_user->setFont(QFont("Microsoft YaHei UI", 13));
    return label_total_user;
}

widget_add_user* page_user::create_window_add_user(tree_widget_user* list_user, label_total* total)
{
    widget_add_user* window_add_user = new widget_add_user();
    window_add_user->setFixedSize(810, 290);
    window_add_user->setWindowTitle("添加用户信息");
    window_add_user->setPalette(QPalette(Qt::white));
    window_add_user->setWindowIcon(QIcon(":/ico/PTM.ico"));
    window_add_user->setWindowModality(Qt::ApplicationModal);
    window_add_user->list_user = list_user;

    QLabel** labels = new QLabel*[6];
    line_edit_add** texts = new line_edit_add*[6];
    for(int i = 0; i < 6; i++)
    {
        labels[i] = new QLabel(window_add_user);
        labels[i]->resize(140, 45);
        labels[i]->move(10 + 400 * (i % 2), 30 + 60 * (i / 2));
        labels[i]->setText(list_user->headerItem()->text(i) + "：");
        labels[i]->setFont(QFont("Microsoft YaHei UI", 14));
        labels[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        texts[i] = new line_edit_add("", window_add_user);
        texts[i]->resize(230, 45);
        texts[i]->move(labels[i]->x() + labels[i]->width(), labels[i]->y());
        texts[i]->setFont(QFont("Microsoft YaHei UI", 12));
        texts[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        texts[i]->setMaxLength(30);
    }
    window_add_user->labels_input = (QLabel**) (labels);
    window_add_user->texts_input = (line_edit_add**) (texts);

    QPushButton* button_confirm_add = new QPushButton(window_add_user);
    button_confirm_add->resize(120, 50);
    button_confirm_add->move(470, 220);
    button_confirm_add->setText("确认");
    button_confirm_add->setFont(QFont("Microsoft YaHei UI", 16));

    QObject::connect(button_confirm_add, &QPushButton::clicked, window_add_user, &widget_add_user::add_user);

    QMessageBox* box_empty_input = new QMessageBox();
    box_empty_input->setWindowTitle("错误");
    box_empty_input->setText("有字段为空，请重新输入。");
    box_empty_input->addButton("确定", QMessageBox::AcceptRole);
    box_empty_input->setFont(QFont("Microsoft YaHei UI", 10));
    box_empty_input->setWindowIcon(QIcon(":/ico/PTM.ico"));
    box_empty_input->setIcon(QMessageBox::Critical);
    box_empty_input->setWindowModality(Qt::ApplicationModal);

    QObject::connect(window_add_user, &widget_add_user::empty_input, box_empty_input, &QMessageBox::show);

    QMessageBox* box_add_success = new QMessageBox();
    box_add_success->setWindowTitle("成功");
    box_add_success->setText("添加新用户信息成功。");
    box_add_success->addButton("确定", QMessageBox::AcceptRole);
    box_add_success->setFont(QFont("Microsoft YaHei UI", 10));
    box_add_success->setWindowIcon(QIcon(":/ico/PTM.ico"));
    box_add_success->setIcon(QMessageBox::Information);
    box_add_success->setWindowModality(Qt::ApplicationModal);
    QObject::connect(window_add_user, &widget_add_user::add_success, box_add_success, &QMessageBox::show);
    QObject::connect(window_add_user, &widget_add_user::add_success, window_add_user, &widget_add_user::close);
    QObject::connect(window_add_user, &widget_add_user::add_success, total, &label_total::add_total);
    for(int i = 0; i < 6; i++)
    {
        QObject::connect(window_add_user, &widget_add_user::add_success, texts[i], &line_edit_add::clear);
    }

    QPushButton* button_cancel_add = new QPushButton(window_add_user);
    button_cancel_add->resize(120, 50);
    button_cancel_add->move(630, 220);
    button_cancel_add->setText("取消");
    button_cancel_add->setFont(QFont("Microsoft YaHei UI", 16));

    QObject::connect(button_cancel_add, &QPushButton::clicked, window_add_user, &widget_add_user::close);

    window_add_user->setAttribute(Qt::WA_QuitOnClose, false);

    return window_add_user;
}

widget_edit_user* page_user::create_window_edit_user(tree_widget_user* list_user)
{
    widget_edit_user* window_edit_user = new widget_edit_user();
    window_edit_user->setWindowTitle("编辑用户信息");
    window_edit_user->setPalette(QPalette(Qt::white));
    window_edit_user->setWindowIcon(QIcon(":/ico/PTM.ico"));
    window_edit_user->setWindowModality(Qt::ApplicationModal);
    window_edit_user->list_user = list_user;

    QLabel** labels = new QLabel*[6];
    line_edit_edit** texts = new line_edit_edit*[6];
    for(int i = 0; i < 6; i++)
    {
        labels[i] = new QLabel(window_edit_user);
        labels[i]->resize(140, 45);
        labels[i]->move(10 + 400 * (i % 2), 30 + 60 * (i / 2));
        labels[i]->setText(list_user->headerItem()->text(i) + "：");
        labels[i]->setFont(QFont("Microsoft YaHei UI", 14));
        labels[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        texts[i] = new line_edit_edit("", window_edit_user);
        texts[i]->resize(230, 45);
        texts[i]->move(labels[i]->x() + labels[i]->width(), labels[i]->y());
        texts[i]->setFont(QFont("Microsoft YaHei UI", 12));
        texts[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        texts[i]->setMaxLength(30);
        texts[i]->show();
    }
    window_edit_user->labels_input = labels;
    window_edit_user->texts_input = texts;

    QPushButton* button_confirm_edit = new QPushButton(window_edit_user);
    button_confirm_edit->resize(120, 50);
    button_confirm_edit->move(470, 220);
    button_confirm_edit->setText("确认");
    button_confirm_edit->setFont(QFont("Microsoft YaHei UI", 16));

    QObject::connect(button_confirm_edit, &QPushButton::clicked, window_edit_user, &widget_edit_user::edit_user);

    QMessageBox* box_empty_input = new QMessageBox();
    box_empty_input->setWindowTitle("错误");
    box_empty_input->setText("有字段为空，请重新输入。");
    box_empty_input->addButton("确定", QMessageBox::AcceptRole);
    box_empty_input->setFont(QFont("Microsoft YaHei UI", 10));
    box_empty_input->setWindowIcon(QIcon(":/ico/PTM.ico"));
    box_empty_input->setIcon(QMessageBox::Critical);
    box_empty_input->setWindowModality(Qt::ApplicationModal);

    QObject::connect(window_edit_user, &widget_edit_user::empty_input, box_empty_input, &QMessageBox::show);

    QMessageBox* box_edit_success = new QMessageBox();
    box_edit_success->setWindowTitle("成功");
    box_edit_success->setText("编辑用户信息成功。");
    box_edit_success->addButton("确定", QMessageBox::AcceptRole);
    box_edit_success->setFont(QFont("Microsoft YaHei UI", 10));
    box_edit_success->setWindowIcon(QIcon(":/ico/PTM.ico"));
    box_edit_success->setIcon(QMessageBox::Information);
    box_edit_success->setWindowModality(Qt::ApplicationModal);
    QObject::connect(window_edit_user, &widget_edit_user::edit_success, box_edit_success, &QMessageBox::show);
    QObject::connect(window_edit_user, &widget_edit_user::edit_success, window_edit_user, &widget_edit_user::close);
    for(int i = 0; i < 6; i++)
    {
        QObject::connect(window_edit_user, &widget_edit_user::edit_success, texts[i], &line_edit_edit::clear);
    }

    QPushButton* button_cancel_edit = new QPushButton(window_edit_user);
    button_cancel_edit->resize(120, 50);
    button_cancel_edit->move(630, 220);
    button_cancel_edit->setText("取消");
    button_cancel_edit->setFont(QFont("Microsoft YaHei UI", 16));

    QObject::connect(button_cancel_edit, &QPushButton::clicked, window_edit_user, &widget_edit_user::close);

    window_edit_user->setAttribute(Qt::WA_QuitOnClose, false);

    return window_edit_user;
}

void page_user::create_page()
{
    list_user = create_tree_widget_user(w);
    label_instruct_search = create_label_instruct_search_user(w);
    text_search = create_text_search_user(w);
    button_search_user = create_button_search_user(w);
    button_switch_search_user = create_button_switch_search_user(w);
    button_back_user = create_button_back_user(w);
    button_add_user = create_button_add_user(w);
    button_edit_user = create_button_edit_user(w);
    button_del_user = create_button_del_user(w);
    label_total_user = create_label_total_user(w);
    window_add_user = create_window_add_user(list_user, label_total_user);
    window_edit_user = create_window_edit_user(list_user);
    QObject::connect(list_user, &tree_widget_user::itemClicked, button_edit_user, &push_button_edit_user::set_enabled);
    QObject::connect(list_user, &tree_widget_user::itemClicked, button_del_user, &push_button_del_user::set_enabled);
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
    const QString serach_type[6] = {"姓名", "身份证号码", "用户名", "密码", "联系电话", "优惠类型"};
    int t;
    for(int i = 0; i < 6; i++)
    {
        if(button_search_user->search_type_group->checkedAction() == button_search_user->action_search[i])
        {
            t = i;
        }
    }

    QString seach_text = text_search->text();
}

tree_widget_ticket* page_ticket::create_tree_widget_ticket(main_widget* w)
{
    QStringList header_ticket;
    header_ticket << "车次" << "始发站" << "终点站" << "始发时间" << "终到时间" << "天数" << "票价" << "";
    tree_widget_ticket* list_ticket = new tree_widget_ticket(w);
    list_ticket->resize(1567, 680);
    list_ticket->move(353, 298);
    list_ticket->setColumnCount(8);
    list_ticket->setHeaderLabels(header_ticket);
    list_ticket->setFont(QFont("Microsoft YaHei UI", 14));
    list_ticket->setUniformRowHeights(false);
    list_ticket->header()->setDefaultAlignment(Qt::AlignCenter);
    list_ticket->setSortingEnabled(true);
    return list_ticket;
}

QLabel* page_ticket::create_label_instruct_search_ticket(main_widget* w)
{
    QLabel* label_instruct_search = new QLabel(instruct_search, w);
    label_instruct_search->resize(725, 100);
    label_instruct_search->move(520, 195);
    label_instruct_search->setText(instruct_search);
    label_instruct_search->setFont(QFont("Microsoft YaHei UI", 12));
    label_instruct_search->setWordWrap(true);
    return label_instruct_search;
}

line_edit_search* page_ticket::create_text_search_ticket(main_widget* w)
{
    line_edit_search* text_search = new line_edit_search("", w);
    text_search->resize(440, 60);
    text_search->move(1260, 215);
    text_search->setFont(QFont("Microsoft YaHei UI", 16));
    text_search->setClearButtonEnabled(true);
    text_search->setMaxLength(40);
    return text_search;
}

push_button_search_ticket* page_ticket::create_button_search_ticket(main_widget* w)
{
    push_button_search_ticket* button_search_ticket = new push_button_search_ticket("搜索", w);
    button_search_ticket->resize(170, 60);
    button_search_ticket->move(1710, 215);
    button_search_ticket->setIcon(QIcon(":/new/search/btnSearch.png"));
    button_search_ticket->setIconSize(QSize(25, 25));
    button_search_ticket->setFont(QFont("Microsoft YaHei UI", 12));
    return button_search_ticket;
}

push_button_switch_search_ticket* page_ticket::create_button_switch_search_ticket(main_widget* w)
{
    push_button_switch_search_ticket* button_switch_search_ticket = new push_button_switch_search_ticket(w);
    button_switch_search_ticket->resize(20, 60);
    button_switch_search_ticket->move(1880, 215);
    return button_switch_search_ticket;
}

push_button_back* page_ticket::create_button_back_ticket(main_widget* w)
{
    push_button_back* button_back_ticket = new push_button_back("返回", w);
    button_back_ticket->resize(120, 60);
    button_back_ticket->move(375, 215);
    button_back_ticket->setFont(QFont("Microsoft YaHei UI", 14));
    button_back_ticket->setIcon(QIcon(":/new/back/btnBack.png"));
    button_back_ticket->setIconSize(QSize(20, 20));
    button_back_ticket->setDisabled(true);
    return button_back_ticket;
}

push_button_add_ticket* page_ticket::create_button_add_ticket(main_widget* w)
{
    push_button_add_ticket* button_add_ticket = new push_button_add_ticket("添加用户信息", w);
    button_add_ticket->resize(150, 40);
    button_add_ticket->move(375, 985);
    button_add_ticket->setFont(font_button_bottom);
    return button_add_ticket;
}

push_button_edit_ticket* page_ticket::create_button_edit_ticket(main_widget* w)
{
    push_button_edit_ticket* button_edit_ticket = new push_button_edit_ticket("编辑用户信息", w);
    button_edit_ticket->resize(150, 40);
    button_edit_ticket->move(560, 985);
    button_edit_ticket->setFont(font_button_bottom);
    button_edit_ticket->set_disabled();
    return button_edit_ticket;
}

push_button_del_ticket* page_ticket::create_button_del_ticket(main_widget* w)
{
    push_button_del_ticket* button_del_ticket = new push_button_del_ticket("删除用户信息", w);
    button_del_ticket->resize(150, 40);
    button_del_ticket->move(745, 985);
    button_del_ticket->setFont(font_button_bottom);
    button_del_ticket->set_disabled();
    return button_del_ticket;
}

label_total* page_ticket::create_label_total_ticket(main_widget* w)
{
    label_total* label_total_ticket = new label_total("现有用户信息总数：", "用户", w);
    label_total_ticket->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label_total_ticket->resize(350, 40);
    label_total_ticket->move(1550, 985);
    label_total_ticket->setFont(QFont("Microsoft YaHei UI", 13));
    return label_total_ticket;
}

widget_add_ticket* page_ticket::create_window_add_ticket(tree_widget_ticket* list_ticket, label_total* total)
{
    widget_add_ticket* window_add_ticket = new widget_add_ticket();
    window_add_ticket->setFixedSize(810, 290);
    window_add_ticket->setWindowTitle("添加用户信息");
    window_add_ticket->setPalette(QPalette(Qt::white));
    window_add_ticket->setWindowIcon(QIcon(":/ico/PTM.ico"));
    window_add_ticket->setWindowModality(Qt::ApplicationModal);
    window_add_ticket->list_ticket = list_ticket;

    QLabel** labels = new QLabel*[6];
    line_edit_add** texts = new line_edit_add*[6];
    for(int i = 0; i < 6; i++)
    {
        labels[i] = new QLabel(window_add_ticket);
        labels[i]->resize(140, 45);
        labels[i]->move(10 + 400 * (i % 2), 30 + 60 * (i / 2));
        labels[i]->setText(list_ticket->headerItem()->text(i) + "：");
        labels[i]->setFont(QFont("Microsoft YaHei UI", 14));
        labels[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        texts[i] = new line_edit_add("", window_add_ticket);
        texts[i]->resize(230, 45);
        texts[i]->move(labels[i]->x() + labels[i]->width(), labels[i]->y());
        texts[i]->setFont(QFont("Microsoft YaHei UI", 12));
        texts[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        texts[i]->setMaxLength(30);
    }
    window_add_ticket->labels_input = (QLabel**) (labels);
    window_add_ticket->texts_input = (line_edit_add**) (texts);

    QPushButton* button_confirm_add = new QPushButton(window_add_ticket);
    button_confirm_add->resize(120, 50);
    button_confirm_add->move(470, 220);
    button_confirm_add->setText("确认");
    button_confirm_add->setFont(QFont("Microsoft YaHei UI", 16));

    QObject::connect(button_confirm_add, &QPushButton::clicked, window_add_ticket, &widget_add_ticket::add_ticket);

    QMessageBox* box_empty_input = new QMessageBox();
    box_empty_input->setWindowTitle("错误");
    box_empty_input->setText("有字段为空，请重新输入。");
    box_empty_input->addButton("确定", QMessageBox::AcceptRole);
    box_empty_input->setFont(QFont("Microsoft YaHei UI", 10));
    box_empty_input->setWindowIcon(QIcon(":/ico/PTM.ico"));
    box_empty_input->setIcon(QMessageBox::Critical);
    box_empty_input->setWindowModality(Qt::ApplicationModal);

    QObject::connect(window_add_ticket, &widget_add_ticket::empty_input, box_empty_input, &QMessageBox::show);

    QMessageBox* box_add_success = new QMessageBox();
    box_add_success->setWindowTitle("成功");
    box_add_success->setText("添加新用户信息成功。");
    box_add_success->addButton("确定", QMessageBox::AcceptRole);
    box_add_success->setFont(QFont("Microsoft YaHei UI", 10));
    box_add_success->setWindowIcon(QIcon(":/ico/PTM.ico"));
    box_add_success->setIcon(QMessageBox::Information);
    box_add_success->setWindowModality(Qt::ApplicationModal);
    QObject::connect(window_add_ticket, &widget_add_ticket::add_success, box_add_success, &QMessageBox::show);
    QObject::connect(window_add_ticket, &widget_add_ticket::add_success, window_add_ticket, &widget_add_ticket::close);
    QObject::connect(window_add_ticket, &widget_add_ticket::add_success, total, &label_total::add_total);
    for(int i = 0; i < 6; i++)
    {
        QObject::connect(window_add_ticket, &widget_add_ticket::add_success, texts[i], &line_edit_add::clear);
    }

    QPushButton* button_cancel_add = new QPushButton(window_add_ticket);
    button_cancel_add->resize(120, 50);
    button_cancel_add->move(630, 220);
    button_cancel_add->setText("取消");
    button_cancel_add->setFont(QFont("Microsoft YaHei UI", 16));

    QObject::connect(button_cancel_add, &QPushButton::clicked, window_add_ticket, &widget_add_ticket::close);

    window_add_ticket->setAttribute(Qt::WA_QuitOnClose, false);

    return window_add_ticket;
}

widget_edit_ticket* page_ticket::create_window_edit_ticket(tree_widget_ticket* list_ticket)
{
    widget_edit_ticket* window_edit_ticket = new widget_edit_ticket();
    window_edit_ticket->setWindowTitle("编辑用户信息");
    window_edit_ticket->setPalette(QPalette(Qt::white));
    window_edit_ticket->setWindowIcon(QIcon(":/ico/PTM.ico"));
    window_edit_ticket->setWindowModality(Qt::ApplicationModal);
    window_edit_ticket->list_ticket = list_ticket;

    QLabel** labels = new QLabel*[6];
    line_edit_edit** texts = new line_edit_edit*[6];
    for(int i = 0; i < 6; i++)
    {
        labels[i] = new QLabel(window_edit_ticket);
        labels[i]->resize(140, 45);
        labels[i]->move(10 + 400 * (i % 2), 30 + 60 * (i / 2));
        labels[i]->setText(list_ticket->headerItem()->text(i) + "：");
        labels[i]->setFont(QFont("Microsoft YaHei UI", 14));
        labels[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        texts[i] = new line_edit_edit("", window_edit_ticket);
        texts[i]->resize(230, 45);
        texts[i]->move(labels[i]->x() + labels[i]->width(), labels[i]->y());
        texts[i]->setFont(QFont("Microsoft YaHei UI", 12));
        texts[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        texts[i]->setMaxLength(30);
        texts[i]->show();
    }
    window_edit_ticket->labels_input = labels;
    window_edit_ticket->texts_input = texts;

    QPushButton* button_confirm_edit = new QPushButton(window_edit_ticket);
    button_confirm_edit->resize(120, 50);
    button_confirm_edit->move(470, 220);
    button_confirm_edit->setText("确认");
    button_confirm_edit->setFont(QFont("Microsoft YaHei UI", 16));

    QObject::connect(button_confirm_edit, &QPushButton::clicked, window_edit_ticket, &widget_edit_ticket::edit_ticket);

    QMessageBox* box_empty_input = new QMessageBox();
    box_empty_input->setWindowTitle("错误");
    box_empty_input->setText("有字段为空，请重新输入。");
    box_empty_input->addButton("确定", QMessageBox::AcceptRole);
    box_empty_input->setFont(QFont("Microsoft YaHei UI", 10));
    box_empty_input->setWindowIcon(QIcon(":/ico/PTM.ico"));
    box_empty_input->setIcon(QMessageBox::Critical);
    box_empty_input->setWindowModality(Qt::ApplicationModal);

    QObject::connect(window_edit_ticket, &widget_edit_ticket::empty_input, box_empty_input, &QMessageBox::show);

    QMessageBox* box_edit_success = new QMessageBox();
    box_edit_success->setWindowTitle("成功");
    box_edit_success->setText("编辑用户信息成功。");
    box_edit_success->addButton("确定", QMessageBox::AcceptRole);
    box_edit_success->setFont(QFont("Microsoft YaHei UI", 10));
    box_edit_success->setWindowIcon(QIcon(":/ico/PTM.ico"));
    box_edit_success->setIcon(QMessageBox::Information);
    box_edit_success->setWindowModality(Qt::ApplicationModal);
    QObject::connect(window_edit_ticket, &widget_edit_ticket::edit_success, box_edit_success, &QMessageBox::show);
    QObject::connect(window_edit_ticket, &widget_edit_ticket::edit_success, window_edit_ticket, &widget_edit_ticket::close);
    for(int i = 0; i < 6; i++)
    {
        QObject::connect(window_edit_ticket, &widget_edit_ticket::edit_success, texts[i], &line_edit_edit::clear);
    }

    QPushButton* button_cancel_edit = new QPushButton(window_edit_ticket);
    button_cancel_edit->resize(120, 50);
    button_cancel_edit->move(630, 220);
    button_cancel_edit->setText("取消");
    button_cancel_edit->setFont(QFont("Microsoft YaHei UI", 16));

    QObject::connect(button_cancel_edit, &QPushButton::clicked, window_edit_ticket, &widget_edit_ticket::close);

    window_edit_ticket->setAttribute(Qt::WA_QuitOnClose, false);

    return window_edit_ticket;
}

void page_ticket::create_page()
{
    list_ticket = create_tree_widget_ticket(w);
    label_instruct_search = create_label_instruct_search_ticket(w);
    text_search = create_text_search_ticket(w);
    button_search_ticket = create_button_search_ticket(w);
    button_switch_search_ticket = create_button_switch_search_ticket(w);
    button_back_ticket = create_button_back_ticket(w);
    button_add_ticket = create_button_add_ticket(w);
    button_edit_ticket = create_button_edit_ticket(w);
    button_del_ticket = create_button_del_ticket(w);
    label_total_ticket = create_label_total_ticket(w);
    window_add_ticket = create_window_add_ticket(list_ticket, label_total_ticket);
    window_edit_ticket = create_window_edit_ticket(list_ticket);
    QObject::connect(list_ticket, &tree_widget_ticket::itemClicked, button_edit_ticket, &push_button_edit_ticket::set_enabled);
    QObject::connect(list_ticket, &tree_widget_ticket::itemClicked, button_del_ticket, &push_button_del_ticket::set_enabled);
}

void page_ticket::create_list_widget(Ticket* head)
{
    Ticket* t = head;
    QStringList data;
    while(t->next != NULL)
    {
        t = t->next;
        data << t->no << t->departure << t->destination << QString::number(t->day) << QString::number(t->price) << t->time_leave.toString("HH:MM") << t->time_arrive.toString("HH:MM");
        QTreeWidgetItem* new_item = new QTreeWidgetItem(list_ticket, data);
        list_ticket->addTopLevelItem(new_item);
        func_set_alignment_and_width(list_ticket, new_item, 175);
        data.clear();

        load_progress_bar->setValue(load_progress_bar->value() + 1);
        double progress = double(load_progress_bar->value() - load_progress_bar->minimum()) * 100 / double(load_progress_bar->maximum() - load_progress_bar->minimum());
        load_progress_bar->setFormat("车次信息加载中……" + QString::number(progress, 'f', 1) + "%");
    }
}

void page_ticket::func_switch_search_type()
{
    button_switch_search_ticket->search_type_group = new QActionGroup(button_switch_search_ticket);
    button_switch_search_ticket->search_type_group->setExclusive(true);

    QMenu* menu_search = new QMenu(button_search_ticket);
    button_switch_search_ticket->menu = menu_search;
    QAction** action_search = new QAction*[7];
    for(int i = 0; i < 7; i = i + 1)
    {
        action_search[i] = new QAction(menu_search);
        action_search[i]->setText(search_type_ticket[i]);
        action_search[i]->setCheckable(true);
        menu_search->addAction(action_search[i]);
        button_switch_search_ticket->search_type_group->addAction(action_search[i]);
    }
    button_switch_search_ticket->setMenu(menu_search);
    button_search_ticket->action_search = action_search;

    button_search_ticket->search_type_group = button_switch_search_ticket->search_type_group;
    QObject::connect(button_switch_search_ticket->search_type_group, &QActionGroup::triggered, button_search_ticket, &push_button_search_ticket::change_text);
    action_search[0]->trigger();
}

void page_ticket::func_open_window_add_and_edit_ticket()
{
    QObject::connect(button_add_ticket, &push_button_add_ticket::clicked, window_add_ticket, &widget_add_ticket::show);
    QObject::connect(button_edit_ticket, &push_button_edit_ticket::clicked, window_edit_ticket, &widget_edit_ticket::show);
    QObject::connect(button_edit_ticket, &push_button_edit_ticket::clicked, window_edit_ticket, &widget_edit_ticket::show_info);
}

void page_ticket::show()
{
    list_ticket->show();
    label_instruct_search->show();
    text_search->show();
    button_search_ticket->show();
    button_switch_search_ticket->show();
    button_back_ticket->show();
    button_add_ticket->show();
    button_edit_ticket->show();
    button_del_ticket->show();
    label_total_ticket->show();
}

void page_ticket::set_hidden()
{
    list_ticket->setHidden(true);
    label_instruct_search->setHidden(true);
    text_search->setHidden(true);
    button_search_ticket->setHidden(true);
    button_switch_search_ticket->setHidden(true);
    button_back_ticket->setHidden(true);
    button_add_ticket->setHidden(true);
    button_edit_ticket->setHidden(true);
    button_del_ticket->setHidden(true);
    label_total_ticket->setHidden(true);
}

void page_ticket::func_del_ticket()
{
    QMessageBox* box_del_ticket = new QMessageBox;
    box_del_ticket->setWindowTitle("删除车次信息");
    box_del_ticket->setText("确认删除该车次信息吗？");
    box_del_ticket->addButton("确定", QMessageBox::AcceptRole);
    box_del_ticket->addButton("取消", QMessageBox::RejectRole);
    box_del_ticket->setFont(QFont("Microsoft YaHei UI", 10));
    box_del_ticket->setWindowIcon(QIcon(":/ico/PTM.ico"));
    box_del_ticket->setIcon(QMessageBox::Question);
    box_del_ticket->setWindowModality(Qt::ApplicationModal);

    QObject::connect(button_del_ticket, &push_button_del_ticket::clicked, box_del_ticket, &QMessageBox::show);

    list_ticket->confirm_del_ticket = box_del_ticket->buttons().first();
    QObject::connect(box_del_ticket, &QMessageBox::buttonClicked, list_ticket, &tree_widget_ticket::del_ticket);

    QMessageBox* box_del_success = new QMessageBox;
    box_del_success->setWindowTitle("删除成功");
    box_del_success->setText("删除车次信息成功。");
    box_del_success->addButton("确定", QMessageBox::AcceptRole);
    box_del_success->setFont(QFont("Microsoft YaHei UI", 10));
    box_del_success->setWindowIcon(QIcon(":/ico/PTM.ico"));
    box_del_success->setIcon(QMessageBox::Information);
    box_del_success->setWindowModality(Qt::ApplicationModal);
    QObject::connect(list_ticket, &tree_widget_ticket::del_success, box_del_success, &QMessageBox::show);
    QObject::connect(list_ticket, &tree_widget_ticket::del_success, button_edit_ticket, &push_button_edit_ticket::set_disabled);
    QObject::connect(list_ticket, &tree_widget_ticket::del_success, label_total_ticket, &label_total::minus_total);
    QObject::connect(label_total_ticket, &label_total::no_data, button_del_ticket, &push_button_del_ticket::set_disabled);
}

void page_ticket::search_ticket()
{
    const QString serach_type[7] = {"车次", "始发站", "终点站", "始发时间", "终到时间", "天数", "票价"};
    int t;
    for(int i = 0; i < 7; i++)
    {
        if(button_search_ticket->search_type_group->checkedAction() == button_search_ticket->action_search[i])
        {
            t = i;
        }
    }

    QString seach_text = text_search->text();
}



