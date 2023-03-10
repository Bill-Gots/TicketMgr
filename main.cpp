#include "widget.h"
#include "utils.h"
#include <QApplication>


const QString mnuStyle = "QPushButton:!pressed{border-image:url(:/new/menu/btnLeft0.jpg)} "
                         "QPushButton:hover, QPushButton:checked{border-image:url(:/new/menu/btnLeft1.jpg); color:white}";

const QString searchMethod[7] = {"查询车次", "查询站名", "查询时刻", "查询乘车时间", "查询硬座票价", "查询卧铺票价", "查询里程"};

const QString instruct[7] = {"在输入框内输入待查询的内容，点击查询按钮即可查询信息。依次单击表头可以设置内容的升序和降序排列。"
                            "点击下拉菜单可以更改查询信息的类别。输入\"-\"符号可以查询该符号前后两个值组成的区间，例如300-500。乘车时间按分钟计算。",
                            "请在下面的输入框内输入待修改的车次：",
                            "只有在点击“保存修改”按钮后，您的修改才会保存。\n请注意，一次只能修改一个车次的信息。",
                            "点击站次旁的展开按钮即可察看对该站点的编辑操作。\n请不要在下表中直接编辑或删除起始站和终点站的信息，如要编辑请在上方的输入框编辑。",
                            "要添加途径站信息，请先添加车次后再在“编辑车次信息”一栏中编辑。",
                            "请在下面的输入框内输入待删除的车次：",
                            "请注意，删除操作不可撤销。"};

const QString mnuText[4] = {"车次信息浏览与查询  ", "编辑车次信息  ", "添加或删除车次信息  ", "使用帮助  "};

const QString editButtons[3] = {"插入新站点", "编辑该站点", "删除该站点"};

const QColor changedItemColor(170, 200, 255);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    login_widget* lw = load_login_window();

    main_widget* w = load_main_window();

    func_login_interface(lw, w);

    QPushButton* button_exit = create_exit_button(w);

    QMessageBox* box_exit = create_exit_box();

    func_exit_window(w, box_exit);
    func_show_exit_box(button_exit, box_exit);

    Customer* head_customer;
    Ticket* head_ticket;
    Order* head_order;

    //int total_user = count_total(head_customer);
    //int total_ticket = count_total(head_ticket);
    //int total_order = count_total(head_order);
    //QProgressBar* load_progress_bar = create_load_progress_bar(w, total_user + total_ticket + total_user);

    int total = 3000;
    QProgressBar* load_progress_bar = create_load_progress_bar(w, total);

    QButtonGroup* menu = create_menu(w);

    create_label_systime(w);

    page_user* user_info = new page_user;
    user_info->w = w;
    user_info->load_progress_bar = load_progress_bar;
    user_info->create_page();
    user_info->func_switch_search_type();
    //user_info->create_list_widget(head_customer);
    user_info->func_open_window_add_and_edit_user();
    user_info->func_del_user();
    user_info->func_search_user();

    page_ticket* ticket_info = new page_ticket;
    ticket_info->w = w;
    ticket_info->load_progress_bar = load_progress_bar;
    ticket_info->create_page();
    ticket_info->func_switch_search_type();
    //ticket_info->create_list_widget(head_customer);
    ticket_info->func_open_window_add_and_edit_ticket();
    ticket_info->func_del_ticket();
    ticket_info->func_search_ticket();

    page_order* order_info = new page_order;
    order_info->w = w;
    order_info->load_progress_bar = load_progress_bar;
    order_info->create_page();
    order_info->func_switch_search_type();
    //order_info->create_list_widget(head_customer);
    order_info->func_open_window_add_and_edit_order();
    order_info->func_del_order();
    order_info->func_search_order();






    w->setAttribute(Qt::WA_QuitOnClose, true);



    func_switch_pages(menu, user_info, ticket_info, order_info);
    menu->button(0)->click();
    return a.exec();
}

