#include "utils.h"
#include "push_button.h"

login_widget* load_login_window()
{
    login_widget* lw = new login_widget;
    lw->setFixedSize(800, 425);
    lw->setWindowTitle("登录数据库");
    lw->setPalette(QPalette(Qt::white));
    lw->setWindowIcon(QIcon(":/ico/PTM.ico"));
    lw->show();
    return lw;
}

main_widget* load_main_window()
{
    main_widget* w = new main_widget;
    w->setWindowTitle("12307客运列车票务管理系统");
    w->setPalette(QPalette(Qt::white));
    w->setWindowIcon(QIcon(":/ico/PTM.ico"));
    return w;
}

void func_login_interface(login_widget* lw, main_widget* w)
{
    QLabel* label_welcome = new QLabel("欢迎使用12307客运列车票务信息管理系统", lw);
    label_welcome->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    label_welcome->move(0, 0);
    label_welcome->resize(lw->width(), 100);
    label_welcome->setFont(QFont("华文中宋", 22));
    label_welcome->setStyleSheet("border-image:url(:/new/login_title/login_title.png); color:#FFFFFF");
    label_welcome->show();

    QLabel* label_user = new QLabel("用户名：", lw);
    label_user->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label_user->move(100, 125);
    label_user->resize(100, 50);
    label_user->setFont(QFont("Microsoft YaHei UI", 12));
    label_user->show();

    QLineEdit* text_user = new QLineEdit(lw);
    text_user->move(200, 125);
    text_user->resize(500, 50);
    text_user->setFont(QFont("Microsoft YaHei UI", 12));
    text_user->setClearButtonEnabled(true);
    text_user->setMaxLength(20);
    text_user->show();

    QLabel* label_password = new QLabel("密   码：", lw);
    label_password->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label_password->move(100, 200);
    label_password->resize(100, 50);
    label_password->setFont(QFont("Microsoft YaHei UI", 12));
    label_password->show();

    QLineEdit* text_password = new QLineEdit(lw);
    text_password->move(200, 200);
    text_password->resize(500, 50);
    text_password->setFont(QFont("Microsoft YaHei UI", 12));
    text_password->setClearButtonEnabled(true);
    text_password->setMaxLength(20);
    text_password->show();

    QLabel* label_sql_name = new QLabel("数据库名：", lw);
    label_sql_name->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label_sql_name->move(100, 275);
    label_sql_name->resize(100, 50);
    label_sql_name->setFont(QFont("Microsoft YaHei UI", 12));
    label_sql_name->show();

    QLineEdit* text_sql_name = new QLineEdit(lw);
    text_sql_name->move(200, 275);
    text_sql_name->resize(175, 50);
    text_sql_name->setFont(QFont("Microsoft YaHei UI", 12));
    text_sql_name->setClearButtonEnabled(true);
    text_sql_name->setMaxLength(20);
    text_sql_name->show();

    QLabel* label_port = new QLabel("端   口：", lw);
    label_port->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label_port->move(425, 275);
    label_port->resize(75, 50);
    label_port->setFont(QFont("Microsoft YaHei UI", 12));
    label_port->show();

    QLineEdit* text_port = new QLineEdit(lw);
    text_port->move(500, 275);
    text_port->resize(200, 50);
    text_port->setFont(QFont("Microsoft YaHei UI", 12));
    text_port->setClearButtonEnabled(true);
    text_port->setMaxLength(20);
    text_port->show();

    push_button_login* button_login = new push_button_login(text_user, text_password, text_sql_name, text_port, "登   录", lw);
    button_login->move(300, 350);
    button_login->resize(200, 50);
    button_login->setFont(QFont("Microsoft YaHei UI", 14));
    button_login->setIcon(QIcon(":/new/head/head_icon.png"));
    button_login->setIconSize(QSize(21, 21));
    button_login->show();

    QMessageBox* box_login_success = new QMessageBox;
    box_login_success->setWindowTitle("提示");
    box_login_success->setText("登录数据库成功");
    box_login_success->setFont(QFont("Microsoft YaHei UI", 10));
    box_login_success->setWindowIcon(QIcon(":/ico/PTM.ico"));
    box_login_success->setIcon(QMessageBox::Information);
    box_login_success->setWindowModality(Qt::ApplicationModal);

    QMessageBox* box_login_failed = new QMessageBox;
    box_login_failed->setWindowTitle("提示");
    box_login_failed->setText("登录数据库失败");
    box_login_failed->setFont(QFont("Microsoft YaHei UI", 10));
    box_login_failed->setWindowIcon(QIcon(":/ico/PTM.ico"));
    box_login_failed->setIcon(QMessageBox::Critical);
    box_login_failed->setWindowModality(Qt::ApplicationModal);

    QObject::connect(button_login, &push_button_login::clicked, button_login, &push_button_login::login);
    QObject::connect(button_login, &push_button_login::login_success, box_login_success, &QMessageBox::show);
    QObject::connect(button_login, &push_button_login::login_success, lw, &login_widget::close);
    QObject::connect(button_login, &push_button_login::login_success, w, &main_widget::showFullScreen);
    QObject::connect(button_login, &push_button_login::login_failed, box_login_failed, &QMessageBox::show);
}

