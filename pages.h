#ifndef PAGES_H
#define PAGES_H

#include <utils.h>

class page_user
{
public:
    main_widget* w;
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
    QLabel* label_total_user;

    void create_page();

public slots:
    void show();
    void set_hidden();
};

#endif // PAGES_H
