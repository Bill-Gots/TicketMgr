#include "widget.h"
#include <QApplication>
#include <fstream>
#include <QTextStream>
#include <QTimer>
#include <QProgressBar>
#include <QList>
#include <QStringList>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMenu>
#include <QLineEdit>
#include <QToolButton>
#include <QFrame>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDebug>

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

void setWidthAndAlignCenter(QTreeWidget* list, QTreeWidgetItem* item)
{
    for(int i = 0; i <= list->columnCount(); i = i + 1)
    {
        item->setTextAlignment(i, Qt::AlignCenter);
        list->setColumnWidth(i, 140);
    }
}

class MyWidget:public Widget
{
    Q_OBJECT

signals:
    void conflitNo();

public:
    QPushButton* agree;
    train* list;
    int* total;

    MyWidget(QWidget* parent = 0):Widget(parent)
    {

    }

public slots:
    void confirmExit(QAbstractButton* clickedBtn)
    {
        if(clickedBtn == (QAbstractButton*) agree)
        {
            train* p = list;
            std::ofstream outfile("data.txt", std::ios::trunc);
            outfile << *total << std::endl;
            while(p->next != NULL)
            {
                p = p->next;
                outfile << p->No << '\t' << p->departure << '\t' << p->destination
                    << '\t' << p->LeaveTime.hour() << '\t' << p->LeaveTime.minute()
                    << '\t' << p->ArriveTime.hour() << '\t' << p->ArriveTime.minute()
                    << '\t' << p->numOfPasses
                    << '\t' << p->priceSit << '\t' << p->priceSleep
                    << '\t' << p->days << '\t' << p->distance << std::endl;
                passStation* q = p->passStations;
                while (q->next != NULL)
                {
                    q = q->next;
                    outfile << q->no << '\t' << q->station
                        << '\t' << q->arriveTime.hour() << '\t' << q->arriveTime.minute()
                        << '\t' << q->leaveTime.hour() << '\t' << q->leaveTime.minute()
                        << '\t' << q->day << '\t' << q->kilometers << std::endl;
                }
            }
            outfile.close();

            this->close();
        }
    }

    void showEditWindow(int id)
    {
        if(!(id % 3 == 2))
        {
            this->Widget::show();
        }
    }
};

class MyLabel:public QLabel
{
    Q_OBJECT

public:
    int* numOfResult, * total;
    int id;

    MyLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags()):QLabel(parent, f)
    {

    }

public slots:
    void setHidden()
    {
        this->QLabel::setHidden(true);
    }

    void updateTime()
    {
        this->setText(QDateTime::currentDateTime().toString("系统时间：yyyy年M月d日 dddd  HH:mm:ss"));
    }

    void updateTotal()
    {
        this->setText("现有车次信息总数：" + QString::number(*total));
    }

    void changeText()
    {
        this->setText("系统查询到了" + QString::number(*numOfResult) + "个符合条件的结果：\n"
                      "如要继续在结果中查询，可直接再次进行查询；如要重新查询，请点击返回按钮。");
        *numOfResult = 0;
    }

    void changeNo(train* result)
    {
        this->setText(QString::fromStdString(result->No) + "车次信息如下：");
    }

    void showInfo(train* result)
    {
        switch (id)
        {
        case 0:this->setText(QString::fromStdString(result->No)); break;
        case 1:this->setText(QString::fromStdString(result->departure)); break;
        case 2:this->setText(QString::fromStdString(result->destination)); break;
        case 3:this->setText(result->LeaveTime.toString("HH:mm")); break;
        case 4:this->setText(result->ArriveTime.toString("HH:mm")); break;
        case 5:this->setText(QString::number(result->days)); break;
        case 6:this->setText(QString::number(result->priceSit)); break;
        case 7:this->setText(QString::number(result->priceSleep)); break;
        case 8:this->setText(QString::number(result->distance)); break;
        case 9:this->setText(QString::fromStdString(result->Note)); break;
        }
    }

    void back()
    {
        this->setText(instruct[0]);
    }
};

class MyPushButton:public QPushButton
{
    Q_OBJECT

public:
    QActionGroup* actSearchGroup;

    MyPushButton(QWidget* parent = Q_NULLPTR):QPushButton(parent)
    {

    }

    MyPushButton(const QString& text, QWidget *parent = Q_NULLPTR):QPushButton(text, parent)
    {

    }

public slots:
    void setHidden()
    {
        this->QPushButton::setHidden(true);
    }

    void setEnabled()
    {
        this->QPushButton::setEnabled(true);
    }

    void setDisabled()
    {
        this->QPushButton::setDisabled(true);
    }

    void changeState(bool empty)
    {
        this->QPushButton::setEnabled(!empty);
    }

    void changeText()
    {
        this->setText(actSearchGroup->checkedAction()->text());
    }
};

class MyTreeWidget:public QTreeWidget
{
    Q_OBJECT

signals:
    void searchFinished();
    void searchFound(train* result);
    void searchNoFound();
    void wrongInput();
    void reverseInput();
    void sendStation(QTreeWidgetItem* item);
    void sendList(MyTreeWidget* list);
    void received();
    void checkStationSuccess();
    void checkAllSuccess();
    void trainIsSet();
    void trainCreated();
    void delFound(train* result);
    void delNoFound();
    void conflictDelNumber();
    void trainDeleted();

public:
    QAction** actSearch;
    QActionGroup* actSearchGroup;
    static train* head, * result, * delResult, * addTrain;
    int* numOfResult, * total;
    int numOfReceived, passedSection, setItem;
    QButtonGroup* childButtons;
    QTreeWidgetItem* changingItem;
    static QTreeWidgetItem* tempTrain, * newTrain;
    MyWidget* wEdit;
    QMessageBox* deleteBox;
    QPushButton* deleteStationConfirm, * deleteTrainConfirm;
    MyPushButton* btnSave;

    MyTreeWidget(QWidget* parent = Q_NULLPTR):QTreeWidget(parent)
    {
        numOfReceived = passedSection = setItem = 0;
        deleteBox = new QMessageBox;
        deleteBox->setWindowTitle("确认删除该站点");
        deleteBox->setText("您确定要删除这个站点吗？");
        deleteBox->setFont(QFont("Microsoft YaHei UI", 10));
        deleteStationConfirm = deleteBox->addButton("确定", QMessageBox::AcceptRole);
        deleteBox->addButton("取消", QMessageBox::RejectRole);
        deleteBox->setWindowIcon(QIcon(":/ico/PTM.ico"));
        deleteBox->setIcon(QMessageBox::Critical);
        deleteBox->setWindowModality(Qt::ApplicationModal);//直到关闭提示框才使主窗口恢复焦点
        connect(deleteBox, &QMessageBox::buttonClicked, this, confirmDeleteStation);

        tempTrain = new QTreeWidgetItem((QTreeWidget*) (NULL));
        newTrain = new QTreeWidgetItem((QTreeWidget*) (NULL));
        addTrain = new train;
    }

public slots:
    void setHidden()
    {
        this->QTreeWidget::setHidden(true);
    }

