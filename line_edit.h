#ifndef LINE_EDIT_H
#define LINE_EDIT_H

#include <QLineEdit>

class line_edit_login: public QLineEdit
{
    Q_OBJECT

public:
    line_edit_login(const QString label = "", QWidget* parent = Q_NULLPTR);


public slots:
    void emit_text();
};

class line_edit_search: public QLineEdit
{
    Q_OBJECT

public:
    line_edit_search(const QString label = "", QWidget* parent = Q_NULLPTR);


public slots:
    void emit_text();
};

#endif // LINE_EDIT_H
