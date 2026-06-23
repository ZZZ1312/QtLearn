#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QDataStream>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "qwintspindelegate.h"
#include "qwfloatspindelegate.h"
#include "qwcomboboxdelegate.h"
#include <QListView>
#include <QDebug>

static int FixedColumnCount = 6;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    ui->tabWidget->setTabText(0, "表格数据文件");

    theModel = new QStandardItemModel(0, FixedColumnCount, this);
    theSelection = new QItemSelectionModel(theModel);

    ui->tabWidget->setCurrentIndex(0);
    QWidget *widget = ui->tabWidget->currentWidget();
    QTableView *tableView = widget->findChild<QTableView*>("tableView");
    tableView->setModel(theModel);
    tableView->setSelectionModel(theSelection);

    QStringList horizontalHeaders{"测深", "垂深", "方位", "位移", "固井质量", "测井取样"};
    theModel->setHorizontalHeaderLabels(horizontalHeaders);

    intSpinDelegate = new QWIntSpinDelegate{};
    floatSpinDelegate = new QWFloatSpinDelegate{};
    comboBoxDelegate = new QWComboBoxDelegate{};

    tableView->setItemDelegateForColumn(0, intSpinDelegate);
    tableView->setItemDelegateForColumn(1, floatSpinDelegate);
    tableView->setItemDelegateForColumn(2, floatSpinDelegate);
    tableView->setItemDelegateForColumn(3, floatSpinDelegate);
    tableView->setItemDelegateForColumn(4, comboBoxDelegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetTable(int aRowCount)
{
    // 表格复位
    theModel->removeRows(0, theModel->rowCount());
    theModel->setColumnCount(FixedColumnCount);
    theModel->setRowCount(aRowCount);
    QString str = theModel->headerData(theModel->columnCount() - 1,
                                       Qt::Horizontal, Qt::DisplayRole).toString();
    for (int i = 0; i < theModel->rowCount(); ++i)
    {
        QList<QStandardItem *> rowItems;
        for (int j = 0; j < FixedColumnCount; ++j)
        {
            rowItems << new QStandardItem{""};
        }

        // 创建最后一列需要特殊处理的 Item
        QStandardItem *lastItem = new QStandardItem{str};
        lastItem->setCheckable(true);
        lastItem->setEditable(false);
        rowItems << lastItem;
        theModel->appendRow(rowItems);
    }
}



bool MainWindow::saveDataAsStream(const QString &fileName)
{
    // 将模型数据保存为 Qt 预定义编码的数据文件
    QFile aFile(fileName);
    if (!(aFile.open(QIODevice::WriteOnly | QIODevice::Truncate)))
        return false;
    QDataStream aStream(&aFile);
    aStream.setVersion(QDataStream::Qt_6_11); // 流版本号,写入和读取版本要兼容
    qint16 rowCount = theModel->rowCount();
    qint16 colCount = theModel->columnCount();

    aStream <<rowCount; // 写入文件流,行数
    aStream << colCount; // 写入文件流,列数
    // 获取表头文字中
    for (int i = 0; i < theModel->columnCount();++i)
    {
        QString str = theModel->horizontalHeaderItem(i)->text(); // 表头文字
        aStream << str;
    }

    // 获取数据区的数据
    for (int i = 0; i < theModel->rowCount(); ++i)
    {
        QStandardItem *item = theModel->item(i,0); // 侧深
        qint16 ceShen = item->data(Qt::DisplayRole).toInt();
        aStream << ceShen;

        item = theModel->item(i,1); // 垂深
        qreal chuiShen = item->data(Qt::DisplayRole).toFloat();
        aStream << chuiShen;

        item = theModel->item(i,2); // 方位
        qreal fangWei = item->data(Qt::DisplayRole).toFloat();
        aStream << fangWei;

        item = theModel->item(i,3); // 位移
        qreal weiYi = item->data(Qt::DisplayRole).toInt();
        aStream << weiYi;

        item = theModel->item(i,4); // 固井质量
        QString quality = item->data(Qt::DisplayRole).toString();
        aStream << quality;

        item = theModel->item(i,5); // 侧深
        bool quYang = (item->checkState() == Qt::Checked);
        aStream << quYang;
    }

    aFile.close();
    return true;
}


bool MainWindow::openDataAsStream(const QString& fileName)
{
    // 从 stm 文件读入数据
    QFile aFile(fileName);
    if (!(aFile.open(QIODevice::ReadOnly)))
        return false;
    QDataStream aStream(&aFile);
    aStream.setVersion(QDataStream::Qt_6_11);
    qint16 rowCount, colCount;
    aStream >> rowCount;
    aStream >> colCount;
    this->resetTable(rowCount);
    // 获取表头文字，但并不使用
    QString str;
    for (int i = 0; i < colCount; ++i)
        aStream >> str; // 读取表头字符串
    // 读取数据区数据
    qint16 ceShen;
    qreal chuiShen, fangWei, weiYi;
    QString zhiLiang;
    bool quYang;
    QStandardItem *aItem;
    QModelIndex index;
    resetTable(rowCount);
    for (int i = 0; i < rowCount; ++i)
    {
        aStream >> ceShen; // 读取测深
        index = theModel->index(i, 0);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(ceShen, Qt::DisplayRole);

        aStream >> chuiShen; // 垂深
        index = theModel->index(i, 1);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(chuiShen, Qt::DisplayRole);

        aStream >> fangWei; // 方位
        index = theModel->index(i, 2);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(fangWei, Qt::DisplayRole);

        aStream >> weiYi;
        index = theModel->index(i, 3);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(weiYi, Qt::DisplayRole);

        aStream >> zhiLiang;
        index = theModel->index(i, 4);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(zhiLiang, Qt::DisplayRole);

        aStream >> quYang;
        index = theModel->index(i, 5);
        aItem = theModel->itemFromIndex(index);
        aItem->setCheckState(quYang ? Qt::Checked : Qt::Unchecked);
    }
    aFile.close();
    return true;
}


bool MainWindow::saveBinaryFile(const QString &aFileName)
{
    // 保存为 dat 文件
    QFile aFile(aFileName);
    if (!(aFile.open(QIODevice::WriteOnly)))
        return false;
    QDataStream aStream(&aFile);
    aStream.setByteOrder(QDataStream::LittleEndian); // 小端字节序
    qint16 rowCount = theModel->rowCount();
    qint16 colCount = theModel->columnCount();
    aStream.writeRawData((char*)&rowCount, sizeof(qint16));
    aStream.writeRawData((char*)&colCount, sizeof(qint16));
    // 获取表头文字
    QByteArray btArray;
    QStandardItem *aItem;
    for (int i = 0; i < theModel->columnCount(); ++i)
    {
        aItem = theModel->horizontalHeaderItem(i); // 获取表头 item
        QString str = aItem->text(); // 获取表头文字
        btArray = str.toUtf8();
        aStream.writeBytes(btArray, btArray.length()); // 写入字符串数据
    }
    // 获取表格数据区
    qint8 yes = 1, no = 0; // 分别代表逻辑值 true 和 false
    for (int i = 0; i < theModel->rowCount(); ++i)
    {
        aItem = theModel->item(i, 0);       // 测深
        qint16 ceShen = aItem->data(Qt::DisplayRole).toInt();
        aStream.writeRawData((char*)&ceShen, sizeof(qint16));

        aItem = theModel->item(i, 1);
        qreal chuiShen = aItem->data(Qt::DisplayRole).toFloat();
        aStream.writeRawData((char*)&chuiShen, sizeof(qreal));

        aItem = theModel->item(i, 2);
        qreal fangWei = aItem->data(Qt::DisplayRole).toFloat();
        aStream.writeRawData((char*)&fangWei, sizeof(qreal));

        aItem = theModel->item(i, 3);
        qreal weiYi = aItem->data(Qt::DisplayRole).toFloat();
        aStream.writeRawData((char*)&weiYi, sizeof(qreal));

        aItem = theModel->item(i, 4);
        QString zhiLiang = aItem->data(Qt::DisplayRole).toString();
        QByteArray zhiLiangBtArray = zhiLiang.toUtf8();
        aStream.writeBytes(btArray, btArray.length());

        aItem = theModel->item(i, 5);
        bool quYang  = (aItem->checkState() == Qt::Checked);
        if (quYang)
            aStream.writeRawData((char*)&yes, sizeof(qint8));
        else
            aStream.writeRawData((char*)&no, sizeof(qint8));
    }
    aFile.close();
    return true;
}

bool MainWindow::openBinaryFile(const QString &aFileName)
{
    // 打开 dat 文件
    QFile aFile(aFileName);
    if (!(aFile.open(QIODevice::ReadOnly)))
        return false;
    QDataStream aStream(&aFile);
    aStream.setByteOrder(QDataStream::LittleEndian);

    qint16 rowCount, colCount;
    aStream.readRawData((char*)&rowCount, sizeof(qint16));
    aStream.readRawData((char*)&colCount, sizeof(qint16));
    this->resetTable(rowCount);
    // 读取表头文字，但是并不利用
    char *buf;
    uint strLen;
    for (int i = 0; i < colCount; ++i)
    {
        aStream.readBytes(buf, strLen); // 同时读取字符串长度和字符串内容
        QString str = QString::fromLocal8Bit(buf, strLen);
    }
    // 读取数据区数据
    QStandardItem *aItem;
    qint16 ceShen;
    qreal chuiShen, fangWei, weiYi;
    QString zhiLiang;
    qint8 quYang; // 1=true,0=false
    QModelIndex index;
    for (int i = 0; i < rowCount; ++i)
    {
        aStream.readRawData((char*)&ceShen, sizeof(qint16)); // 测深
        index = theModel->index(i, 0);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(ceShen, Qt::DisplayRole);

        aStream.readRawData((char*)&chuiShen, sizeof(qreal));
        index = theModel->index(i, 1);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(chuiShen, Qt::DisplayRole);

        aStream.readRawData((char*)&fangWei, sizeof(qreal));
        index = theModel->index(i, 2);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(fangWei, Qt::DisplayRole);

        aStream.readRawData((char*)&weiYi, sizeof(qreal));
        index = theModel->index(i, 3);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(weiYi, Qt::DisplayRole);

        aStream.readBytes(buf, strLen); // 古井质量
        zhiLiang = QString::fromUtf8(buf, strLen);
        index = theModel->index(i, 4);
        aItem = theModel->itemFromIndex(index);;
        aItem->setData(zhiLiang, Qt::DisplayRole);

        aStream.readRawData((char*)&quYang, sizeof(quint8));
        index = theModel->index(i, 5);
        aItem = theModel->itemFromIndex(index);
        if (1 == quYang)
            aItem->setCheckState(Qt::Checked);
        else
            aItem->setCheckState(Qt::Unchecked);
    }
    aFile.close();
    return true;
}


QList<QStandardItem *> MainWindow::createRow()
{
    QList<QStandardItem*> aItemList; // 列表
    QStandardItem *aItem;
    for (int i = 0; i < FixedColumnCount - 2; ++i)
    {
        aItem = new QStandardItem("0");
        aItemList << aItem;
    }
    // 倒数第二列，质量
    aItem = new QStandardItem("良");
    aItemList << aItem;
    //最后一列，
    QString str = theModel->headerData(theModel->columnCount() - 1, Qt::Horizontal, Qt::DisplayRole).toString();
    aItem = new QStandardItem(str);
    aItem->setCheckable(true);
    aItem->setCheckState(Qt::Unchecked);
    aItem->setEditable(false);
    aItemList << aItem;
    return aItemList;
}





void MainWindow::on_actOpenStm_triggered()
{
    // 打开 stm 文件
    QString curPath = QDir::currentPath();
    QString fileName =  QFileDialog::getOpenFileName(
        this,
        "打开一个文件",
        curPath,
        "Qt 预定义编码数据文件(*.stm)");
    if (fileName.isEmpty())
        return;
    if (openDataAsStream(fileName))
        QMessageBox::information(this, "提示消息", "文件已打开");
}




void MainWindow::on_actSaveStm_triggered()
{
    // 以Qt预定义编码保存文件
    QString curPath = QDir::currentPath();
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "选择保存的文件",
        curPath,
        "Qt预定义编码数据文件(*.stm)");
    if (fileName.isEmpty())
        return;
    if (saveDataAsStream(fileName))
        QMessageBox::information(this, "提示消息", "文件已成功保存");
}


void MainWindow::on_actOpenDat_triggered()
{
    // 打开 dat 文件
    QString curPath = QDir::currentPath();
    QString fileName =  QFileDialog::getOpenFileName(
        this,
        "打开一个文件",
        curPath,
        "标准编码数据文件(*.dat)");
    if (fileName.isEmpty())
        return;
    if (openBinaryFile(fileName))
        QMessageBox::information(this, "提示消息", "文件已打开");
}

void MainWindow::on_actSaveDat_triggered()
{
    // 保存 dat 文件
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getOpenFileName(
        this,
        "选择保存文件",
        curPath,
        "标准编码数据文件(*.dat);;所有文件(*.*)");
    if (aFileName.isEmpty())
        return;
    if (saveBinaryFile(aFileName))
        QMessageBox::information(this, "提示信息", "文件已经保存成功!");
}



void MainWindow::on_actAppend_triggered()
{
    QList<QStandardItem*> aItemList = createRow();
    theModel->insertRow(theModel->rowCount(), aItemList);

    QModelIndex curIndex = theModel->index(theModel->rowCount() - 1, 0);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}



void MainWindow::on_actReset_triggered()
{
    resetTable(0);
}
