#include <pages.h>

void page_user::create_page()
{
    list_user = create_widget_user(w);
    label_instruct_search = create_label_instruct_search(w);
    text_search = create_text_search(w);
    button_search_user = create_button_search_user(w);
    button_switch_search_user = create_button_switch_search_user(w);
    button_back_user = create_button_back(w);
    button_add_user = create_button_add_user(w);
    button_edit_user = create_button_edit_user(w);
    button_del_user = create_button_del_user(w);
    window_add_user = create_window_add_user();
    window_edit_user = create_window_edit_user();
    label_total_user = create_label_total_user(w);
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

