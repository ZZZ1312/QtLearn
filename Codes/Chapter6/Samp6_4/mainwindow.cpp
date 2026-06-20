#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qformdoc.h"
#include <QDir>
#include <QFileDialog>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->mdiArea);
    this->setWindowState(Qt::WindowMaximized);
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actNew_triggered()
{
    // 新建文档
    QFormDoc *formDoc = new QFormDoc(this);
    ui->mdiArea->addSubWindow(formDoc); // 文档串口添加到 MDI
    formDoc->show();
}


void MainWindow::on_actOpen_triggered()
{
    // 打开文件
    bool needNew = false; // 是否需要新建子窗口
    QFormDoc *formDoc;
    if (ui->mdiArea->subWindowList().count() > 0) // 获取活动窗口
    {
        formDoc = static_cast<QFormDoc*>(ui->mdiArea->activeSubWindow()->widget());
        needNew = formDoc->isFileOpened(); // 文件已经打开，需要新建窗口哦
    }
    else
        needNew = true;

    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getOpenFileName(this, "打开一个文件", curPath, "C程序文件(*.h *.cpp);;所有文件(*.*)");
    if (aFileName.isEmpty())
        return;
    if (needNew) // 需要新建子窗口
    {
        formDoc = new QFormDoc(this);
        ui->mdiArea->addSubWindow(formDoc);
    }

    formDoc->loadFormFile(aFileName); // 打开文件
    formDoc->show();
    ui->actCut->setEnabled(true);
    ui->actCopy->setEnabled(true);
    ui->actPaste->setEnabled(true);
    ui->actFont->setEnabled(true);

    ui->statusbar->showMessage(aFileName);
}


void MainWindow::on_actCascade_triggered()
{
    // 窗口级联展开
    ui->mdiArea->cascadeSubWindows();
}


void MainWindow::on_actTile_triggered()
{
    // 平铺展开
    ui->mdiArea->tileSubWindows();
}


void MainWindow::on_actCloseAll_triggered()
{
    // 关闭子窗口
    ui->mdiArea->closeAllSubWindows();
}

void MainWindow::on_actMDI_triggered(bool checked)
{
    // MDI 显示模式
    if (checked)
    {
        ui->mdiArea->setViewMode(QMdiArea::TabbedView);// Tab多页显示模式
        ui->mdiArea->setTabsClosable(true); // 页面可关闭
        ui->actCascade->setEnabled(false);
        ui->actTile->setEnabled(false);
    }
    else // 子窗口模式
    {
        ui->mdiArea->setViewMode(QMdiArea::SubWindowView); // 子窗口模式
        ui->actCascade->setEnabled(true);
        ui->actTile->setEnabled(true);
    }
}


void MainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow *arg1)
{
    if (ui->mdiArea->subWindowList().count() == 0)
    {
        // 若子窗口个数为0
        ui->actCut->setEnabled(false);
        ui->actCopy->setEnabled(false);
        ui->actPaste->setEnabled(false);
        ui->actFont->setEnabled(false);
        ui->statusbar->clearMessage();
    }
    else
    {
        QFormDoc *formDoc = static_cast<QFormDoc*>(arg1->widget());
        ui->statusbar->showMessage(formDoc->currentFileName());
    }
}

