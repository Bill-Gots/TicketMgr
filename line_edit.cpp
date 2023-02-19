#include "line_edit.h"

line_edit_login::line_edit_login(const QString label, QWidget* parent): QLineEdit(parent)
{

}

void line_edit_login::emit_text()
{

}

line_edit_search::line_edit_search(const QString label, QWidget* parent): QLineEdit(parent)
{

}

void line_edit_search::emit_text()
{

}

line_edit_add::line_edit_add(const QString label, QWidget* parent): QLineEdit(parent)
{
    this->setText(label);
}

void line_edit_add::emit_text()
{

}

line_edit_edit::line_edit_edit(const QString label, QWidget* parent): QLineEdit(parent)
{
    this->setText(label);
}

void line_edit_edit::emit_text()
{

}
