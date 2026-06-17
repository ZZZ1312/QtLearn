#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setRootPath(QDir::currentPath()); // 设置根目录
    ui->treeView->setModel(model); // 设置数据模型
    ui->listView->setModel(model); // 设置数据模型
    ui->tableView->setModel(model); // 设置数据模型
    // 信号与槽关联，treeView 单击时，其目录设置为 listView 和 tableView 的根节点
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), ui->listView, SLOT(setRootIndex(QModelIndex)));
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), ui->tableView, SLOT(setRootIndex(QModelIndex)));


}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_treeView_clicked(const QModelIndex &index)
{
    ui->chkIsDir->setChecked(model->isDir(index));
    ui->LabPath->setText(model->filePath(index));
    ui->LabType->setText(model->type(index));
    ui->LabFileName->setText(model->fileName(index));
    int sz = model->size(index);
    if (sz < 1024)
        ui->LabFileSize->setText(QString("%1 Byte").arg(sz));
    else
    {
        sz = sz / 1024;
        if (sz < 1024)
            ui->LabFileSize->setText(QString("%1 KB").arg(sz));
        else
            ui->LabFileSize->setText(QString::asprintf("%.1f MB", sz / 1024.0));
    }
}

