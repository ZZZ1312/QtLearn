#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setActionsForButton();
    createSelectionPopMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setActionsForButton()
{
    // 为QToolButton按钮设置 Action
    ui->tBtnInit->setDefaultAction(ui->actionInitList);
    ui->tBtnClear->setDefaultAction(ui->actionClear);
    ui->tBtnInsert->setDefaultAction(ui->actionInsert);
    ui->tBtnAdd->setDefaultAction(ui->actionAdd);
    ui->tBtnDelete->setDefaultAction(ui->actionDelete);

    ui->tBtnSelAll->setDefaultAction(ui->actionSelAll);
    ui->tBtnSelNone->setDefaultAction(ui->actionSelNone);
    ui->tBtnSelInvs->setDefaultAction(ui->actionSelInvs);
}

void MainWindow::createSelectionPopMenu()
{
    // 创建下拉菜单
    QMenu *menuSelection = new QMenu(this); // 创建弹出式菜单
    menuSelection->addAction(ui->actionSelAll);
    menuSelection->addAction(ui->actionSelNone);
    menuSelection->addAction(ui->actionSelInvs);

    // listWidget上方的bBtnSelectItem按钮
    ui->tBtnSelectItem->setPopupMode(QToolButton::MenuButtonPopup);
    ui->tBtnSelectItem->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->tBtnSelectItem->setDefaultAction(ui->actionSelPopMenu);
    ui->tBtnSelectItem->setMenu(menuSelection);

    // 工具栏上的下拉式菜单按钮
    QToolButton *aBtn = new QToolButton(this);
    aBtn->setPopupMode(QToolButton::InstantPopup);
    aBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    aBtn->setDefaultAction(ui->actionSelPopMenu);
    aBtn->setMenu(menuSelection);

    ui->toolBar->addWidget(aBtn); // 工具栏添加按钮
    // 工具条添加分隔条和退出按钮
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionQuit);

}

void MainWindow::on_actionInitList_triggered()
{
    // 初始化列表
    QListWidgetItem *aItem; // 每一行是一个QListWidgetItem
    QIcon aIcon;
    aIcon.addFile(":/images/icons/point.png");
    bool chk = ui->chkListEditable->isChecked();

    ui->listWidget->clear();
    for (int i = 0; i < 10; ++i)
    {
        QString str = QString::asprintf("Item %d",i );
        aItem = new QListWidgetItem;
        aItem->setText(str);
        aItem->setIcon(aIcon);
        aItem->setCheckState(Qt::Checked);
        if (chk)
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable
                            | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        else
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        ui->listWidget->addItem(aItem);
    }
}

void MainWindow::on_actionClear_triggered()
{
    // 清除列表
    ui->listWidget->clear();
}


void MainWindow::on_actionInsert_triggered()
{
    // 插入一个项
    QIcon aIcon;
    aIcon.addFile(":/images/icons/point.png");
    bool chk = ui->chkListEditable->isChecked();

    QListWidgetItem *aItem = new QListWidgetItem("New Inserted Item");
    aItem->setIcon(aIcon);
    aItem->setCheckState(Qt::Checked);
    if (chk)
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable
                        | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    else
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    int curRow = ui->listWidget->currentRow();
    ui->listWidget->insertItem(curRow, aItem);

}


void MainWindow::on_actionAdd_triggered()
{
    // 添加一个项
    QIcon aIcon;
    aIcon.addFile(":/images/icons/point.png");
    bool chk = ui->chkListEditable->isChecked();

    QListWidgetItem *aItem = new QListWidgetItem("New Append Item");
    aItem->setIcon(aIcon);
    aItem->setCheckState(Qt::Checked);
    if (chk)
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable
                        | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    else
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    ui->listWidget->addItem(aItem);
}


void MainWindow::on_actionDelete_triggered()
{
    // 删除当前项
    int row = ui->listWidget->currentRow();
    QListWidgetItem *aItem = ui->listWidget->takeItem(row);
    delete aItem; // 手动删除对象
}


void MainWindow::on_actionSelAll_triggered()
{
    // 全选
    int cnt = ui->listWidget->count(); // 个数
    for (int i = 0; i < cnt; ++i)
    {
        QListWidgetItem *aItem = ui->listWidget->item(i); // 获取一个项
        aItem->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_actionSelNone_triggered()
{
    // 全不选
    int cnt = ui->listWidget->count(); // 个数
    for (int i = 0; i < cnt; ++i)
    {
        QListWidgetItem *aItem = ui->listWidget->item(i); // 获取一个项
        aItem->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_actionSelInvs_triggered()
{
    // 反选
    int cnt = ui->listWidget->count();
    for (int i = 0; i < cnt; ++i)
    {
        QListWidgetItem *aItem = ui->listWidget->item(i); // 获取一个项
        Qt::CheckState curState = aItem->checkState();
        Qt::CheckState newState = Qt::Checked;
        if (curState == Qt::Checked)
            newState = Qt::Unchecked;
        aItem->setCheckState(newState);
    }
}


void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    // ListWidget当前选中项发生变化
    QString str;
    if (current != nullptr)
    {
        if (previous == nullptr)
            str = "当前项："+ current->text();
        else
            str = "前一项：" + previous->text() + "；当前项："+current->text();
        ui->editCurrentItem->setText(str);
    }
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->toolBox->setCurrentIndex(index);
}

