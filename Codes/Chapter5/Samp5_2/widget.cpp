#include "widget.h"
#include "./ui_widget.h"
#include <QStringList>
#include "counter.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    counter = new Counter();
    QStringList theStrList;
    theStrList << "北京" << "上海" << "天津" << "河北" << "山东" << "四川"
               << "重庆";
    theModel = new QStringListModel(this);
    theModel->setStringList(theStrList);
    ui->listView->setModel(theModel);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked |
                                  QAbstractItemView::SelectedClicked);
    // 设置为不可编辑
    // ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Widget::~Widget()
{
    delete ui;
    delete counter;
}

void Widget::on_btnAddItem_clicked()
{
    // 添加一行
    theModel->insertRow(theModel->rowCount()); // 在尾部插入一行
    QModelIndex index = theModel->index(theModel->rowCount() - 1, 0);
    theModel->setData(index,QString("new Item%1").arg(counter->getNextNumber()), Qt::DisplayRole);
    ui->listView->setCurrentIndex(index); // 设置当前选中的行
}


void Widget::on_btnInsertItem_clicked()
{
    // 插入一行
    QModelIndex index = ui->listView->currentIndex();
    theModel->insertRow(index.row());
    theModel->setData(index, QString("inserted Item%1").arg(counter->getNextNumber()), Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void Widget::on_btnDeleteItem_clicked()
{
    // 删除当前行
    QModelIndex index = ui->listView->currentIndex();
    theModel->removeRow(index.row());
}



void Widget::on_btnClear_clicked()
{
    // 删除整个列表
    theModel->removeRows(0, theModel->rowCount());
}


void Widget::on_btnShow_clicked()
{
    // 显示数据模型的 StringList
    QStringList tmpList = theModel->stringList();
    ui->plainTextEdit->clear();
    for (int i = 0; i < tmpList.count(); ++i)
    {
        ui->plainTextEdit->appendPlainText(tmpList.at(i));
    }
}


void Widget::on_btnClearText_clicked()
{
    // 清空文本框
    ui->plainTextEdit->clear();
}


void Widget::on_listView_clicked(const QModelIndex &index)
{
    // 显示QModelIndex的行、列号
    ui->LabInfo->setText(QString::asprintf("当前条目:row=%d, column=%d", index.row(), index.column()));
}

