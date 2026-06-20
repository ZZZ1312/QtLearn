#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStringList>
#include <QMessageBox>
#include <QCloseEvent>

#include "qwdialogsize.h"
#include "qwdialogheaders.h"
#include "qwdialoglocate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    theModel = new QStandardItemModel(this);
    QStringList headers{"姓名","性别", "年龄", "籍贯"};
    theModel->setHorizontalHeaderLabels(headers);
    ui->tableView->setModel(theModel);

    theSelection = new QItemSelectionModel(theModel);
    ui->tableView->setSelectionModel(theSelection);

    labCellPos = new QLabel("当前单元格: ");
    labContent = new QLabel("单元格内容: ");
    ui->statusbar->addWidget(labCellPos,1);
    ui->statusbar->addWidget(labContent,2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // 窗口关闭时询问是否退出
    QMessageBox::StandardButton result = QMessageBox::question(
        this,
        "确认","确认要退出本程序吗?",
        QMessageBox::Yes| QMessageBox::No | QMessageBox::Cancel,
                QMessageBox::No);
    if (result == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

void MainWindow::on_actSetRowColumn_triggered()
{
    // 模态对话框，动态创建，用过后删除
    QWDialogSize *dlgTableSize = new QWDialogSize(this);
    Qt::WindowFlags flags = dlgTableSize->windowFlags();
    dlgTableSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    dlgTableSize->setRowColumn(theModel->rowCount(),theModel->columnCount());

    int ret = dlgTableSize->exec(); // 以模态方式显示对话框
    if (ret == QDialog::Accepted)
    {
        // OK 按钮被按下，获取对话框的输入，设置行数和列数
        int cols  = dlgTableSize->columnCount();
        theModel->setColumnCount(cols);
        int rows = dlgTableSize->rowCount();
        theModel->setRowCount(rows);
    }
    delete dlgTableSize;
}


void MainWindow::on_actSetHeaders_triggered()
{
    if (dlgSetHeaders == nullptr)
    {
        dlgSetHeaders = new QWDialogHeaders(this);
    }
    if (dlgSetHeaders->headerList().count() != theModel->columnCount())
    {
        // 如果表头列数变化，重新初始化
        QStringList strList;
        for (int i = 0; i < theModel->columnCount(); ++i) // 获取现有的表头标题
        {
            strList.append(theModel->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        }
        dlgSetHeaders->setHeaderList(strList); // 对话框初始化显示
    }

    int ret = dlgSetHeaders->exec(); // 以模态方式显示对话框
    if (ret == QDialog::Accepted)
    {
        QStringList strList = dlgSetHeaders->headerList();
        theModel->setHorizontalHeaderLabels(strList); // 设置模型的表头标题
    }
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    emit cellIndexChanged(index.row(), index.column());
}


void MainWindow::on_actLocateCell_triggered()
{
    // 创建 StayOnTop 的对话框，对话框关闭时自动删除
    QWDialogLocate *dlgLocate = new QWDialogLocate(this);
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose);

    Qt::WindowFlags flags = dlgLocate->windowFlags();
    dlgLocate->setWindowFlags(flags | Qt::WindowStaysOnTopHint);
    dlgLocate->setSpinRange(theModel->rowCount(), theModel->columnCount());
    QModelIndex curIndex = theSelection->currentIndex();
    if(curIndex.isValid())
        dlgLocate->setSpinValue(curIndex.row(), curIndex.column());
    // 对话框发射信号，设置单元格文字
    connect(dlgLocate, SIGNAL(changeCellText(int,int,QString)),
            this, SLOT(setACellTextSlot(int,int,QString)));
    // 对话框发射信号，设置 actLocateCell 的属性
    connect(dlgLocate, SIGNAL(changeActionEnable(bool)),
            this, SLOT(setActLocateEnable(bool)));
    // 主窗口发射信号，修改对话框上的 spinBox 的值
    connect(this, SIGNAL(cellIndexChanged(int,int)),
            dlgLocate, SLOT(setSpinValue(int,int)));
    dlgLocate->show(); // 非模态显示对话框
}

void MainWindow::setACellTextSlot(int row, int column, const QString &text)
{
    // 定位到单元格，并设置字符串
    QModelIndex index = theModel->index(row, column);
    if (!index.isValid())
        return;
    theSelection->clearSelection();
    theSelection->setCurrentIndex(index, QItemSelectionModel::Select);
    theModel->setData(index, text);
}

void MainWindow::setActLocateEnable(bool enable)
{
    // 设置 actLocate 的 enabeld 属性
    ui->actLocateCell->setEnabled(enable);
}