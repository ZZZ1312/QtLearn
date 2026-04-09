#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStringList>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->scrollArea);
    labFileName = new QLabel("");
    ui->statusBar->addWidget(labFileName);
    initTree();

    ui->actDockVisible->setChecked(ui->dockWidget->isVisible());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTree()
{
    // 初始化目录树
    QString dataStr = ""; // Item 的 Data 存储的 string
    ui->treeFiles->clear();
    QIcon aIcon;
    aIcon.addFile(":/images/icons/root.png");

    QTreeWidgetItem *item = new QTreeWidgetItem(MainWindow::itTopItem);
    item->setIcon(MainWindow::colItem, aIcon);
    item->setText(MainWindow::colItem, "图片文件");
    item->setText(MainWindow::colItemType, "type=itTopItem");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
                   | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);

    item->setData(MainWindow::colItem, Qt::UserRole, QVariant(dataStr));
    ui->treeFiles->addTopLevelItem(item); // 添加顶层节点

}

void MainWindow::addFolderItem(QTreeWidgetItem *parItem, QString dirName)
{
    // 添加一个组节点
    QIcon icon(":/images/icons/dir.png");
    QString nodeText = getFinalFolderName(dirName); // 获得最后的文件夹的名称

    QTreeWidgetItem *item;
    item = new QTreeWidgetItem(MainWindow::itGroupItem); // 节点类型 itGroupItem
    item->setIcon(colItem, icon);
    item->setText(colItem, nodeText);
    item->setText(colItemType, "type=itGroupItem");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
                   | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);
    item->setData(colItem, Qt::UserRole, QVariant(dirName));
    parItem->addChild(item); // 在父节点下面添加子节点
}

QString MainWindow::getFinalFolderName(const QString &fullPathName)
{
    // 从一个完整目录名称丽，获得最后的文件夹名称
    int cnt = fullPathName.length();
    int i = fullPathName.lastIndexOf("/")   ;
    QString str = fullPathName.right(cnt - i - 1);
    return str;
}

void MainWindow::addImageItem(QTreeWidgetItem *parItem, QString aFileName)
{
    // 添加一个图片节点
    QIcon icon(":/images/icons/picture.png");
    QString nodeText = getFinalFolderName(aFileName); // 获得最后的文件名成
    QTreeWidgetItem *item;
    item = new QTreeWidgetItem(MainWindow::itImageItem); // 节点类型 itImageItem
    item->setIcon(colItem, icon);
    item->setText(colItem, nodeText);
    item->setText(colItemType, "type=itImageItem");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
                   | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);
    item->setData(colItem, Qt::UserRole, QVariant(aFileName));
    parItem->addChild(item);
}

void MainWindow::displayImage(QTreeWidgetItem *item)
{
    // 显示图片，节点Item存储了图片文件名
    QString fileName = item->data(colItem, Qt::UserRole).toString(); // 文件名
    labFileName->setText(fileName);
    curPixmap.load(fileName);
    on_actZoomFitH_triggered();

}

void MainWindow::changeItemCaption(QTreeWidgetItem *item)
{
    // 改变节点的标题文字
    QString str = "*" + item->text(colItem); // 节点标题前加*
    item->setText(colItem, str);
    if (item->childCount() > 0)
    {
        for (int i = 0; i < item->childCount(); ++i)
        {
            changeItemCaption(item->child(i));
        }
    }
}
void MainWindow::on_actAddFolder_triggered()
{
    // 添加组节点
    QString dir = QFileDialog::getExistingDirectory(); // 选择目录

    if (dir.isEmpty())
        return;

    QTreeWidgetItem *parItem = ui->treeFiles->currentItem(); // 当前节点
    if (parItem == nullptr)
    {
        int topCnt = ui->treeFiles->topLevelItemCount();
        if (topCnt < 1)
            return;
        else
            parItem = ui->treeFiles->topLevelItem(0);
    }

    addFolderItem(parItem, dir);
}