QPushButton* create_exit_button(main_widget* w)
{
    QPushButton* button_exit = new QPushButton(w);
    button_exit->resize(145, 145);
    button_exit->move(1750, 22);
    button_exit->setFlat(true);
    button_exit->setIconSize(QSize(145, 145));
    button_exit->setStyleSheet("QPushButton:!hover{border-image:url(:/new/close/exit0.jpg)} "
                            "QPushButton:hover{border-image:url(:/new/close/exit1.jpg)}");
    button_exit->show();
    button_exit->setCursor(QCursor(Qt::PointingHandCursor));
    return button_exit;
}

QMessageBox* create_exit_box()
{
    QMessageBox* box_exit = new QMessageBox;
    box_exit->setWindowTitle("提示");
    box_exit->setText("您确定要退出吗？");
    box_exit->setFont(QFont("Microsoft YaHei UI", 10));
    box_exit->addButton("确定", QMessageBox::AcceptRole);
    box_exit->addButton("取消", QMessageBox::RejectRole);
    box_exit->setWindowIcon(QIcon(":/ico/PTM.ico"));
    box_exit->setIcon(QMessageBox::Question);
    box_exit->setWindowModality(Qt::ApplicationModal);
    return box_exit;
}

void func_exit_window(main_widget* w, QMessageBox* box_exit)
{
    w->button_confirm_exit = box_exit->buttons().first();
    QObject::connect(box_exit, &QMessageBox::buttonClicked, w, &main_widget::confirm_exit);
}

void func_show_exit_box(QPushButton* button_exit, QMessageBox* box_exit)
{
    QObject::connect(button_exit, &QPushButton::clicked, box_exit, &QMessageBox::show);
}

template <typename T>
int count_total(T head)
{
    int total = 0;
    T t = head;
    while(t->next != NULL)
    {
        t = t->next;
        total += 1;
    }
    return total;
}

QProgressBar* create_load_progress_bar(main_widget* w, int total)
{
    QProgressBar* load_progress_bar = new QProgressBar(w);
    load_progress_bar->resize(1200, 60);
    load_progress_bar->move(400, 540);
    load_progress_bar->setMinimum(0);
    load_progress_bar->setMaximum(total);
    load_progress_bar->setValue(0);
    double progress = double(load_progress_bar->value() - load_progress_bar->minimum()) * 100 / (load_progress_bar->maximum() - load_progress_bar->minimum());
    load_progress_bar->setFormat("数据库信息加载中……" + QString::number(0, 'f', 1) + "%");
    load_progress_bar->setFont(QFont("Microsoft YaHei UI", 16));
    load_progress_bar->setStyleSheet("QProgressBar{background:white; color:black;} QProgressBar::chunk{background:#327bff}");
    load_progress_bar->setAlignment(Qt::AlignCenter);
    load_progress_bar->show();
    return load_progress_bar;
}

const QString mnuText[4] = {"用户信息管理", "车票信息管理", "订单信息管理", "使用帮助"};

QButtonGroup* create_menu(main_widget* w)
{
    QPushButton* button_menu[4];
    QButtonGroup* menu = new QButtonGroup;
    menu->setExclusive(true);
    for(int i = 0; i < 4; i = i + 1)
    {
        button_menu[i] = new QPushButton(mnuText[i], w);
        menu->addButton(button_menu[i], i);
        button_menu[i]->resize(350, 110);
        button_menu[i]->move(0, 188 + i * 110);
        button_menu[i]->setFlat(true);
        button_menu[i]->setFont(QFont("Microsoft YaHei UI", 18));
        button_menu[i]->setCheckable(true);
        button_menu[i]->setStyleSheet("QPushButton:!pressed{border-image:url(:/new/menu/btnLeft0.jpg)} "
                                  "QPushButton:hover, QPushButton:checked{border-image:url(:/new/menu/btnLeft1.jpg); color:white}");
        button_menu[i]->show();
    }
    return menu;
}

label_system_time* create_label_systime(main_widget* w)
{
    label_system_time* label_systime = new label_system_time(w);
    label_systime->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label_systime->move(5, 1033);
    label_systime->resize(500, 47);
    label_systime->setFont(QFont("Microsoft YaHei UI", 12));
    label_systime->show();
    QTimer *timer = new QTimer(w);
    timer->start(500);
    QObject::connect(timer, &QTimer::timeout, label_systime, &label_system_time::update_time);
    return label_systime;
}

