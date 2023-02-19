#ifndef UTILS_H
#define UTILS_H


#include <QMessageBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QProgressBar>
#include <QTimer>
#include <QMenu>
#include "dt.h"
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
int count_total(T head);
QProgressBar* create_load_progress_bar(main_widget* w, int total);
QButtonGroup* create_menu(main_widget* w);
label_system_time* create_label_systime(main_widget* w);
tree_widget_user* create_tree_widget_user(main_widget* w);
QLabel* create_label_instruct_search(main_widget* w);
line_edit_search* create_text_search(main_widget* w);
push_button_search_user* create_button_search_user(main_widget* w);
push_button_switch_search_user* create_button_switch_search_user(main_widget* w);
push_button_back* create_button_back(main_widget* w);
push_button_add_user* create_button_add_user(main_widget* w);
push_button_edit_user* create_button_edit_user(main_widget* w);
push_button_del_user* create_button_del_user(main_widget* w);
widget_operate_user* create_window_add_user();
widget_edit_user* create_window_edit_user();
label_total* create_label_total_user(main_widget* w);

#endif // UTILS_H
