#ifndef PAGES_H
#define PAGES_H

#include <QMenu>
#include <QMessageBox>
#include <QProgressBar>
#include <QHeaderView>
#include "widget.h"
#include "label.h"
#include "tree_widget.h"
#include "line_edit.h"
#include "push_button.h"

void func_set_alignment_and_width(QTreeWidget* list, QTreeWidgetItem* item, int width = 215);

class page_user
{
public:
    main_widget* w;
    QProgressBar* load_progress_bar;
    tree_widget_user* list_user;
    QLabel* label_instruct_search;
    line_edit_search* text_search;
    push_button_search_user* button_search_user;
    push_button_switch_search_user* button_switch_search_user;
    push_button_back* button_back_user;
    push_button_add_user* button_add_user;
    push_button_edit_user* button_edit_user;
    push_button_del_user* button_del_user;
    widget_add_user* window_add_user;
    widget_edit_user* window_edit_user;
    label_total* label_total_user;
    QMessageBox* add_user_success, add_user_failed;

    tree_widget_user* create_tree_widget_user(main_widget* w);
    QLabel* create_label_instruct_search_user(main_widget* w);
    line_edit_search* create_text_search_user(main_widget* w);
    push_button_search_user* create_button_search_user(main_widget* w);
    push_button_switch_search_user* create_button_switch_search_user(main_widget* w);
    push_button_back* create_button_back_user(main_widget* w);
    push_button_add_user* create_button_add_user(main_widget* w);
    push_button_edit_user* create_button_edit_user(main_widget* w);
    push_button_del_user* create_button_del_user(main_widget* w);
    label_total* create_label_total_user(main_widget* w);
    widget_add_user* create_window_add_user(tree_widget_user* list_user, label_total* total);
    widget_edit_user* create_window_edit_user(tree_widget_user* list_user);
    void create_page();
    void func_switch_search_type();
    void create_list_widget(Customer* head);
    void func_open_window_add_and_edit_user();
    void func_del_user();
    void search_user();

public slots:
    void show();
    void set_hidden();
};

class page_ticket
{
public:
    main_widget* w;
    QProgressBar* load_progress_bar;
    tree_widget_ticket* list_ticket;
    QLabel* label_instruct_search;
    line_edit_search* text_search;
    push_button_search_ticket* button_search_ticket;
    push_button_switch_search_ticket* button_switch_search_ticket;
    push_button_back* button_back_ticket;
    push_button_add_ticket* button_add_ticket;
    push_button_edit_ticket* button_edit_ticket;
    push_button_del_ticket* button_del_ticket;
    widget_add_ticket* window_add_ticket;
    widget_edit_ticket* window_edit_ticket;
    label_total* label_total_ticket;
    QMessageBox* add_ticket_success, add_ticket_failed;

    tree_widget_ticket* create_tree_widget_ticket(main_widget* w);
    QLabel* create_label_instruct_search_ticket(main_widget* w);
    line_edit_search* create_text_search_ticket(main_widget* w);
    push_button_search_ticket* create_button_search_ticket(main_widget* w);
    push_button_switch_search_ticket* create_button_switch_search_ticket(main_widget* w);
    push_button_back* create_button_back_ticket(main_widget* w);
    push_button_add_ticket* create_button_add_ticket(main_widget* w);
    push_button_edit_ticket* create_button_edit_ticket(main_widget* w);
    push_button_del_ticket* create_button_del_ticket(main_widget* w);
    label_total* create_label_total_ticket(main_widget* w);
    widget_add_ticket* create_window_add_ticket(tree_widget_ticket* list_ticket, label_total* total);
    widget_edit_ticket* create_window_edit_ticket(tree_widget_ticket* list_ticket);
    void create_page();
    void func_switch_search_type();
    void create_list_widget(Ticket* head);
    void func_open_window_add_and_edit_ticket();
    void func_del_ticket();
    void search_ticket();

public slots:
    void show();
    void set_hidden();
};

class page_order
{
public:
    main_widget* w;
    QProgressBar* load_progress_bar;
    tree_widget_order* list_order;
    QLabel* label_instruct_search;
    line_edit_search* text_search;
    push_button_search_order* button_search_order;
    push_button_switch_search_order* button_switch_search_order;
    push_button_back* button_back_order;
    push_button_add_order* button_add_order;
    push_button_edit_order* button_edit_order;
    push_button_del_order* button_del_order;
    widget_add_order* window_add_order;
    widget_edit_order* window_edit_order;
    label_total* label_total_order;
    QMessageBox* add_order_success, add_order_failed;

    tree_widget_order* create_tree_widget_order(main_widget* w);
    QLabel* create_label_instruct_search_order(main_widget* w);
    line_edit_search* create_text_search_order(main_widget* w);
    push_button_search_order* create_button_search_order(main_widget* w);
    push_button_switch_search_order* create_button_switch_search_order(main_widget* w);
    push_button_back* create_button_back_order(main_widget* w);
    push_button_add_order* create_button_add_order(main_widget* w);
    push_button_edit_order* create_button_edit_order(main_widget* w);
    push_button_del_order* create_button_del_order(main_widget* w);
    label_total* create_label_total_order(main_widget* w);
    widget_add_order* create_window_add_order(tree_widget_order* list_order, label_total* total);
    widget_edit_order* create_window_edit_order(tree_widget_order* list_order);
    void create_page();
    void func_switch_search_type();
    void create_list_widget(Customer* head);
    void func_open_window_add_and_edit_order();
    void func_del_order();
    void search_order();

public slots:
    void show();
    void set_hidden();
};

#endif // PAGES_H