tree_widget_user* create_tree_widget_user(main_widget* w)
{
    QStringList header_user;
    header_user << "姓名" << "身份证号码" << "用户名" << "密码" << "联系电话" << "优惠类型" << "订单信息";
    tree_widget_user* list_user = new tree_widget_user(w);
    list_user->resize(1567, 680);
    list_user->move(353, 298);
    list_user->setColumnCount(7);
    list_user->setHeaderLabels(header_user);
    list_user->setFont(QFont("Microsoft YaHei UI", 14));
    list_user->setUniformRowHeights(false);
    return list_user;
}

const QString instruct_search = "在输入框内输入待查询的内容，点击查询按钮即可查询信息。依次单击表头可以设置内容的升序和降序排列。 点击下拉菜单可以更改查询信息的类别。";

QLabel* create_label_instruct_search(main_widget* w)
{
    QLabel* label_instruct_search = new QLabel(instruct_search, w);
    label_instruct_search->resize(725, 100);
    label_instruct_search->move(520, 195);
    label_instruct_search->setText(instruct_search);
    label_instruct_search->setFont(QFont("Microsoft YaHei UI", 12));
    label_instruct_search->setWordWrap(true);
    return label_instruct_search;
}

line_edit_search* create_text_search(main_widget* w)
{
    line_edit_search* text_search = new line_edit_search("", w);
    text_search->resize(440, 60);
    text_search->move(1260, 215);
    text_search->setFont(QFont("Microsoft YaHei UI", 16));
    text_search->setClearButtonEnabled(true);
    text_search->setMaxLength(40);
    return text_search;
}

push_button_search_user* create_button_search_user(main_widget* w)
{
    push_button_search_user* button_search_user = new push_button_search_user("搜索", w);
    button_search_user->resize(170, 60);
    button_search_user->move(1710, 215);
    button_search_user->setIcon(QIcon(":/new/search/btnSearch.png"));
    button_search_user->setIconSize(QSize(25, 25));
    button_search_user->setFont(QFont("Microsoft YaHei UI", 12));
    return button_search_user;
}

push_button_switch_search_user* create_button_switch_search_user(main_widget* w)
{
    push_button_switch_search_user* button_switch_search_user = new push_button_switch_search_user(w);
    button_switch_search_user->resize(20, 60);
    button_switch_search_user->move(1880, 215);
    return button_switch_search_user;
}

push_button_back* create_button_back(main_widget* w)
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
push_button_add_user* create_button_add_user(main_widget* w)
{
    push_button_add_user* button_add_user = new push_button_add_user("添加用户信息", w);
    button_add_user->resize(150, 40);
    button_add_user->move(375, 985);
    button_add_user->setFont(font_button_bottom);
    return button_add_user;
}
push_button_edit_user* create_button_edit_user(main_widget* w)
{
    push_button_edit_user* button_edit_user = new push_button_edit_user("编辑用户信息", w);
    button_edit_user->resize(150, 40);
    button_edit_user->move(560, 985);
    button_edit_user->setFont(font_button_bottom);
    return button_edit_user;
}

push_button_del_user* create_button_del_user(main_widget* w)
{
    push_button_del_user* button_del_user = new push_button_del_user("删除用户信息", w);
    button_del_user->resize(150, 40);
    button_del_user->move(745, 985);
    button_del_user->setFont(font_button_bottom);
    return button_del_user;
}

widget_operate_user* create_window_add_user()
{
    widget_operate_user* window_add_user = new widget_operate_user();
    window_add_user->setWindowTitle("添加用户信息");
    window_add_user->setPalette(QPalette(Qt::white));
    window_add_user->setWindowIcon(QIcon(":/ico/PTM.ico"));
    window_add_user->setWindowModality(Qt::ApplicationModal);


    return window_add_user;
}

widget_edit_user* create_window_edit_user()
{
    widget_edit_user* window_edit_user = new widget_edit_user();
    window_edit_user->setWindowTitle("编辑用户信息");
    window_edit_user->setPalette(QPalette(Qt::white));
    window_edit_user->setWindowIcon(QIcon(":/ico/PTM.ico"));
    window_edit_user->setWindowModality(Qt::ApplicationModal);
    return window_edit_user;
}

label_total* create_label_total_user(main_widget* w)
{
    label_total* label_total_user = new label_total("现有用户信息总数：", "用户", w);
    label_total_user->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label_total_user->resize(350, 40);
    label_total_user->move(1550, 985);
    label_total_user->setFont(QFont("Microsoft YaHei UI", 13));
    return label_total_user;
}