    void searchAndShowResult(QString inputText)
    {
        int n = 0, numOfHyphen = 0;
        while (n < inputText.length())
        {
            if(inputText[n] == '-')
            {
                numOfHyphen = numOfHyphen + 1;
                if(numOfHyphen >= 2)
                {
                    emit wrongInput();
                    return;
                }
            }
            n = n + 1;
        }

        int searchType;
        for(int i = 0; i < 7; i = i + 1)
        {
            if(actSearchGroup->checkedAction() == actSearch[i])
            {
                searchType = i;
            }
        }

        QString first, second;
        if(numOfHyphen)
        {
            QStringList interval = inputText.split('-');
            first = interval.takeFirst();
            second = interval.takeFirst();
        }

        switch (searchType)
        {
        case 0://查询车次
        {
            if(numOfHyphen)
            {
                if(first.length() != 5 || second.length() != 5 || first > second)
                {
                    emit wrongInput();
                    return;
                }
                else
                {
                    if(!first[0].isLetter())
                    {
                        emit wrongInput();
                        return;
                    }
                    for(int i = 1; i < 5; i = i + 1)
                    {
                        if(!inputText[i].isDigit())
                        {
                            emit wrongInput();
                            return;
                        }
                    }

                    if(!second[0].isLetter())
                    {
                        emit wrongInput();
                        return;
                    }
                    for(int i = 1; i < 5; i = i + 1)
                    {
                        if(!second[i].isDigit())
                        {
                            emit wrongInput();
                            return;
                        }
                    }
                }

                QTreeWidgetItem* tempItem;
                for(int i = 0; i < this->topLevelItemCount(); i = i + 1)
                {
                    tempItem = this->topLevelItem(i);
                    if(!(tempItem->isHidden()))
                    {
                        if(tempItem->text(0) >= first && tempItem->text(0) <= second)
                        {
                            *numOfResult = *numOfResult + 1;
                        }
                        else
                        {
                            tempItem->setHidden(true);
                        }
                    }
                }

            }
            else
            {
                if(inputText.length() > 5)
                {
                    emit wrongInput();
                    return;
                }
                else
                {
                    if(!inputText[0].isLetterOrNumber())
                    {
                        emit wrongInput();
                        return;
                    }
                    for(int i = 1; i < inputText.length(); i = i + 1)
                    {
                        if(!inputText[i].isDigit())
                        {
                            emit wrongInput();
                            return;
                        }
                    }
                }

                QTreeWidgetItem* tempItem;
                for(int i = 0; i < this->topLevelItemCount(); i = i + 1)
                {
                    tempItem = this->topLevelItem(i);
                    if(!(tempItem->isHidden()))
                    {
                        if(tempItem->text(0).contains(inputText))
                        {
                            *numOfResult = *numOfResult + 1;
                        }
                        else
                        {
                            tempItem->setHidden(true);
                        }
                    }
                }
            }
            emit searchFinished();
            break;
        }
        case 1://查询站名
        {
            QTreeWidgetItem* tempItem;
            for(int i = 0; i < this->topLevelItemCount(); i = i + 1)
            {
                tempItem = this->topLevelItem(i);
                if(!(tempItem->isHidden()))
                {
                    if(tempItem->text(1).contains(inputText) || tempItem->text(2).contains(inputText))
                    {
                        *numOfResult = *numOfResult + 1;
                    }
                    else
                    {
                        QTreeWidget* tempChildList = (QTreeWidget*) (QTreeWidget::itemWidget(tempItem->child(0), 0));
                        QTreeWidgetItem* tempChildListItem;
                        for(int j = 0; j < tempChildList->topLevelItemCount(); j = j + 1)
                        {
                            tempChildListItem = tempChildList->topLevelItem(j);
                            if(tempChildListItem->text(1).contains(inputText))
                            {
                                *numOfResult = *numOfResult + 1;
                                break;
                            }
                            else
                            {
                                if(j == tempChildList->topLevelItemCount() - 1)
                                {
                                    tempItem->setHidden(true);
                                }
                            }
                        }
                    }
                }
            }
            emit searchFinished();
            break;
        }
        case 2://查询时刻
        {
            if(numOfHyphen)
            {
                if(first.length() != 5 || second.length() != 5 ||
                   !(first[0].isDigit() && first[1].isDigit() && first[2] == ':' && first[3].isDigit() && first[4].isDigit() &&
                     second[0].isDigit() && second[1].isDigit() && second[2] == ':' && second[3].isDigit() && second[4].isDigit()))
                {
                    emit wrongInput();
                    return;
                }
                else
                {
                    QStringList tempTime = first.split(':');
                    QString tempHour = tempTime.takeFirst();
                    QString tempMin = tempTime.takeFirst();
                    if(tempHour >= "24" || tempMin >= "60")
                    {
                        emit wrongInput();
                        return;
                    }
                    tempTime = second.split(':');
                    tempHour = tempTime.takeFirst();
                    tempMin = tempTime.takeFirst();
                    if(tempHour >= "24" || tempMin >= "60")
                    {
                        emit wrongInput();
                        return;
                    }
                }

                QTreeWidgetItem* tempItem;
                for(int i = 0; i < this->topLevelItemCount(); i = i + 1)
                {
                    tempItem = this->topLevelItem(i);
                    if(!(tempItem->isHidden()))
                    {
                        if((tempItem->text(3) >= first && tempItem->text(3) <= second) ||
                           (tempItem->text(4) >= first && tempItem->text(4) <= second))
                        {
                            *numOfResult = *numOfResult + 1;
                        }
                        else
                        {
                            QTreeWidget* tempChildList = (QTreeWidget*) (QTreeWidget::itemWidget(tempItem->child(0), 0));
                            QTreeWidgetItem* tempChildListItem;
                            for(int j = 0; j < tempChildList->topLevelItemCount(); j = j + 1)
                            {
                                tempChildListItem = tempChildList->topLevelItem(j);
                                if((tempChildListItem->text(2) >= first && tempChildListItem->text(2) <= second) ||
                                   (tempChildListItem->text(3) >= first && tempChildListItem->text(3) <= second))
                                {
                                    *numOfResult = *numOfResult + 1;
                                    break;
                                }
                                else
                                {
                                    if(j == tempChildList->topLevelItemCount() - 1)
                                    {
                                        tempItem->setHidden(true);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(inputText.length() != 5 ||
                   !(inputText[0].isDigit() && inputText[1].isDigit() && inputText[2] == ':' && inputText[3].isDigit() && inputText[4].isDigit()))
                {
                    emit wrongInput();
                    return;
                }
                else
                {
                    QStringList tempTime = inputText.split(':');
                    QString tempHour = tempTime.takeFirst();
                    QString tempMin = tempTime.takeFirst();
                    if(tempHour >= "24" || tempMin >= "60")
                    {
                        emit wrongInput();
                        return;
                    }
                }

                QTreeWidgetItem* tempItem;
                for(int i = 0; i < this->topLevelItemCount(); i = i + 1)
                {
                    tempItem = this->topLevelItem(i);
                    if(!(tempItem->isHidden()))
                    {
                        if(tempItem->text(3) == inputText || tempItem->text(4) == inputText)
                        {
                            *numOfResult = *numOfResult + 1;
                        }
                        else
                        {
                            QTreeWidget* tempChildList = (QTreeWidget*) (QTreeWidget::itemWidget(tempItem->child(0), 0));
                            QTreeWidgetItem* tempChildListItem;
                            for(int j = 0; j < tempChildList->topLevelItemCount(); j = j + 1)
                            {
                                tempChildListItem = tempChildList->topLevelItem(j);
                                if(tempChildListItem->text(2) == inputText || tempChildListItem->text(3) == inputText)
                                {
                                    *numOfResult = *numOfResult + 1;
                                    break;
                                }
                                else
                                {
                                    if(j == tempChildList->topLevelItemCount() - 1)
                                    {
                                        tempItem->setHidden(true);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            emit searchFinished();
            break;
        }
        case 3://查询乘车时间
        {
            if(numOfHyphen)
            {
                for(int i = 0; i < first.length(); i = i + 1)
                {
                    if(!first[i].isDigit())
                    {
                        emit wrongInput();
                        return;
                    }
                }

                for(int i = 0; i < second.length(); i = i + 1)
                {
                    if(!second[i].isDigit())
                    {
                        emit wrongInput();
                        return;
                    }
                }

                if(first[0] == '0' || second[0] == '0')
                {
                    emit wrongInput();
                    return;
                }

                int low = first.toInt(), high = second.toInt();
                if(low > high)
                {
                    emit wrongInput();
                    return;
                }

                QTreeWidgetItem* tempItem;
                for(int i = 0; i < this->topLevelItemCount(); i = i + 1)
                {
                    tempItem = this->topLevelItem(i);
                    if(!(tempItem->isHidden()))
                    {
                        QTime leaveTime = QTime::fromString(tempItem->text(3), "HH:mm");
                        QTime arriveTime = QTime::fromString(tempItem->text(4), "HH:mm");
                        int days = tempItem->text(5).toInt();
                        int minutes = (arriveTime.hour() - leaveTime.hour() + 24 * (days - 1)) * 60 + arriveTime.minute() - leaveTime.minute();

                        if(minutes >= low && minutes <= high)
                        {
                            *numOfResult = *numOfResult + 1;
                        }
                        else
                        {
                            tempItem->setHidden(true);
                        }
                    }
                }
            }
            else
            {
                for(int i = 0; i < inputText.length(); i = i + 1)
                {
                    if(!inputText[i].isDigit())
                    {
                        emit wrongInput();
                        return;
                    }
                }

                if(inputText[0] == '0')
                {
                    emit wrongInput();
                    return;
                }

                QTreeWidgetItem* tempItem;
                for(int i = 0; i < this->topLevelItemCount(); i = i + 1)
                {
                    tempItem = this->topLevelItem(i);
                    if(!(tempItem->isHidden()))
                    {
                        QTime leaveTime = QTime::fromString(tempItem->text(3), "HH:mm");
                        QTime arriveTime = QTime::fromString(tempItem->text(4), "HH:mm");
                        int days = tempItem->text(7).toInt();
                        int minutes = (arriveTime.hour() - leaveTime.hour() + 24 * (days - 1)) * 60 + arriveTime.minute() - leaveTime.minute();

                        if(minutes == inputText.toInt())
                        {
                            *numOfResult = *numOfResult + 1;
                        }
                        else
                        {
                            tempItem->setHidden(true);
                        }
                    }
                }
            }
            emit searchFinished();
            break;
        }
        case 4:case 5:case 6:
        {
            int column = searchType + 2;//调整列

            if(numOfHyphen)
            {
                for(int i = 0; i < first.length(); i = i + 1)
                {
                    if(!first[i].isDigit())
                    {
                        emit wrongInput();
                        return;
                    }
                }

                for(int i = 0; i < second.length(); i = i + 1)
                {
                    if(!second[i].isDigit())
                    {
                        emit wrongInput();
                        return;
                    }
                }

                if(first[0] == '0' || second[0] == '0')
                {
                    emit wrongInput();
                    return;
                }

                int low = first.toInt(), high = second.toInt();
                if(low > high)
                {
                    emit wrongInput();
                    return;
                }

                QTreeWidgetItem* tempItem;
                for(int i = 0; i < this->topLevelItemCount(); i = i + 1)
                {
                    tempItem = this->topLevelItem(i);
                    if(!(tempItem->isHidden()))
                    {
                        int columnData = tempItem->text(column).toInt();
                        if(columnData >= low && columnData <= high)
                        {
                            *numOfResult = *numOfResult + 1;
                        }
                        else
                        {
                            tempItem->setHidden(true);
                        }
                    }
                }
            }
            else
            {
                for(int i = 0; i < inputText.length(); i = i + 1)
                {
                    if(!inputText[i].isDigit())
                    {
                        emit wrongInput();
                        return;
                    }
                }

                if(inputText[0] == '0')
                {
                    emit wrongInput();
                    return;
                }

                QTreeWidgetItem* tempItem;
                for(int i = 0; i < this->topLevelItemCount(); i = i + 1)
                {
                    tempItem = this->topLevelItem(i);
                    if(!(tempItem->isHidden()))
                    {
                        if(tempItem->text(column).toInt() == inputText.toInt())
                        {
                            *numOfResult = *numOfResult + 1;
                        }
                        else
                        {
                            tempItem->setHidden(true);
                        }
                    }
                }
            }
            emit searchFinished();
            break;
        }
        }

    }

    void back()
    {
        QTreeWidgetItem* tempItem;
        for(int i = 0; i < this->topLevelItemCount(); i = i + 1)
        {
            tempItem = this->topLevelItem(i);
            tempItem->setHidden(false);
        }
    }

    void searchNo(QString inputNo)
    {
        train* temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
            if(QString::fromStdString(temp->No) == inputNo)
            {
                result = temp;
                emit searchFound(temp);
                return;
            }
        }
        emit searchNoFound();
    }

    void showResultList()
    {
        this->clear();
        passStation* temp = result->passStations;
        while(temp->next != NULL)
        {
            temp = temp->next;
            QStringList stlStations;
            stlStations << QString::number(temp->no) << QString::fromStdString(temp->station)
                        << temp->arriveTime.toString("HH:mm") << temp->leaveTime.toString("HH:mm")
                        << QString::number(temp->day) << QString::number(temp->kilometers);
            QTreeWidgetItem* newItem = new QTreeWidgetItem(this, stlStations);
            this->addTopLevelItem(newItem);
            setWidthAndAlignCenter(this, newItem);
            stlStations.clear();
        }

        QTreeWidgetItem* tempItem;
        childButtons = new QButtonGroup(this);
        childButtons->setExclusive(true);
        int id = 0;
        for(int i = 0; i < this->topLevelItemCount() - 1; i = i + 1)
        {
            tempItem = this->topLevelItem(i);
            QTreeWidgetItem* newChildItem = new QTreeWidgetItem(tempItem);
            QPushButton* newChildButton[3];
            for(int j = 0; j < 3; j = j + 1)
            {
                newChildButton[j] = new QPushButton(this);
                newChildButton[j]->resize(120, 40);
                newChildButton[j]->setText(editButtons[j]);
                newChildButton[j]->setFont(QFont("Microsoft YaHei UI", 12));
                newChildButton[j]->setCheckable(true);
                this->setItemWidget(newChildItem, j + 1, newChildButton[j]);
                childButtons->addButton(newChildButton[j], id);
                id = id + 1;
            }

            if(i == 0)
            {
                newChildButton[1]->setDisabled(true);
                newChildButton[2]->setDisabled(true);
            }
        }
        connect(childButtons, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), wEdit, &MyWidget::showEditWindow);
        connect(childButtons, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &MyTreeWidget::operateStation);
    }

    void receiveAndShowStation(QString text, int id)
    {
        changingItem->setText(id, text);
        numOfReceived = numOfReceived + 1;
        if(numOfReceived == 7)
        {
            int checkedButton = childButtons->checkedId();
            if(checkedButton % 3 == 0)
            {
                for(int i = (checkedButton / 3) + 1; i < this->topLevelItemCount(); i = i + 1)
                {
                    for(int j = 0; j < 3; j = j + 1)
                    {
                        childButtons->setId(childButtons->button(3 * i + j), 3 * (i + 1) + j);
                    }
                    this->topLevelItem(i)->setText(0, QString::number(i + 2));
                }
                this->insertTopLevelItem((checkedButton / 3) + 1, changingItem);
                for(int i = 0; i < changingItem->columnCount(); i = i  + 1)
                {
                    changingItem->setTextAlignment(i, Qt::AlignCenter);
                }

                QTreeWidgetItem* newChildItem = new QTreeWidgetItem(changingItem);
                QPushButton* newChildButton[3];
                for(int i = 0; i < 3; i = i + 1)
                {
                    newChildButton[i] = new QPushButton(this);
                    newChildButton[i]->resize(120, 40);
                    newChildButton[i]->setText(editButtons[i]);
                    newChildButton[i]->setFont(QFont("Microsoft YaHei UI", 12));
                    newChildButton[i]->setCheckable(true);
                    this->setItemWidget(newChildItem, i + 1, newChildButton[i]);
                    childButtons->addButton(newChildButton[i], checkedButton + 3 + i);
                }
            }

            numOfReceived = 0;
            emit received();
        }
    }

    void changeFirstAndLastStation(QString text, int id)
    {
        switch (id)
        {
        case 1:
        {
            this->topLevelItem(0)->setText(1, text);
            break;
        }
        case 2:
        {
            this->topLevelItem(this->topLevelItemCount() - 1)->setText(1, text);
            break;
        }
        case 3:
        {
            this->topLevelItem(0)->setText(3, text);
            break;
        }
        case 4:
        {
            this->topLevelItem(this->topLevelItemCount() - 1)->setText(2, text);
            break;
        }
        case 5:
        {
            this->topLevelItem(this->topLevelItemCount() - 1)->setText(4, text);
            break;
        }
        case 8:
        {
            this->topLevelItem(this->topLevelItemCount() - 1)->setText(5, text);
            break;
        }
        }
    }

    void operateStation(int id)
    {
        QTreeWidgetItem* item;
        switch (id % 3)
        {
        case 0:
        {
            wEdit->setWindowTitle("添加站点信息");
            QStringList empty;
            empty << QString::number((id / 3) + 2) << "" << "" << "" << "" << "" << "";
            item = new QTreeWidgetItem((QTreeWidget*) (NULL), empty);
            changingItem = item;
            emit sendStation(item);
            empty.clear();
            break;
        }
        case 1:
        {
            wEdit->setWindowTitle("编辑站点信息");
            int index = id / 3;
            item = this->topLevelItem(index);
            changingItem = item;
            emit sendStation(item);
            break;
        }
        case 2:
        {
            deleteBox->show();
            changingItem = this->topLevelItem(id / 3);
            break;
        }
        }

    }
    
    void confirmDeleteStation(QAbstractButton* clickedBtn)
    {
        if(clickedBtn == (QAbstractButton*) deleteStationConfirm)
        {
            int checkedButton = childButtons->checkedId();
            for(int i = 0; i < 3; i = i + 1)
            {
                childButtons->removeButton(childButtons->button(checkedButton - 2 + i));
            }
            for(int i = (checkedButton / 3) + 1; i < this->topLevelItemCount(); i = i + 1)
            {
                this->topLevelItem(i)->setText(0, QString::number(i));
                for(int j = 0; j < 3; j = j + 1)
                {
                    childButtons->setId(childButtons->button(3 * i + j), 3 * (i - 1) + j);
                }
            }
            this->takeTopLevelItem(checkedButton / 3);
            btnSave->setEnabled();
        }
    }
    
    void confirmDeleteTrain(QAbstractButton* clickedBtn)
    {
        if(clickedBtn == (QAbstractButton*) deleteTrainConfirm)
        {
            if(QString::fromStdString(delResult->No) == QString::fromStdString(result->No))
            {
                emit conflictDelNumber();
                return;
            }

            for(int i = 0; i < this->topLevelItemCount(); i = i + 1)
            {
                if(this->topLevelItem(i)->text(0) == QString::fromStdString(delResult->No))
                {
                    this->takeTopLevelItem(i);
                    *total = *total - 1;
                    emit trainDeleted();
                    break;
                }
            }

            passStation* p = delResult->passStations, * q = delResult->passStations->next;
            while(q != NULL)
            {
                delete p;
                p = q;
                q = q->next;
            }

            train* pre = head;
            while(pre->next != NULL && pre->next != delResult)
            {
                pre = pre->next;
            }
            pre->next = pre->next->next;
            delete delResult;
        }
    }

    void checkStation()
    {
        QTreeWidgetItem* tempItem[2];
        for(int i = 0; i < this->topLevelItemCount(); i = i + 1)
        {
            tempItem[0] = this->topLevelItem(i);
            if(tempItem[0]->text(0) != QString::number(i + 1))
            {
                passedSection = 0;
                emit wrongInput();
                return;
            }
            for(int j = i + 1; j < this->topLevelItemCount(); j = j + 1)
            {
                tempItem[1] = this->topLevelItem(j);
                if(tempItem[0]->text(1) == tempItem[1]->text(1))
                {
                    passedSection = 0;
                    emit wrongInput();
                    return;
                }
            }
        }

        for(int i = 0; i < this->topLevelItemCount() - 1; i = i + 1)
        {
            tempItem[0] = this->topLevelItem(i);
            tempItem[1] = this->topLevelItem(i + 1);
            if((tempItem[0]->text(4).toInt() > tempItem[1]->text(4).toInt()) ||
               (tempItem[0]->text(5).toInt() >= tempItem[1]->text(5).toInt()))
            {
                passedSection = 0;
                emit wrongInput();
                return;
            }
        }

        QDateTime tempTime[2];
        for(int i = 1; i < this->topLevelItemCount(); i = i + 1)
        {
            tempItem[0] = this->topLevelItem(i - 1);
            tempItem[1] = this->topLevelItem(i);
            tempTime[0] = QDateTime::fromString(("01:" + tempItem[0]->text(3)), "dd:HH:mm");
            tempTime[1] = QDateTime::fromString(("01:" + tempItem[1]->text(2)), "dd:HH:mm");
            tempTime[0] = tempTime[0].addDays(tempItem[0]->text(4).toInt() - 1);
            tempTime[1] = tempTime[1].addDays(tempItem[1]->text(4).toInt() - 1);
            if(tempTime[0] >= tempTime[1])
            {
                passedSection = 0;
                emit wrongInput();
                return;
            }
        }

        for(int i = 1; i < this->topLevelItemCount() - 1; i = i + 1)
        {
            tempItem[0] = this->topLevelItem(i);
            tempTime[0] = QDateTime::fromString(("01:" + tempItem[0]->text(2)), "dd:HH:mm");
            tempTime[1] = QDateTime::fromString(("01:" + tempItem[0]->text(3)), "dd:HH:mm");
            tempTime[0] = tempTime[0].addDays(tempItem[0]->text(4).toInt() - 1);
            tempTime[1] = tempTime[1].addDays(tempItem[0]->text(4).toInt() - 1);
            if(tempTime[0] >= tempTime[1])
            {
                passedSection = 0;
                emit wrongInput();
                return;
            }
        }

        emit checkStationSuccess();
    }

    void checkAll()
    {
        passedSection = passedSection + 1;
        if(passedSection == 2)
        {
            emit checkAllSuccess();
            passedSection = 0;
        }
    }

    void setTrain(QString text, int id)
    {
        tempTrain->setText(id, text);
        setItem = setItem + 1;
        if(setItem == 10)
        {
            for(int i = 0; i < this->topLevelItemCount(); i = i + 1)
            {
                if(this->topLevelItem(i)->text(0) == QString::fromStdString(result->No))
                {
                    changingItem = this->topLevelItem(i);
                    break;
                }
            }

            for(int i = 0; i < this->columnCount(); i = i + 1)
            {
                changingItem->setText(i, tempTrain->text(i));
                changingItem->setBackgroundColor(i, changedItemColor);
            }

            delete tempTrain;
            tempTrain = new QTreeWidgetItem((QTreeWidget*) (NULL));

            result->No = changingItem->text(0).toStdString();
            result->departure = changingItem->text(1).toStdString();
            result->destination = changingItem->text(2).toStdString();
            result->LeaveTime = QTime::fromString(changingItem->text(3), "HH:mm");
            result->ArriveTime = QTime::fromString(changingItem->text(4), "HH:mm");
            result->days = changingItem->text(5).toInt();
            result->priceSit = changingItem->text(6).toInt();
            result->priceSleep = changingItem->text(7).toInt();
            result->distance = changingItem->text(8).toInt();
            result->Note = changingItem->text(9).toStdString();

            setItem = 0;
            emit trainIsSet();
        }
    }

    void addNewTrain(QString text, int id)
    {
        newTrain->setText(id, text);
        setItem = setItem + 1;
        if(setItem == 10)
        {
            QDateTime tempTime[2];
            tempTime[0] = QDateTime::fromString(("01:" + newTrain->text(3)), "dd:HH:mm");
            tempTime[1] = QDateTime::fromString(("01:" + newTrain->text(4)), "dd:HH:mm");
            tempTime[1] = tempTime[1].addDays(newTrain->text(5).toInt() - 1);
            if(tempTime[0] >= tempTime[1])
            {
                setItem = 0;
                emit reverseInput();
                delete newTrain;
                newTrain = new QTreeWidgetItem((QTreeWidget*) (NULL));
                return;
            }

            this->addTopLevelItem(newTrain);
            QStringList stlStationHeader;
            stlStationHeader << "站次" << "站名"
                             << "到达时间" << "开车时间"
                             << "天数" << "里程" << "备注";
            QTreeWidgetItem* newChildItem = new QTreeWidgetItem(newTrain);
            QTreeWidget* newChildList = new QTreeWidget(this);
            newChildList->setColumnCount(7);
            newChildList->setFont(QFont("Microsoft YaHei UI", 12));
            newChildList->setHeaderLabels(stlStationHeader);
            this->setItemWidget(newChildItem, 0, newChildList);
            this->setFirstItemColumnSpanned(newChildItem, true);

            QTreeWidgetItem* newChildListItem[2];
            newChildListItem[0] = new QTreeWidgetItem(newChildList);
            newChildListItem[0]->setText(0, "1");
            newChildListItem[0]->setText(1, newTrain->text(1));
            newChildListItem[0]->setText(2, "");
            newChildListItem[0]->setText(3, newTrain->text(3));
            newChildListItem[0]->setText(4, "1");
            newChildListItem[0]->setText(5, "0");
            newChildListItem[0]->setText(6, newTrain->text(9));
            newChildList->addTopLevelItem(newChildListItem[0]);
            newChildListItem[1] = new QTreeWidgetItem(newChildList);
            newChildListItem[1]->setText(0, "2");
            newChildListItem[1]->setText(1, newTrain->text(2));
            newChildListItem[1]->setText(2, newTrain->text(4));
            newChildListItem[1]->setText(3, "");
            newChildListItem[1]->setText(4, newTrain->text(5));
            newChildListItem[1]->setText(5, newTrain->text(8));
            newChildListItem[1]->setText(6, newTrain->text(9));
            newChildList->addTopLevelItem(newChildListItem[1]);

            addTrain->No = newTrain->text(0).toStdString();
            addTrain->departure = newTrain->text(1).toStdString();
            addTrain->destination = newTrain->text(2).toStdString();
            addTrain->LeaveTime = QTime::fromString(newTrain->text(3), "HH:mm");
            addTrain->ArriveTime = QTime::fromString(newTrain->text(4), "HH:mm");
            addTrain->days = newTrain->text(5).toInt();
            addTrain->priceSit = newTrain->text(6).toInt();
            addTrain->priceSleep = newTrain->text(7).toInt();
            addTrain->distance = newTrain->text(8).toInt();
            addTrain->Note = newTrain->text(9).toStdString();
            addTrain->numOfPasses = 2;

            passStation* tempStation = new passStation;
            addTrain->passStations = tempStation;
            tempStation->next = new passStation;
            tempStation = tempStation->next;

            tempStation->no = 1;
            tempStation->station = newChildListItem[0]->text(1).toStdString();
            tempStation->arriveTime = QTime::fromString(newChildListItem[0]->text(2), "HH:mm");
            tempStation->leaveTime = QTime::fromString(newChildListItem[0]->text(3), "HH:mm");
            tempStation->day = 1;
            tempStation->kilometers = 0;
            tempStation->note = newChildListItem[0]->text(6).toStdString();
            tempStation->next = new passStation;
            tempStation = tempStation->next;

            tempStation->no = 2;
            tempStation->station = newChildListItem[1]->text(1).toStdString();
            tempStation->arriveTime = QTime::fromString(newChildListItem[1]->text(2), "HH:mm");
            tempStation->leaveTime = QTime::fromString(newChildListItem[1]->text(3), "HH:mm");
            tempStation->day = newChildListItem[1]->text(4).toInt();
            tempStation->kilometers = newChildListItem[1]->text(5).toInt();
            tempStation->note = newChildListItem[1]->text(6).toStdString();
            tempStation->next = NULL;

            for(int i = 0; i < this->columnCount(); i = i + 1)
            {
                newTrain->setTextAlignment(i, Qt::AlignCenter);
                newTrain->setBackgroundColor(i, changedItemColor);
            }
            for(int i = 0; i < newChildList->columnCount(); i = i + 1)
            {
                newChildList->setColumnWidth(i, 140);
                newChildListItem[0]->setTextAlignment(i, Qt::AlignCenter);
                newChildListItem[1]->setTextAlignment(i, Qt::AlignCenter);
            }

            train* lastTrain = head;
            while(lastTrain->next != NULL)
            {
                lastTrain = lastTrain->next;
            }
            lastTrain->next = addTrain;
            addTrain->next = NULL;

            *total = *total + 1;
            train* tempTrain = new train;
            addTrain = tempTrain;
            setItem = 0;
            QTreeWidgetItem* tempItem = new QTreeWidgetItem((QTreeWidget*) (NULL));
            newTrain = tempItem;
            emit trainCreated();
            this->back();
        }
    }

    void emitList()
    {
        emit sendList(this);
    }

    void setStation(MyTreeWidget* lstStation)
    {
        passStation* temp = result->passStations->next;
        passStation* tempNext = temp->next;
        while(tempNext != NULL)
        {
            delete temp;
            temp = tempNext;
            tempNext = tempNext->next;
        }

        QTreeWidget* changingWidget = (QTreeWidget*) (QTreeWidget::itemWidget(changingItem->child(0), 0));
        changingWidget->clear();

        QTreeWidgetItem* tempItem; temp = result->passStations;
        for(int i = 0; i < lstStation->topLevelItemCount(); i = i + 1)
        {
            tempItem = lstStation->topLevelItem(i);
            QTreeWidgetItem* newChildListItem = new QTreeWidgetItem(changingWidget);
            for(int j = 0; j < changingWidget->columnCount(); j = j + 1)
            {
                newChildListItem->setText(j, tempItem->text(j));
                changingWidget->setColumnWidth(i, 140);
                newChildListItem->setTextAlignment(j, Qt::AlignCenter);
            }
            changingWidget->addTopLevelItem(newChildListItem);

            temp->next = new passStation;
            temp = temp->next;
            temp->no = tempItem->text(0).toInt();
            temp->station = tempItem->text(1).toStdString();
            temp->arriveTime = QTime::fromString(tempItem->text(2), "HH:mm");
            temp->leaveTime = QTime::fromString(tempItem->text(3), "HH:mm");
            temp->day = tempItem->text(4).toInt();
            temp->kilometers = tempItem->text(5).toInt();
            temp->note = tempItem->text(6).toStdString();
        }
        temp->next = NULL;
        result->numOfPasses = lstStation->topLevelItemCount();
    }

    void searchDel(QString inputNo)
    {
        train* temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
            if(QString::fromStdString(temp->No) == inputNo)
            {
                delResult = temp;
                emit delFound(temp);
                return;
            }
        }
        emit delNoFound();
    }

    void setEnabled()
    {
        this->QTreeWidget::setEnabled(true);
    }

    void setDisabled()
    {
        this->QTreeWidget::setDisabled(true);
    }
};
train* MyTreeWidget::head = NULL, * MyTreeWidget::result = NULL, * MyTreeWidget::delResult = NULL, * MyTreeWidget::addTrain = NULL;
QTreeWidgetItem* MyTreeWidget::tempTrain = NULL, * MyTreeWidget::newTrain = NULL;

class MyLineEdit:public QLineEdit
{
    Q_OBJECT

signals:
    void isEmpty(bool empty);
    void sendText(QString text);
    void sendTextNo(QString textNo);
    void sendTextAndId(QString text, int index);
    void sendEditTextAndId(QString text, int index);
    void wrongInput();
    void conflictInput();
    void checkPassed();

public:
    bool edit;
    int id;
    static int passed1, passed2;
    static MyTreeWidget* list;

    MyLineEdit(QWidget* parent = Q_NULLPTR):QLineEdit(parent)
    {
        edit = false;
    }

public slots:
    void emitIsEmpty()
    {
        emit isEmpty(this->text().isEmpty());
    }

    void emitText()
    {
        emit sendText(this->text());
    }

    void emitTextNo()
    {
        if(this->text().length() != 5)
        {
            emit wrongInput();
            return;
        }
        else
        {
            if(!(this->text())[0].isLetter())
            {
                emit wrongInput();
                return;
            }

            for(int i = 1; i < 5; i = i + 1)
            {
                if(!(this->text())[i].isDigit())
                {
                    emit wrongInput();
                    return;
                }
            }
        }

        emit sendTextNo(this->text());
    }

    void emitCheckPassed1()
    {
        if(passed1 == 10)
        {
            emit checkPassed();
            passed1 = 0;
        }
    }

    void checkTextAndId1()
    {
        switch (id)
        {
        case 0:
        {
            if(this->text().length() != 5)
            {
                emit wrongInput();
                passed1 = 0;
                return;
            }
            else
            {
                if(!(this->text())[0].isLetter())
                {
                    emit wrongInput();
                    passed1 = 0;
                    return;
                }

                for(int i = 1; i < 5; i = i + 1)
                {
                    if(!(this->text())[i].isDigit())
                    {
                        emit wrongInput();
                        passed1 = 0;
                        return;
                    }
                }
            }

            for(int i = 0; i < list->topLevelItemCount(); i = i + 1)
            {
                if(list->topLevelItem(i)->text(0) == this->text())
                {
                    if(!edit)
                    {
                        emit conflictInput();
                        passed1 = 0;
                        return;
                    }
                    else
                    {
                        if(QString::fromStdString(MyTreeWidget::result->No) != this->text())
                        {
                            emit conflictInput();
                            passed1 = 0;
                            return;
                        }
                    }
                }
            }

            passed1 = passed1 + 1;
            break;
        }
        case 1:case 2:
        {
            if(!this->text().length())
            {
                emit wrongInput();
                passed1 = 0;
                return;
            }
        }
        case 9:
        {
            passed1 = passed1 + 1;
            break;
        }
        case 3:case 4:
        {
            if(this->text().length() != 5 ||
               !(this->text()[0].isDigit() && this->text()[1].isDigit() && this->text()[2] == ':' && this->text()[3].isDigit() && this->text()[4].isDigit()))
            {
                emit wrongInput();
                passed1 = 0;
                return;
            }
            else
            {
                QStringList tempTime = this->text().split(':');
                QString tempHour = tempTime.takeFirst();
                QString tempMin = tempTime.takeFirst();
                if(tempHour >= "24" || tempMin >= "60")
                {
                    emit wrongInput();
                    passed1 = 0;
                    return;
                }
            }

            passed1 = passed1 + 1;
            break;
        }
        case 5:case 6:case 7:case 8:
        {
            for(int i = 0; i < this->text().length(); i = i + 1)
            {
                if(!(this->text()[i].isDigit()))
                {
                    passed1 = 0;
                    emit wrongInput();
                    return;
                }
            }

            if(this->text()[0] == '0')
            {
                passed1 = 0;
                emit wrongInput();
                return;
            }

            passed1 = passed1 + 1;
            break;
        }
        }

        emitCheckPassed1();
    }

    void emitCheckPassed2()
    {
        if(passed2 == 7)
        {
            emit checkPassed();
            passed2 = 0;
        }
    }

    void checkTextAndId2()
    {
        switch (id)
        {
        case 0:case 4:case 5:
        {
            for(int i = 0; i < this->text().length(); i = i + 1)
            {
                if(!(this->text())[i].isDigit())
                {
                    emit wrongInput();
                    passed2 = 0;
                    return;
                }
            }

            if(this->text()[0] == '0')
            {
                emit wrongInput();
                passed2 = 0;
                return;
            }

            passed2 = passed2 + 1;
            break;
        }
        case 1:
        {
            if(!this->text().length())
            {
                emit wrongInput();
                passed2 = 0;
                return;
            }
        }
        case 6:
        {
            passed2 = passed2 + 1;
            break;
        }
        case 2:case 3:
        {
            if(this->text().length() != 5 ||
               !(this->text()[0].isDigit() && this->text()[1].isDigit() && this->text()[2] == ':' && this->text()[3].isDigit() && this->text()[4].isDigit()))
            {
                emit wrongInput();
                passed2 = 0;
                return;
            }
            else
            {
                QStringList tempTime = this->text().split(':');
                QString tempHour = tempTime.takeFirst();
                QString tempMin = tempTime.takeFirst();
                if(tempHour >= "24" || tempMin >= "60")
                {
                    emit wrongInput();
                    passed2 = 0;
                    return;
                }
            }

            passed2 = passed2 + 1;
            break;
        }
        }

        emitCheckPassed2();
    }

    void emitTextAndId()
    {
        sendTextAndId(this->text(), id);
    }

    void emitEditTextAndId()
    {
        sendEditTextAndId(this->text(), id);
    }

    void setHidden()
    {
        this->QLineEdit::setHidden(true);
    }

    void setEnabled()
    {
        this->QLineEdit::setEnabled(true);
    }

    void setDisabled()
    {
        this->QLineEdit::setDisabled(true);
    }
    
    void showInfo(train* result)
    {
        switch (id)
        {
        case 0:this->setText(QString::fromStdString(result->No)); break;
        case 1:this->setText(QString::fromStdString(result->departure)); break;
        case 2:this->setText(QString::fromStdString(result->destination)); break;
        case 3:this->setText(result->LeaveTime.toString("HH:mm")); break;
        case 4:this->setText(result->ArriveTime.toString("HH:mm")); break;
        case 5:this->setText(QString::number(result->days)); break;
        case 6:this->setText(QString::number(result->priceSit)); break;
        case 7:this->setText(QString::number(result->priceSleep)); break;
        case 8:this->setText(QString::number(result->distance)); break;
        case 9:this->setText(QString::fromStdString(result->Note)); break;
        }
    }

    void showStation(QTreeWidgetItem* item)
    {
        this->setText(item->text(id));
    }
};
int MyLineEdit::passed1 = 0, MyLineEdit::passed2 = 0;
MyTreeWidget* MyLineEdit::list = NULL;

class MyFrame:public QFrame
{
    Q_OBJECT

public:
    MyFrame(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags()):QFrame(parent, f)
    {

    }


public slots:
    void setHidden()
    {
        this->QFrame::setHidden(true);
    }

};

void loadData(train*& trains, int total, std::ifstream& infile, QProgressBar* pgbLoad, double& progress)
{
    train* p = trains, *q;
    int LeaveHour, LeaveMin, ArriveHour, ArriveMin, arriveHour, arriveMin, leaveHour, leaveMin;
    for(int i = 0; i < total; i = i + 1)
    {
        q = new train;
        infile >> q->No >> q->departure >> q->destination
                >> LeaveHour >> LeaveMin >> ArriveHour >> ArriveMin
                >> q->numOfPasses >> q->priceSit >> q->priceSleep
                >> q->days >> q->distance;
        q->LeaveTime.setHMS(LeaveHour, LeaveMin, 0);
        q->ArriveTime.setHMS(ArriveHour, ArriveMin, 0);

        q->passStations = new passStation;
        passStation* r = q->passStations, *s;
        for(int j = 0; j < q->numOfPasses; j = j + 1)
        {
            s = new passStation;
            infile >> s->no >> s->station
                    >> arriveHour >> arriveMin >> leaveHour >> leaveMin
                    >> s->day >> s->kilometers;
            s->arriveTime.setHMS(arriveHour, arriveMin, 0);
            s->leaveTime.setHMS(leaveHour, leaveMin, 0);
            r->next = s;
            r = s;
        }
        r->next = NULL;
        p->next = q;
        p = q;

        pgbLoad->setValue(pgbLoad->value() + 1);
        progress = double(pgbLoad->value() - pgbLoad->minimum()) * 100 / double(pgbLoad->maximum() - pgbLoad->minimum());
        pgbLoad->setFormat("车次信息加载中……" + QString::number(progress, 'f', 1) + "%");
    }
    p->next = NULL;
}

void createTree(train* trains, QProgressBar* pgbLoad, double& progress, MyTreeWidget* lstTrains, MyWidget* w)
{
    train* Temp = trains; QStringList stlTrain, stlStations;
    while(Temp->next != NULL)
    {
        Temp = Temp->next;
        stlTrain << QString::fromStdString(Temp->No) << QString::fromStdString(Temp->departure) << QString::fromStdString(Temp->destination)
                 << Temp->LeaveTime.toString("HH:mm") << Temp->ArriveTime.toString("HH:mm") << QString::number(Temp->days)
                 << QString::number(Temp->priceSit) << QString::number(Temp->priceSleep);
        QTreeWidgetItem* newItem = new QTreeWidgetItem(lstTrains, stlTrain);
        newItem->setData(8, 0, Temp->distance);
        setWidthAndAlignCenter(lstTrains, newItem);
        lstTrains->addTopLevelItem(newItem);
        stlTrain.clear();
        
        QTreeWidgetItem* newChildItem = new QTreeWidgetItem(newItem);
        newChildItem->setSizeHint(0, QSize(1000, 25 + 35 * Temp->numOfPasses));
        QStringList stlStationHeader;
        stlStationHeader << "站次" << "站名"
                         << "到达时间" << "开车时间"
                         << "天数" << "里程" << "备注";
        QTreeWidget* newChildList = new QTreeWidget(w);
        newChildList->resize(1000, 50 * Temp->numOfPasses);
        newChildList->setColumnCount(7);
        newChildList->setFont(QFont("Microsoft YaHei UI", 12));
        newChildList->setHeaderLabels(stlStationHeader);
        lstTrains->setItemWidget(newChildItem, 0, newChildList);
        lstTrains->setFirstItemColumnSpanned(newChildItem, true);

        passStation* temp = Temp->passStations;
        while(temp->next != NULL)
        {
            temp = temp->next;
            stlStations << QString::number(temp->no) << QString::fromStdString(temp->station)
                        << temp->arriveTime.toString("HH:mm") << temp->leaveTime.toString("HH:mm")
                        << QString::number(temp->day) << QString::number(temp->kilometers);
            QTreeWidgetItem* newChildListItem = new QTreeWidgetItem(newChildList, stlStations);
            setWidthAndAlignCenter(newChildList, newChildListItem);
            newChildList->addTopLevelItem(newChildListItem);
            stlStations.clear();
        }

        pgbLoad->setValue(pgbLoad->value() + 1);
        progress = double(pgbLoad->value() - pgbLoad->minimum()) * 100 / double(pgbLoad->maximum() - pgbLoad->minimum());
        pgbLoad->setFormat("车次信息加载中……" + QString::number(progress, 'f', 1) + "%");
    }
}

void loadHelp(MyTreeWidget* lstHelp)
{
    std::ifstream infile("help.txt");
    int numOfHelp;
    infile >> numOfHelp;
    for(int i = 0; i < numOfHelp; i = i + 1)
    {
        QTreeWidgetItem* helpItem = new QTreeWidgetItem(lstHelp);
        std::string helpString;
        infile >> helpString;
        helpItem->setText(0, QString::fromStdString(helpString));
        QTreeWidgetItem* answerItem = new QTreeWidgetItem(helpItem);
        QLabel* lblAnswer = new QLabel(lstHelp);
        infile >> helpString;
        lblAnswer->setText(QString::fromStdString(helpString));
        lblAnswer->setWordWrap(true);
        lstHelp->setItemWidget(answerItem, 0, lblAnswer);
        helpItem->setExpanded(true);
    }
    infile.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.showFullScreen();
    w.setWindowTitle("12307客运列车信息管理系统");
    w.setPalette(QPalette(Qt::white));
    w.setWindowIcon(QIcon(":/ico/PTM.ico"));

    QMessageBox exitBox;
    exitBox.setWindowTitle("提示");
    exitBox.setText("您确定要退出吗？");
    exitBox.setFont(QFont("Microsoft YaHei UI", 10));
    w.agree = exitBox.addButton("确定", QMessageBox::AcceptRole);
    exitBox.addButton("取消", QMessageBox::RejectRole);
    exitBox.setWindowIcon(QIcon(":/ico/PTM.ico"));
    exitBox.setIcon(QMessageBox::Question);
    exitBox.setWindowModality(Qt::ApplicationModal);//直到关闭提示框才使主窗口恢复焦点
    QObject::connect(&exitBox, &QMessageBox::buttonClicked, &w, &MyWidget::confirmExit);

    MyPushButton btnExit(NULL, &w);
    btnExit.resize(145, 145);
    btnExit.move(1750, 22);
    btnExit.setFlat(true);
    btnExit.setIconSize(QSize(145, 145));
    btnExit.setStyleSheet("QPushButton:!hover{border-image:url(:/new/close/exit0.jpg)} "
                          "QPushButton:hover{border-image:url(:/new/close/exit1.jpg)}");
    btnExit.show();
    btnExit.setCursor(QCursor(Qt::PointingHandCursor));
    QObject::connect(&btnExit, &MyPushButton::clicked, &exitBox, &QMessageBox::show);

    QMessageBox wrongBox;
    wrongBox.setWindowTitle("错误");
    wrongBox.setText("数据文件打开失败，请检查数据文件！点击\"确认\"关闭系统。");
    wrongBox.addButton("确定", QMessageBox::AcceptRole);
    wrongBox.setFont(QFont("Microsoft YaHei UI", 10));
    wrongBox.setWindowIcon(QIcon(":/ico/PTM.ico"));
    wrongBox.setIcon(QMessageBox::Critical);
    wrongBox.setWindowModality(Qt::ApplicationModal);//直到关闭提示框才使主窗口恢复焦点

    int total = 0;
    w.total = &total;
    std::ifstream infile("data.txt");
    if(!infile.is_open())
    {
        wrongBox.show();
        w.close();
        return a.exec();
    }
    infile >> total;

    QProgressBar* pgbLoad = new QProgressBar(&w);
    pgbLoad->resize(1200, 60);
    pgbLoad->move(400, 510);
    pgbLoad->setMinimum(0);
    pgbLoad->setMaximum(2 * total);
    pgbLoad->setValue(0);
    double progress = double(pgbLoad->value() - pgbLoad->minimum()) * 100 / (pgbLoad->maximum() - pgbLoad->minimum());
    pgbLoad->setFormat("车次信息加载中……" + QString::number(progress, 'f', 1) + "%");
    pgbLoad->setFont(QFont("Microsoft YaHei UI", 16));
    pgbLoad->setStyleSheet("QProgressBar{background:white; color:black;} QProgressBar::chunk{background:#327bff}");
    pgbLoad->setAlignment(Qt::AlignCenter);
    pgbLoad->show();

    train* trains = new train;
    trains->next = NULL;
    loadData(trains, total, infile, pgbLoad, progress);
    w.list = trains;
    infile.close();

    MyPushButton* btnMenu[4];
    QButtonGroup* mnu = new QButtonGroup;
    mnu->setExclusive(true);
    for(int i = 0; i < 4; i = i + 1)
    {
        btnMenu[i] = new MyPushButton(mnuText[i], &w);
        mnu->addButton(btnMenu[i], i);
        btnMenu[i]->resize(350, 110);
        btnMenu[i]->move(0, 188 + i * 110);
        btnMenu[i]->setFlat(true);
        btnMenu[i]->setFont(QFont("Microsoft YaHei UI", 18));
        btnMenu[i]->setCheckable(true);
        btnMenu[i]->setStyleSheet(mnuStyle);
        btnMenu[i]->show();
    }

    MyLabel lblSysTime(&w);
    lblSysTime.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    lblSysTime.move(5, 1033);
    lblSysTime.resize(500, 47);
    lblSysTime.setFont(QFont("Microsoft YaHei UI", 12));
    lblSysTime.show();
    QTimer *timer = new QTimer(&w);
    timer->start(500);
    QObject::connect(timer, &QTimer::timeout, &lblSysTime, &MyLabel::updateTime);

    MyLabel lblTotal(&w);
    lblTotal.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    lblTotal.move(500, 1033);
    lblTotal.resize(300, 47);
    lblTotal.setFont(QFont("Microsoft YaHei UI", 12));
    lblTotal.setText("现有车次信息总数：" + QString::number(total));
    lblTotal.show();
    lblTotal.total = &total;

    QStringList stlHeader;
    stlHeader << "车次" << "始发站" << "终点站"
           << "始发时间" << "终到时间" << "天数"
           << "硬座票价" << "卧铺票价" << "里程"
           << "备注";
    MyTreeWidget* lstTrains = new MyTreeWidget(&w);
    lstTrains->resize(1567, 732);
    lstTrains->move(353, 298);
    lstTrains->setColumnCount(10);
    lstTrains->setHeaderLabels(stlHeader);
    lstTrains->setFont(QFont("Microsoft YaHei UI", 14));
    lstTrains->setUniformRowHeights(false);
    int numOfResult = 0;
    lstTrains->numOfResult = &numOfResult;
    lstTrains->total = &total;

    createTree(trains, pgbLoad, progress, lstTrains, &w);
    lstTrains->setSortingEnabled(true);
    MyTreeWidget::head = trains;
    delete(pgbLoad);

    MyLineEdit* txtSearch = new MyLineEdit(&w);
    txtSearch->resize(440, 60);
    txtSearch->move(1260, 215);
    txtSearch->setFont(QFont("Microsoft YaHei UI", 16));
    txtSearch->setClearButtonEnabled(true);
    txtSearch->setMaxLength(40);

    MyPushButton* btnSearch = new MyPushButton(&w);
    btnSearch->resize(170, 60);
    btnSearch->move(1710, 215);
    btnSearch->setIcon(QIcon(":/new/search/btnSearch.png"));
    btnSearch->setIconSize(QSize(25, 25));
    btnSearch->setFont(QFont("Microsoft YaHei UI", 12));

    MyPushButton* btnSwitch = new MyPushButton(&w);
    btnSwitch->resize(20, 60);
    btnSwitch->move(1880, 215);
    btnSwitch->actSearchGroup = new QActionGroup(btnSwitch);
    btnSwitch->actSearchGroup->setExclusive(true);
    lstTrains->actSearchGroup = btnSwitch->actSearchGroup;

    QMenu* mnuSearch = new QMenu(btnSwitch);
    mnuSearch->setFont(QFont("Microsoft YaHei UI", 10));
    QAction* actSearch[7];
    for(int i = 0; i < 7; i = i + 1)
    {
        actSearch[i] = new QAction(mnuSearch);
        actSearch[i]->setText(searchMethod[i]);
        actSearch[i]->setCheckable(true);
        mnuSearch->addAction(actSearch[i]);
        btnSwitch->actSearchGroup->addAction(actSearch[i]);
    }
    btnSwitch->setMenu(mnuSearch);

    btnSearch->actSearchGroup = btnSwitch->actSearchGroup;
    lstTrains->actSearch = (QAction**)(&actSearch);
    QObject::connect(btnSwitch->actSearchGroup, QActionGroup::triggered, btnSearch, MyPushButton::changeText);
    actSearch[0]->trigger();

    btnSearch->QPushButton::setEnabled(false);
    btnSwitch->QPushButton::setEnabled(false);
    QObject::connect(txtSearch, &MyLineEdit::textChanged, txtSearch, &MyLineEdit::emitIsEmpty);
    QObject::connect(txtSearch, &MyLineEdit::isEmpty, btnSearch, &MyPushButton::changeState);
    QObject::connect(txtSearch, &MyLineEdit::isEmpty, btnSwitch, &MyPushButton::changeState);

    MyPushButton* btnBack = new MyPushButton("返回", &w);
    btnBack->resize(120, 60);
    btnBack->move(375, 215);
    btnBack->setFont(QFont("Microsoft YaHei UI", 14));
    btnBack->setIcon(QIcon(":/new/back/btnBack.png"));
    btnBack->setIconSize(QSize(20, 20));
    btnBack->setDisabled();

    MyLabel* lblSearch = new MyLabel(&w);
    lblSearch->resize(725, 100);
    lblSearch->move(520, 195);
    lblSearch->setText(instruct[0]);
    lblSearch->setFont(QFont("Microsoft YaHei UI", 12));
    lblSearch->setWordWrap(true);
    lblSearch->numOfResult = &numOfResult;

    QMessageBox wrongInputBox[3];
    wrongInputBox[0].setWindowTitle("输入错误");
    wrongInputBox[0].setText("请重新检查输入内容，尤其注意以下事项：\n"
                             "一、车次和时刻应尽量输入完整，例如G2922、13:50。\n"
                             "二、不应输入两个以上的“-”符号或任何数量的空格。\n"
                             "三、检查搜索类别是否正确。");
    wrongInputBox[0].addButton("确定", QMessageBox::AcceptRole);
    wrongInputBox[0].setFont(QFont("Microsoft YaHei UI", 10));
    wrongInputBox[0].setWindowIcon(QIcon(":/ico/PTM.ico"));
    wrongInputBox[0].setIcon(QMessageBox::Critical);
    wrongInputBox[0].setWindowModality(Qt::ApplicationModal);//直到关闭提示框才使主窗口恢复焦点

    QObject::connect(btnSearch, &MyPushButton::clicked, txtSearch, &MyLineEdit::emitText);
    QObject::connect(txtSearch, &MyLineEdit::returnPressed, txtSearch, &MyLineEdit::emitText);
    QObject::connect(lstTrains, &MyTreeWidget::wrongInput, &wrongInputBox[0], &QMessageBox::show);
    QObject::connect(txtSearch, &MyLineEdit::sendText, lstTrains, &MyTreeWidget::searchAndShowResult);
    QObject::connect(lstTrains, &MyTreeWidget::searchFinished, lblSearch, &MyLabel::changeText);
    QObject::connect(lstTrains, &MyTreeWidget::searchFinished, btnBack, &MyPushButton::setEnabled);
    QObject::connect(btnBack, &MyPushButton::clicked, lstTrains, &MyTreeWidget::back);
    QObject::connect(btnBack, &MyPushButton::clicked, btnBack, &MyPushButton::setDisabled);
    QObject::connect(btnBack, &MyPushButton::clicked, lblSearch, &MyLabel::back);

    MyLabel* lblEdit = new MyLabel(&w);
    lblEdit->resize(440, 45);
    lblEdit->move(370, 185);
    lblEdit->setText(instruct[1]);
    lblEdit->setFont(QFont("Microsoft YaHei UI", 14));
    lblEdit->setWordWrap(true);

    MyLineEdit* txtEdit = new MyLineEdit(&w);
    txtEdit->resize(440, 60);
    txtEdit->move(370, 230);
    txtEdit->setFont(QFont("Microsoft YaHei UI", 16));
    txtEdit->setClearButtonEnabled(true);
    txtEdit->setMaxLength(40);

    MyPushButton* btnEdit = new MyPushButton(&w);
    btnEdit->resize(130, 60);
    btnEdit->move(815, 230);
    btnEdit->setText("查找并编辑");
    btnEdit->setFont(QFont("Microsoft YaHei UI", 12));
    btnEdit->setDisabled();

    MyLabel* lblSave = new MyLabel(&w);
    lblSave->resize(600, 60);
    lblSave->move(1050, 210);
    lblSave->setText(instruct[2]);
    lblSave->setFont(QFont("Microsoft YaHei UI", 14));
    lblSave->setWordWrap(true);

    wrongInputBox[1].setWindowTitle("输入错误");
    wrongInputBox[1].setText("请重新检查输入内容，尤其注意输入车次和时刻时应尽量输入完整，例如G2922、13:50。");
    wrongInputBox[1].addButton("确定", QMessageBox::AcceptRole);
    wrongInputBox[1].setFont(QFont("Microsoft YaHei UI", 10));
    wrongInputBox[1].setWindowIcon(QIcon(":/ico/PTM.ico"));
    wrongInputBox[1].setIcon(QMessageBox::Critical);
    wrongInputBox[1].setWindowModality(Qt::ApplicationModal);//直到关闭提示框才使主窗口恢复焦点

    MyPushButton* btnSave = new MyPushButton(&w);
    btnSave->resize(200, 85);
    btnSave->move(1700, 200);
    btnSave->setText("保存修改");
    btnSave->setFont(QFont("Microsoft YaHei UI", 16));
    btnSave->setIcon(QIcon(":/new/save/btnSave.png"));
    btnSave->setIconSize(QSize(30, 30));
    btnSave->QPushButton::setDisabled(true);

    MyFrame* lneEdit1 = new MyFrame(&w);
    lneEdit1->move(353, 298);
    lneEdit1->resize(1567, 3);
    lneEdit1->setLineWidth(3);
    lneEdit1->setFrameShape(QFrame::HLine);
    lneEdit1->setFrameShadow(QFrame::Plain);
    lneEdit1->setStyleSheet("color:#0076e4");

    QMessageBox noFoundBox;
    noFoundBox.setWindowTitle("未找到车次");
    noFoundBox.setText("没有找到该车次的信息，请重新输入！");
    noFoundBox.addButton("确定", QMessageBox::AcceptRole);
    noFoundBox.setFont(QFont("Microsoft YaHei UI", 10));
    noFoundBox.setWindowIcon(QIcon(":/ico/PTM.ico"));
    noFoundBox.setIcon(QMessageBox::Critical);
    noFoundBox.setWindowModality(Qt::ApplicationModal);//直到关闭提示框才使主窗口恢复焦点

    MyLabel* lblNo = new MyLabel(&w);
    lblNo->resize(440, 45);
    lblNo->move(370, 305);
    lblNo->setText("");
    lblNo->setFont(QFont("Microsoft YaHei UI", 14));
    lblNo->setWordWrap(true);

    MyLabel* lblTrainEdit[10]; MyLineEdit* txtTrainEdit[10];
    for(int i = 0; i < 10; i = i + 1)
    {
        lblTrainEdit[i] = new MyLabel(&w);
        lblTrainEdit[i]->resize(200, 50);
        lblTrainEdit[i]->move(400 + (i % 3) * 460, 360 + (i / 3) * 65);
        lblTrainEdit[i]->setText(lstTrains->headerItem()->text(i) + "：");
        lblTrainEdit[i]->setFont(QFont("Microsoft YaHei UI", 16));
        lblTrainEdit[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        txtTrainEdit[i] = new MyLineEdit(&w);
        txtTrainEdit[i]->resize(220, 50);
        txtTrainEdit[i]->move(lblTrainEdit[i]->x() + lblTrainEdit[i]->width(), lblTrainEdit[i]->y());
        txtTrainEdit[i]->setFont(QFont("Microsoft YaHei UI", 16));
        txtTrainEdit[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        txtTrainEdit[i]->id = i;
        txtTrainEdit[i]->setDisabled();
        txtTrainEdit[i]->setMaxLength(20);
    }
    txtTrainEdit[9]->resize(txtTrainEdit[8]->x() + txtTrainEdit[8]->width() - txtTrainEdit[9]->x(), 50);
    txtTrainEdit[9]->setMaxLength(100);
    txtTrainEdit[9]->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    txtTrainEdit[0]->edit = true;
    MyLineEdit::list = lstTrains;

    wrongInputBox[2].setWindowTitle("输入错误");
    wrongInputBox[2].setText("请重新检查输入内容，尤其注意输入车次和时刻时应尽量输入完整，例如G2922、13:50。"
                             "此外，还应注意输入的信息（比如开车时间）是否在正确的位置、是否有合理的逻辑顺序。");
    wrongInputBox[2].addButton("确定", QMessageBox::AcceptRole);
    wrongInputBox[2].setFont(QFont("Microsoft YaHei UI", 10));
    wrongInputBox[2].setWindowIcon(QIcon(":/ico/PTM.ico"));
    wrongInputBox[2].setIcon(QMessageBox::Critical);
    wrongInputBox[2].setWindowModality(Qt::ApplicationModal);//直到关闭提示框才使主窗口恢复焦点

    QMessageBox conflictNoBox;
    conflictNoBox.setWindowTitle("错误");
    conflictNoBox.setText("数据列表中已经存在该车次号，请修改车次号避免冲突。");
    conflictNoBox.setFont(QFont("Microsoft YaHei UI", 10));
    conflictNoBox.addButton("确定", QMessageBox::AcceptRole);
    conflictNoBox.setWindowIcon(QIcon(":/ico/PTM.ico"));
    conflictNoBox.setIcon(QMessageBox::Critical);
    conflictNoBox.setWindowModality(Qt::ApplicationModal);//直到关闭提示框才使主窗口恢复焦点

    MyLabel* lblStationsInfo = new MyLabel(&w);
    lblStationsInfo->resize(220, 40);
    lblStationsInfo->move(370, 695);
    lblStationsInfo->setText("途经站列表：");
    lblStationsInfo->setFont(QFont("Microsoft YaHei UI", 16));
    lblStationsInfo->setWordWrap(true);
    lblStationsInfo->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    MyLabel* lblCheckOperation = new MyLabel(&w);
    lblCheckOperation->resize(1000, 80);
    lblCheckOperation->move(600, 610);
    lblCheckOperation->setText(instruct[3]);
    lblCheckOperation->setFont(QFont("Microsoft YaHei UI", 14));
    lblCheckOperation->setWordWrap(true);

    QStringList stlStationHeader;
    stlStationHeader << "站次" << "站名"
                     << "到达时间" << "开车时间"
                     << "天数" << "里程" << "备注";
    MyTreeWidget* lstStations = new MyTreeWidget(&w);
    lstStations->resize(1150, 315);
    lstStations->move(600, 695);
    lstStations->setColumnCount(7);
    lstStations->setHeaderLabels(stlStationHeader);
    lstStations->setFont(QFont("Microsoft YaHei UI", 12));
    lstStations->setDisabled();
    lstStations->btnSave = btnSave;

    QObject::connect(txtEdit, &MyLineEdit::textChanged, txtEdit, &MyLineEdit::emitIsEmpty);
    QObject::connect(txtEdit, &MyLineEdit::isEmpty, btnEdit, &MyPushButton::changeState);
    QObject::connect(btnEdit, &MyPushButton::clicked, txtEdit, &MyLineEdit::emitTextNo);
    QObject::connect(txtEdit, &MyLineEdit::returnPressed, txtEdit, &MyLineEdit::emitTextNo);
    QObject::connect(txtEdit, &MyLineEdit::wrongInput, &wrongInputBox[1], &QMessageBox::show);
    QObject::connect(txtEdit, &MyLineEdit::sendTextNo, lstTrains, &MyTreeWidget::searchNo);
    QObject::connect(lstTrains, &MyTreeWidget::searchFound, lblNo, &MyLabel::changeNo);
    QObject::connect(lstTrains, &MyTreeWidget::searchFound, lstStations, &MyTreeWidget::setEnabled);
    QObject::connect(lstTrains, &MyTreeWidget::searchFound, lstStations, &MyTreeWidget::showResultList);
    QObject::connect(lstTrains, &MyTreeWidget::searchNoFound, &noFoundBox, &QMessageBox::show);
    for(int i = 0; i < 10; i = i + 1)
    {
        QObject::connect(lstTrains, &MyTreeWidget::searchFound, txtTrainEdit[i], &MyLineEdit::setEnabled);
        QObject::connect(lstTrains, &MyTreeWidget::searchFound, txtTrainEdit[i], &MyLineEdit::showInfo);
        QObject::connect(txtTrainEdit[i], &MyLineEdit::textEdited, btnSave, &MyPushButton::setEnabled);
        QObject::connect(txtTrainEdit[i], &MyLineEdit::textEdited, txtTrainEdit[i], &MyLineEdit::emitEditTextAndId);
        QObject::connect(txtTrainEdit[i], &MyLineEdit::sendEditTextAndId, lstStations, &MyTreeWidget::changeFirstAndLastStation);

        QObject::connect(btnSave, &MyPushButton::clicked, txtTrainEdit[i], &MyLineEdit::checkTextAndId1);
        QObject::connect(txtTrainEdit[i], &MyLineEdit::wrongInput, &wrongInputBox[2], &QMessageBox::show);
        QObject::connect(txtTrainEdit[i], &MyLineEdit::checkPassed, lstStations, &MyTreeWidget::checkAll);
    }
    QObject::connect(txtTrainEdit[0], &MyLineEdit::conflictInput, &conflictNoBox, &QMessageBox::show);

    lstStations->wEdit = new MyWidget;
    lstStations->wEdit->resize(810, 340);
    lstStations->wEdit->move(450, 200);
    lstStations->wEdit->setFixedSize(QSize(810, 340));
    lstStations->wEdit->setWindowTitle("*");
    lstStations->wEdit->setPalette(QPalette(Qt::white));
    lstStations->wEdit->setWindowIcon(QIcon(":/ico/PTM.ico"));
    lstStations->wEdit->removeAllObject();
    lstStations->wEdit->setWindowModality(Qt::ApplicationModal);//保持子窗口最顶端并使主窗口失去焦点
    w.setAttribute(Qt::WA_QuitOnClose, true);//主窗口关闭其他窗口全部关闭
    lstStations->wEdit->setAttribute(Qt::WA_QuitOnClose, false);

    MyLabel* lblStationEdit[7]; MyLineEdit* txtStationEdit[7];
    for(int i = 0; i < 6; i = i + 1)
    {
        lblStationEdit[i] = new MyLabel(lstStations->wEdit);
        lblStationEdit[i]->resize(170, 45);
        lblStationEdit[i]->move(10 + 350 * (i % 2), 20 + 60 * (i / 2));
        lblStationEdit[i]->setText(stlStationHeader.takeFirst() + "：");
        lblStationEdit[i]->setFont(QFont("Microsoft YaHei UI", 14));
        lblStationEdit[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        txtStationEdit[i] = new MyLineEdit(lstStations->wEdit);
        txtStationEdit[i]->resize(150, 45);
        txtStationEdit[i]->move(lblStationEdit[i]->x() + lblStationEdit[i]->width(), lblStationEdit[i]->y());
        txtStationEdit[i]->setFont(QFont("Microsoft YaHei UI", 14));
        txtStationEdit[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        txtStationEdit[i]->id = i;
        txtStationEdit[i]->setMaxLength(20);
    }
    lblStationEdit[6] = new MyLabel(lstStations->wEdit);
    lblStationEdit[6]->resize(170, 45);
    lblStationEdit[6]->move(lblStationEdit[4]->x(), lblStationEdit[4]->y() + 60);
    lblStationEdit[6]->setText(stlStationHeader.takeFirst() + "：");
    lblStationEdit[6]->setFont(QFont("Microsoft YaHei UI", 14));
    lblStationEdit[6]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    txtStationEdit[6] = new MyLineEdit(lstStations->wEdit);
    txtStationEdit[6]->resize(500, 45);
    txtStationEdit[6]->move(lblStationEdit[6]->x() + lblStationEdit[6]->width(), lblStationEdit[6]->y());
    txtStationEdit[6]->setFont(QFont("Microsoft YaHei UI", 14));
    txtStationEdit[6]->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    txtStationEdit[6]->id = 6;
    txtStationEdit[6]->setMaxLength(20);

    MyPushButton* btnEditConfirm = new MyPushButton(lstStations->wEdit);
    btnEditConfirm->resize(120, 60);
    btnEditConfirm->move(550, 260);
    btnEditConfirm->setText("确认");
    btnEditConfirm->setFont(QFont("Microsoft YaHei UI", 16));

    MyPushButton* btnEditCancel = new MyPushButton(lstStations->wEdit);
    btnEditCancel->resize(120, 60);
    btnEditCancel->move(680, 260);
    btnEditCancel->setText("取消");
    btnEditCancel->setFont(QFont("Microsoft YaHei UI", 16));

    QObject::connect(btnEditConfirm, &MyPushButton::clicked, btnSave, &MyPushButton::setEnabled);
    QObject::connect(btnEditCancel, &MyPushButton::clicked, lstStations->wEdit, &MyWidget::close);
    for(int i = 0; i < 7; i = i + 1)
    {
        QObject::connect(lstStations, &MyTreeWidget::sendStation, txtStationEdit[i], &MyLineEdit::showStation);
        QObject::connect(btnEditConfirm, &MyPushButton::clicked, txtStationEdit[i], &MyLineEdit::checkTextAndId2);
        QObject::connect(txtStationEdit[i], &MyLineEdit::wrongInput, &wrongInputBox[2], &QMessageBox::show);

        for(int j = 0; j < 7; j = j + 1)
        {
            QObject::connect(txtStationEdit[i], &MyLineEdit::checkPassed, txtStationEdit[j], &MyLineEdit::emitTextAndId);
        }

        QObject::connect(txtStationEdit[i], &MyLineEdit::sendTextAndId, lstStations, &MyTreeWidget::receiveAndShowStation);

    }
    QObject::connect(lstStations, &MyTreeWidget::received, lstStations->wEdit, &MyWidget::close);

    QMessageBox editSuccessBox;
    editSuccessBox.setWindowTitle("保存成功");
    editSuccessBox.setText("您的修改已经成功保存！");
    editSuccessBox.addButton("确定", QMessageBox::AcceptRole);
    editSuccessBox.setFont(QFont("Microsoft YaHei UI", 10));
    editSuccessBox.setWindowIcon(QIcon(":/ico/PTM.ico"));
    editSuccessBox.setIcon(QMessageBox::Information);
    editSuccessBox.setWindowModality(Qt::ApplicationModal);//直到关闭提示框才使主窗口恢复焦点

    QObject::connect(btnSave, &MyPushButton::clicked, lstStations, &MyTreeWidget::checkStation);
    QObject::connect(lstStations, &MyTreeWidget::wrongInput, &wrongInputBox[2], &QMessageBox::show);
    QObject::connect(lstStations, &MyTreeWidget::checkStationSuccess, lstStations, &MyTreeWidget::checkAll);
    QObject::connect(lstStations, &MyTreeWidget::checkAllSuccess, &editSuccessBox, &QMessageBox::show);
    for(int i = 0; i < 10; i = i + 1)
    {
        QObject::connect(lstStations, &MyTreeWidget::checkAllSuccess, txtTrainEdit[i], &MyLineEdit::emitTextAndId);
        QObject::connect(txtTrainEdit[i], &MyLineEdit::sendTextAndId, lstTrains, &MyTreeWidget::setTrain);
    }
    QObject::connect(lstTrains, &MyTreeWidget::trainIsSet, lstStations, &MyTreeWidget::emitList);
    QObject::connect(lstStations, &MyTreeWidget::sendList, lstTrains, &MyTreeWidget::setStation);

    MyPushButton* btnAdd = new MyPushButton(&w);
    btnAdd->resize(240, 441);
    btnAdd->move(351, 188);
    btnAdd->setFont(QFont("Microsoft YaHei UI", 18));
    btnAdd->setIcon(QIcon(":/new/add/btnAdd.png"));
    btnAdd->setIconSize(QSize(80, 200));

    MyLabel* lblNew[10]; MyLineEdit* txtNew[10];
    for(int i = 0; i < 10; i = i + 1)
    {
        lblNew[i] = new MyLabel(&w);
        lblNew[i]->resize(180, 50);
        lblNew[i]->move(620 + (i % 3) * 400, 230 + (i / 3) * 80);
        lblNew[i]->setText(lstTrains->headerItem()->text(i) + "：");
        lblNew[i]->setFont(QFont("Microsoft YaHei UI", 18));
        lblNew[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        txtNew[i] = new MyLineEdit(&w);
        txtNew[i]->resize(170, 50);
        txtNew[i]->move(lblNew[i]->x() + lblNew[i]->width(), lblNew[i]->y());
        txtNew[i]->setFont(QFont("Microsoft YaHei UI", 18));
        txtNew[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        txtNew[i]->id = i;
        txtNew[i]->setMaxLength(20);

    }
    txtNew[9]->resize(txtNew[8]->x() + txtNew[8]->width() - txtNew[9]->x(), 50);
    txtNew[9]->setMaxLength(100);
    txtNew[9]->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QObject::connect(txtNew[0], &MyLineEdit::conflictInput, &conflictNoBox, &QMessageBox::show);

    MyLabel* lblAddStationInstuct = new MyLabel(&w);
    lblAddStationInstuct->resize(750, 40);
    lblAddStationInstuct->move(875, 560);
    lblAddStationInstuct->setText(instruct[4]);
    lblAddStationInstuct->setFont(QFont("Microsoft YaHei UI", 14));
    lblAddStationInstuct->setWordWrap(true);

    QMessageBox addSuccessBox;
    addSuccessBox.setWindowTitle("添加成功");
    addSuccessBox.setText("您已经成功添加了车次信息！");
    addSuccessBox.addButton("确定", QMessageBox::AcceptRole);
    addSuccessBox.setFont(QFont("Microsoft YaHei UI", 10));
    addSuccessBox.setWindowIcon(QIcon(":/ico/PTM.ico"));
    addSuccessBox.setIcon(QMessageBox::Information);
    addSuccessBox.setWindowModality(Qt::ApplicationModal);//直到关闭提示框才使主窗口恢复焦点

    for(int i = 0; i < 10; i = i + 1)
    {
        QObject::connect(btnAdd, &MyPushButton::clicked, txtNew[i], &MyLineEdit::checkTextAndId1);
        QObject::connect(txtNew[i], &MyLineEdit::wrongInput, &wrongInputBox[2], &QMessageBox::show);
        for(int j = 0; j < 10; j = j + 1)
        {
            QObject::connect(txtNew[i], &MyLineEdit::checkPassed, txtNew[j], &MyLineEdit::emitTextAndId);
        }
        QObject::connect(txtNew[i], &MyLineEdit::sendTextAndId, lstTrains, &MyTreeWidget::addNewTrain);
        QObject::connect(&addSuccessBox, &QMessageBox::buttonClicked, txtNew[i], &MyLineEdit::clear);
    }
    QObject::connect(lstTrains, &MyTreeWidget::reverseInput, &wrongInputBox[2], &QMessageBox::show);
    QObject::connect(lstTrains, &MyTreeWidget::trainCreated, &addSuccessBox, &QMessageBox::show);
    QObject::connect(lstTrains, &MyTreeWidget::trainCreated, &lblTotal, &MyLabel::updateTotal);

    MyFrame* lneNewAndDel = new MyFrame(&w);
    lneNewAndDel->move(353, 628);
    lneNewAndDel->resize(1567, 3);
    lneNewAndDel->setLineWidth(3);
    lneNewAndDel->setFrameShape(QFrame::HLine);
    lneNewAndDel->setFrameShadow(QFrame::Plain);
    lneNewAndDel->setStyleSheet("color:#0076e4");

    MyLabel* lblDel = new MyLabel(&w);
    lblDel->resize(440, 40);
    lblDel->move(420, 650);
    lblDel->setText(instruct[5]);
    lblDel->setFont(QFont("Microsoft YaHei UI", 14));
    lblDel->setWordWrap(true);

    MyLineEdit* txtDel = new MyLineEdit(&w);
    txtDel->resize(300, 60);
    txtDel->move(420, 700);
    txtDel->setFont(QFont("Microsoft YaHei UI", 16));
    txtDel->setClearButtonEnabled(true);
    txtDel->setMaxLength(40);

    MyPushButton* btnSearchDel = new MyPushButton(&w);
    btnSearchDel->resize(130, 60);
    btnSearchDel->move(720, 700);
    btnSearchDel->setText("查找车次");
    btnSearchDel->setFont(QFont("Microsoft YaHei UI", 12));
    btnSearchDel->setDisabled();

    MyLabel* lblDelInfo[10], * lblDelInfoText[10];
    for(int i = 0; i < 10; i = i + 1)
    {
        lblDelInfo[i] = new MyLabel(&w);
        lblDelInfo[i]->resize(180, 40);
        lblDelInfo[i]->move(400 + (i % 3) * 430, 780 + (i / 3) * 60);
        lblDelInfo[i]->setText(lstTrains->headerItem()->text(i) + "：");
        lblDelInfo[i]->setFont(QFont("Microsoft YaHei UI", 16));
        lblDelInfo[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        lblDelInfoText[i] = new MyLabel(&w);
        lblDelInfoText[i]->resize(150, 40);
        lblDelInfoText[i]->move(lblDelInfo[i]->x() + lblDelInfo[i]->width(), lblDelInfo[i]->y());
        lblDelInfoText[i]->setText("");
        lblDelInfoText[i]->setFont(QFont("Microsoft YaHei UI", 16));
        lblDelInfoText[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        lblDelInfoText[i]->id = i;
    }
    lblDelInfoText[9]->resize(lblDelInfoText[8]->x() + lblDelInfoText[8]->width() - lblDelInfoText[9]->x(), 50);
    lblDelInfoText[9]->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    MyLabel* lblDelCaution = new MyLabel(&w);
    lblDelCaution->resize(400, 60);
    lblDelCaution->move(1000, 680);
    lblDelCaution->setText(instruct[6]);
    lblDelCaution->setFont(QFont("Microsoft YaHei UI", 16));

    MyPushButton* btnDel = new MyPushButton(&w);
    btnDel->resize(240 ,400);
    btnDel->move(1680, 630);
    btnDel->setFont(QFont("Microsoft YaHei UI", 18));
    btnDel->setIcon(QIcon(":/new/del/btnDel.png"));
    btnDel->setIconSize(QSize(80, 200));
    btnDel->setDisabled();

    QMessageBox deleteTrainBox;
    deleteTrainBox.setWindowTitle("确认删除车次信息");
    deleteTrainBox.setText("您确定要删除该车次信息？");
    deleteTrainBox.setFont(QFont("Microsoft YaHei UI", 10));
    lstTrains->deleteTrainConfirm = deleteTrainBox.addButton("确定", QMessageBox::AcceptRole);
    deleteTrainBox.addButton("取消", QMessageBox::RejectRole);
    deleteTrainBox.setWindowIcon(QIcon(":/ico/PTM.ico"));
    deleteTrainBox.setIcon(QMessageBox::Question);
    deleteTrainBox.setWindowModality(Qt::ApplicationModal);//直到关闭提示框才使主窗口恢复焦点

    QMessageBox delTrainSuccessBox;
    delTrainSuccessBox.setWindowTitle("删除成功");
    delTrainSuccessBox.setText("您已成功删除该车次信息！");
    delTrainSuccessBox.setFont(QFont("Microsoft YaHei UI", 10));
    delTrainSuccessBox.addButton("确定", QMessageBox::AcceptRole);
    delTrainSuccessBox.setWindowIcon(QIcon(":/ico/PTM.ico"));
    delTrainSuccessBox.setIcon(QMessageBox::Information);
    delTrainSuccessBox.setWindowModality(Qt::ApplicationModal);//直到关闭提示框才使主窗口恢复焦点

    QMessageBox delTrainConflictBox;
    delTrainConflictBox.setWindowTitle("错误");
    delTrainConflictBox.setText("您正在编辑该车次信息，暂不能删除！");
    delTrainConflictBox.setFont(QFont("Microsoft YaHei UI", 10));
    delTrainConflictBox.addButton("确定", QMessageBox::AcceptRole);
    delTrainConflictBox.setWindowIcon(QIcon(":/ico/PTM.ico"));
    delTrainConflictBox.setIcon(QMessageBox::Critical);
    delTrainConflictBox.setWindowModality(Qt::ApplicationModal);//直到关闭提示框才使主窗口恢复焦点

    QObject::connect(txtDel, &MyLineEdit::textChanged, txtDel, &MyLineEdit::emitIsEmpty);
    QObject::connect(txtDel, &MyLineEdit::isEmpty, btnSearchDel, &MyPushButton::changeState);
    QObject::connect(btnSearchDel, &MyPushButton::clicked, txtDel, &MyLineEdit::emitTextNo);
    QObject::connect(txtDel, &MyLineEdit::returnPressed, txtDel, &MyLineEdit::emitTextNo);
    QObject::connect(txtDel, &MyLineEdit::wrongInput, &wrongInputBox[1], &QMessageBox::show);
    QObject::connect(txtDel, &MyLineEdit::sendTextNo, lstTrains, &MyTreeWidget::searchDel);
    QObject::connect(lstTrains, &MyTreeWidget::conflictDelNumber, &delTrainConflictBox, &QMessageBox::show);
    QObject::connect(lstTrains, &MyTreeWidget::delFound, btnDel, &MyPushButton::setEnabled);
    for(int i = 0 ; i < 10; i = i + 1)
    {
        QObject::connect(lstTrains, &MyTreeWidget::delFound, lblDelInfoText[i], &MyLabel::showInfo);
    }
    QObject::connect(lstTrains, &MyTreeWidget::delFound, btnDel, &MyPushButton::setEnabled);
    QObject::connect(lstTrains, &MyTreeWidget::delNoFound, &noFoundBox, &QMessageBox::show);
    QObject::connect(btnDel, &MyPushButton::clicked, &deleteTrainBox, &QMessageBox::show);
    QObject::connect(&deleteTrainBox, &QMessageBox::buttonClicked, lstTrains, &MyTreeWidget::confirmDeleteTrain);
    QObject::connect(lstTrains, &MyTreeWidget::trainDeleted, &delTrainSuccessBox, &QMessageBox::show);
    QObject::connect(lstTrains, &MyTreeWidget::trainDeleted, &lblTotal, &MyLabel::updateTotal);
    QObject::connect(lstTrains, &MyTreeWidget::trainDeleted, txtDel, &MyLineEdit::clear);
    QObject::connect(lstTrains, &MyTreeWidget::trainDeleted, btnDel, &MyPushButton::setDisabled);

    MyTreeWidget* lstHelp = new MyTreeWidget(&w);
    lstHelp->resize(1450, 700);
    lstHelp->move(400, 230);
    lstHelp->setColumnCount(1);
    lstHelp->setHeaderHidden(true);
    lstHelp->setFont(QFont("华文中宋", 16));
    loadHelp(lstHelp);

    MyLabel* lblContact = new MyLabel(&w);
    lblContact->resize(1050, 45);
    lblContact->move(600, 950);
    lblContact->setText("如果帮助仍然无法解决疑问，或者发现了软件bug，请联系官方邮箱aksldhfjg@163.com进行处理。");
    lblContact->setFont(QFont("Microsoft YaHei UI", 14));

    for(int i = 0; i < 4; i = i + 1)
    {
        if(i == 0)
        {
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lstTrains, &MyTreeWidget::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lblSearch, &MyLabel::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, txtSearch, &MyLineEdit::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, btnSearch, &MyPushButton::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, btnSwitch, &MyPushButton::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, btnBack, &MyPushButton::show);
            continue;
        }

        QObject::connect(btnMenu[i], &MyPushButton::clicked, lstTrains, &MyTreeWidget::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, lblSearch, &MyLabel::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, txtSearch, &MyLineEdit::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, btnSearch, &MyPushButton::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, btnSwitch, &MyPushButton::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, btnBack, &MyPushButton::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, btnBack, &MyPushButton::click);
    }

    for(int i = 0; i < 4; i = i + 1)
    {
        if(i == 1)
        {
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lblEdit, &MyLabel::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, txtEdit, &MyLineEdit::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, btnEdit, &MyPushButton::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lblSave, &MyLabel::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, btnSave, &MyPushButton::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lneEdit1, &MyFrame::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lblNo, &MyLabel::show);
            for(int j = 0; j < 10; j = j + 1)
            {
                QObject::connect(btnMenu[i], &MyPushButton::clicked, lblTrainEdit[j], &MyLabel::show);
                QObject::connect(btnMenu[i], &MyPushButton::clicked, txtTrainEdit[j], &MyLineEdit::show);
            }
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lblCheckOperation, &MyLabel::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lstStations, &MyTreeWidget::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lblStationsInfo, &MyLabel::show);
            continue;
        }

        QObject::connect(btnMenu[i], &MyPushButton::clicked, lblEdit, &MyLabel::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, txtEdit, &MyLineEdit::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, btnEdit, &MyPushButton::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, lblSave, &MyLabel::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, btnSave, &MyPushButton::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, lneEdit1, &MyFrame::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, lblNo, &MyLabel::setHidden);
        for(int j = 0; j < 10; j = j + 1)
        {
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lblTrainEdit[j], &MyLabel::setHidden);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, txtTrainEdit[j], &MyLineEdit::setHidden);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lstStations, &MyTreeWidget::setHidden);
        }
        QObject::connect(btnMenu[i], &MyPushButton::clicked, lblCheckOperation, &MyLabel::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, lblStationsInfo, &MyLabel::setHidden);
    }

    for(int i = 0; i < 4; i = i + 1)
    {
        if(i == 2)
        {
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lblAddStationInstuct, &MyLabel::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lblDel, &MyLabel::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, txtDel, &MyLineEdit::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, btnSearchDel, &MyPushButton::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, btnAdd, &MyPushButton::show);
            for(int j = 0; j < 10; j = j + 1)
            {
                QObject::connect(btnMenu[i], &MyPushButton::clicked, lblNew[j], &MyLabel::show);
                QObject::connect(btnMenu[i], &MyPushButton::clicked, lblDelInfo[j], &MyLabel::show);
                QObject::connect(btnMenu[i], &MyPushButton::clicked, lblDelInfoText[j], &MyLabel::show);
                QObject::connect(btnMenu[i], &MyPushButton::clicked, txtNew[j], &MyLineEdit::show);
            }
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lneNewAndDel, &MyFrame::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lblDelCaution, &MyLabel::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, btnDel, &MyPushButton::show);
            continue;
        }

        QObject::connect(btnMenu[i], &MyPushButton::clicked, lblAddStationInstuct, &MyLabel::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, lblDel, &MyLabel::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, txtDel, &MyLineEdit::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, btnSearchDel, &MyPushButton::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, btnAdd, &MyPushButton::setHidden);
        for(int j = 0; j < 10; j = j + 1)
        {
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lblNew[j], &MyLabel::setHidden);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lblDelInfo[j], &MyLabel::setHidden);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lblDelInfoText[j], &MyLabel::setHidden);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, txtNew[j], &MyLineEdit::setHidden);
        }
        QObject::connect(btnMenu[i], &MyPushButton::clicked, lneNewAndDel, &MyFrame::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, lblDelCaution, &MyLabel::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, btnDel, &MyPushButton::setHidden);
    }

    for(int i = 0; i < 4; i = i + 1)
    {
        if(i == 3)
        {
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lstHelp, &MyTreeWidget::show);
            QObject::connect(btnMenu[i], &MyPushButton::clicked, lblContact, &MyLabel::show);
            continue;
        }
        QObject::connect(btnMenu[i], &MyPushButton::clicked, lstHelp, &MyTreeWidget::setHidden);
        QObject::connect(btnMenu[i], &MyPushButton::clicked, lblContact, &MyLabel::setHidden);
    }

    btnMenu[0]->click();
    return a.exec();
}
#include "main.moc"
