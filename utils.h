#ifndef UTILS_H
#define UTILS_H

#include "widget.h"
#include "label.h"
#include <QMessageBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QProgressBar>
#include <QTimer>

login_widget* load_login_window();
main_widget* load_main_window();
void func_login_interface(login_widget* lw, main_widget* w);
QPushButton* create_exit_button(main_widget* w);
QMessageBox* create_exit_box();
void func_exit_window(main_widget* w, QMessageBox* box_exit);
void func_show_exit_box(QPushButton* button_exit, QMessageBox* box_exit);
void load_data();
QProgressBar* create_load_progress_bar(main_widget* w, int total);
void create_menu(main_widget* w);
label_system_time* create_label_systime(main_widget* w);
void create_user_info_list(main_widget* w);

#endif // UTILS_H