void MainWindow::on_actAddFile_triggered()
{
    // 添加图片文件节点
    QStringList files = QFileDialog::getOpenFileNames(this, "选择一个或多个文件", "", "Images(*.png)");
    if (files.isEmpty())
        return;
    QTreeWidgetItem *parItem, *item;
    item = ui->treeFiles->currentItem();
    if (item->type() == itImageItem)
        parItem = item->parent();
    else
        parItem = item;

    for (int i = 0; i < files.size(); ++i)
    {
        QString aFileName = files.at(i); // 得到一个文件名
        addImageItem(parItem, aFileName); // 得到一个图片节点
    }
}


void MainWindow::on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    // 当前节点变化时的处理
    Q_UNUSED(previous);
    if (current == nullptr)
        return;
    int var = current->type(); // 节点的类型
    switch(var)
    {
    case itTopItem:
        ui->actAddFolder->setEnabled(true);
        ui->actAddFile->setEnabled(true);
        ui->actDeleteItem->setEnabled(false); // 顶层节点不能删除
        break;
    case itGroupItem:
        ui->actAddFolder->setEnabled(true);
        ui->actAddFile->setEnabled(true);
        ui->actDeleteItem->setEnabled(true);
        break;
    case itImageItem:
        ui->actAddFolder->setEnabled(false);
        ui->actAddFile->setEnabled(true);
        ui->actDeleteItem->setEnabled(true);
        displayImage(current); // 显示图片
        break;
    }
}


void MainWindow::on_actDeleteItem_triggered()
{
    // 删除节点
    QTreeWidgetItem *item = ui->treeFiles->currentItem();
    QTreeWidgetItem *parItem = item->parent(); // 父节点
    parItem->removeChild(item);
    delete item;
}


void MainWindow::on_actTraverseItem_triggered()
{
    // 遍历节点
    for (int i = 0; i < ui->treeFiles->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem *item = ui->treeFiles->topLevelItem(i); // 顶层节点
        changeItemCaption(item);
    }
}


void MainWindow::on_actZoomFitH_triggered()
{
    // 适应高度显示图片
    int H = ui->scrollArea->height();
    int realH = curPixmap.height();
    pixRatio = static_cast<float>(H) / static_cast<float>(realH);
    QPixmap pix = curPixmap.scaledToHeight(H - 30); // 图片缩放到指定高度
    ui->labPicutre->setPixmap(pix);
}

void MainWindow::on_actZoomFitW_triggered()
{
    int W = ui->scrollArea->width();
    int realW = curPixmap.width();
    pixRatio = static_cast<float>(W) / static_cast<float>(realW);
    QPixmap pix = curPixmap.scaledToHeight(W - 30);
    ui->labPicutre->setPixmap(pix);
}



void MainWindow::on_actZommIn_triggered()
{
    // 放大显示
    pixRatio = pixRatio * 1.2;
    int w = pixRatio * curPixmap.width();
    int h = pixRatio * curPixmap.height();
    QPixmap pix = curPixmap.scaled(w, h);
    ui->labPicutre->setPixmap(pix);
}


void MainWindow::on_actZoomOut_triggered()
{
    pixRatio = pixRatio * 0.8;
    int w = pixRatio * curPixmap.width();
    int h = pixRatio * curPixmap.height();
    QPixmap pix = curPixmap.scaled(w, h);
    ui->labPicutre->setPixmap(pix);
}


void MainWindow::on_actZoomRealSize_triggered()
{
    pixRatio = 1;
    ui->labPicutre->setPixmap(curPixmap);
}



void MainWindow::on_actDockVisible_toggled(bool arg1)
{
    ui->dockWidget->setVisible(arg1);
}


void MainWindow::on_actDockFloat_triggered(bool checked)
{
    ui->dockWidget->setFloating(checked);
}


void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    ui->actDockVisible->setChecked(visible);
}


void MainWindow::on_dockWidget_topLevelChanged(bool topLevel)
{
    ui->actDockFloat->setChecked(topLevel);
}

