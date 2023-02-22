#ifndef UTILS_H
#define UTILS_H


#include <QMessageBox>
#include <QProgressBar>
#include <QButtonGroup>
#include <QTimer>
#include <QHeaderView>
#include "widget.h"
#include "label.h"
#include "tree_widget.h"
#include "line_edit.h"
#include "push_button.h"
#include "pages.h"


login_widget* load_login_window();
main_widget* load_main_window();
void func_login_interface(login_widget* lw, main_widget* w);
QPushButton* create_exit_button(main_widget* w);
QMessageBox* create_exit_box();
void func_exit_window(main_widget* w, QMessageBox* box_exit);
void func_show_exit_box(QPushButton* button_exit, QMessageBox* box_exit);
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
template <typename T>
void destory_list(T head)
{
    T t1 = head, t2;
    while(t1->next != NULL)
    {
        t2 = t1;
        t1 = t1->next;
        delete t2;
    }
    delete t1;
}
QProgressBar* create_load_progress_bar(main_widget* w, int total);
QButtonGroup* create_menu(main_widget* w);
label_system_time* create_label_systime(main_widget* w);


void func_switch_pages(QButtonGroup* menu, page_user* user_info, page_ticket* ticket_info, page_order* order_info);

#endif // UTILS_H
