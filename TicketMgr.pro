QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        label.cpp \
        line_edit.cpp \
        main.cpp \
        pages.cpp \
        push_button.cpp \
        tree_widget.cpp \
        utils.cpp \
        widget.cpp

HEADERS += \
        dt.h \
        label.h \
        line_edit.h \
        pages.h \
        push_button.h \
        tree_widget.h \
        utils.h \
        widget.h

FORMS += \
    main_widget.ui

RESOURCES += \
    pic_head.qrc \
    pic_close.qrc \
    icon.qrc \
    pic_login_title.qrc \
    pic_menu.qrc \
    pic_search.qrc \
    pic_back.qrc \
    pic_save.qrc \
    pic_left.qrc \
    pic_addanddel.qrc

TRANSLATIONS += \
    TicketMgr_zh_CN.ts

RC_ICONS += TicketMgr.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
