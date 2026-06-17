#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QHBoxLayout>
#include <QFileDialog>
#include <QRegularExpression >
#include "qwintspindelegate.h"
#include "qwfloatspindelegate.h"
#include "qwcomboboxdelegate.h"

static const int FixedColumnCount = 6;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);

    theModel = new QStandardItemModel(0, FixedColumnCount, this); // 数据模型
    theSelection = new QItemSelectionModel(theModel); // 选择模型

    connect(theSelection, SIGNAL(currentChanged(QModelIndex, QModelIndex)),
            this, SLOT(on_currentChanged(QModelIndex,QModelIndex)));

    ui->tableView->setModel(theModel); // 设置数据模型
    ui->tableView->setSelectionModel(theSelection); // 设置选择模型
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    LabCurFile = new QLabel();
    // LabCurFile->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    LabCellPos = new QLabel();
    // LabCellPos->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    LabCellText = new QLabel();
    // LabCellText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    statusBar()->addWidget(LabCurFile,1);
    statusBar()->addWidget(LabCellPos,1);
    statusBar()->addWidget(LabCellText,1);

    // 设置代理
    this->intSpinDelegate = new QWIntSpinDelegate();
    this->floatSpinDelegate = new QWFloatSpinDelegate();
    this->comboBoxDelegate = new QWComboBoxDelegate();
    ui->tableView->setItemDelegateForColumn(0, intSpinDelegate);
    ui->tableView->setItemDelegateForColumn(1, floatSpinDelegate);
    ui->tableView->setItemDelegateForColumn(2, floatSpinDelegate);
    ui->tableView->setItemDelegateForColumn(3, floatSpinDelegate);
    ui->tableView->setItemDelegateForColumn(4, comboBoxDelegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initModelFromStringList(QStringList &aFileContent)
{
    // 从一个StringList获取数据，初始化数据模型
    int rowCount = aFileContent.count(); // 文本行数，第1行是标题
    theModel->setRowCount(rowCount - 1);
    // 设置表头，一个或多个空格、TAB等分隔符隔开的字符串，分解为一个StringList
    QString header = aFileContent.at(0); // 第1行是表头
    QStringList headerList = header.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    theModel->setHorizontalHeaderLabels(headerList); // 设置表头文字


    // 设置表格数据
    QStandardItem *aItem;
    QStringList tmpList;

    int j;
    for(int i = 1; i < rowCount; ++i)
    {
        QString aLineText = aFileContent.at(i);
        tmpList = aLineText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        for (j = 0; j < FixedColumnCount - 1;++j)
        {
            // 不包含最后一列
            aItem = new QStandardItem(tmpList.at(j));
            theModel->setItem(i-1, j, aItem); // 为模型的某个行列位置设置Item
        }
        aItem = new QStandardItem(headerList.at(j)); // 最后一列
        aItem->setCheckable(true); // 设置为可选中
        if (tmpList.at(j) == "0")
            aItem->setCheckState(Qt::Unchecked);
        else
            aItem->setCheckState(Qt::Checked);
        theModel->setItem(i-1,j,aItem);
    }
}

void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    // 选择单元格变化时的响应
    if (current.isValid())
    {
        LabCellPos->setText(QString::asprintf("当前单元格: %d 行, %d 列", current.row(), current.column()));
        QStandardItem *aItem = theModel->itemFromIndex(current);
        this->LabCellText->setText(QString("单元格内容:%1").arg( aItem->text()));
        QFont font = aItem->font();
        ui->actBold->setChecked(font.bold());
    }
}

void MainWindow::on_actOpenFile_triggered()
{
    // 打开文件
    QString curPath = QCoreApplication::applicationDirPath();
    QString aFileName = QFileDialog::getOpenFileName(this, "打开一个文件", curPath, "井数据文件(*.txt);;所有文件(*.*)");

    if (aFileName.isEmpty())
        return;

    QStringList fFileContent;
    QFile aFile(aFileName);

    if (aFile.open(QIODevice::ReadOnly | QIODevice::Text))  // 打开文件
    {
        QTextStream aStream(&aFile); // 用文本流读取文件
        ui->plainTextEdit->clear();
        while (!aStream.atEnd())
        {
            QString str = aStream.readLine();
            ui->plainTextEdit->appendPlainText(str);
            fFileContent.append(str);
        }
        aFile.close();
        this->LabCurFile->setText(QString("当前文件:%1").arg(aFileName)); // 状态栏显示
        initModelFromStringList(fFileContent); // 初始化数据模型
    }
}


void MainWindow::on_actAppend_triggered()
{
    // 在表格最后添加行
    QList<QStandardItem *> aItemList; // 列表类
    QStandardItem *aItem;
    for (int i = 0; i < FixedColumnCount -1; ++i) // 不包含最后1列
    {
        aItem = new QStandardItem("0"); // 创建Item
        aItemList << aItem; // 添加到列表
    }
    // 获取最后一列的表头文字
    QString str = theModel->headerData(theModel->columnCount() - 1, Qt::Horizontal,Qt::DisplayRole).toString();
    aItem = new QStandardItem(str); // 创建 "测井取样" Item
    aItem->setCheckable(true);
    aItemList << aItem; // 添加掉列表

    theModel->insertRow(theModel->rowCount(), aItemList); // 插入一行
    QModelIndex curIndex = theModel->index(theModel->rowCount() - 1, 0);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}


void MainWindow::on_actInsert_triggered()
{
    QList<QStandardItem *> aItemList; // 列表类
    QStandardItem *aItem;
    for (int i = 0; i < FixedColumnCount -1; ++i) // 不包含最后1列
    {
        aItem = new QStandardItem("0"); // 创建Item
        aItemList << aItem; // 添加到列表
    }
    // 获取最后一列的表头文字
    QString str = theModel->headerData(theModel->columnCount() - 1, Qt::Horizontal,Qt::DisplayRole).toString();
    aItem = new QStandardItem(str); // 创建 "测井取样" Item
    aItem->setCheckable(true);
    aItemList << aItem; // 添加掉列表

    QModelIndex index = theSelection->currentIndex();

    theModel->insertRow(index.row(), aItemList); // 插入一行
    theSelection->clearSelection();
    theSelection->setCurrentIndex(index, QItemSelectionModel::Select);
}


void MainWindow::on_actRemove_triggered()
{
    // 删除行
    QModelIndex curIndex = theSelection->currentIndex(); // 获取索引模型
    if (curIndex.row() == theModel->rowCount() - 1) // 最后一行
        theModel->removeRow(curIndex.row());
    else
    {
        theModel->removeRow(curIndex.row()); // 删除一行，并重新设置当前选择行
        theSelection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
    }
}


void MainWindow::setTextAlignment(Qt::AlignmentFlag flag)
{
    // 设置文字对齐
    if (!theSelection->hasSelection())
        return;
    // 获取选择的单元格的模型索引列表，可以是多选
    QModelIndexList selectedIndex = theSelection->selectedIndexes();
    for (int i = 0; i < selectedIndex.count(); ++i)
    {
        QModelIndex aIndex = selectedIndex.at(i); // 获取一个模型索引
        QStandardItem *aItem = theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(flag | Qt::AlignVCenter); // 设置文字对齐方式
    }
}

void MainWindow::on_actLeft_triggered()
{
     setTextAlignment(Qt::AlignLeft);
}

void MainWindow::on_actCenter_triggered()
{
    setTextAlignment(Qt::AlignHCenter);
}

void MainWindow::on_actRight_triggered()
{
    setTextAlignment(Qt::AlignRight);
}

void MainWindow::on_actBold_triggered(bool checked)
{
    // 设置字体粗体
    if (!theSelection->hasSelection())
        return;
    QModelIndexList selectedIndex = theSelection->selectedIndexes();
    for (int i = 0; i < selectedIndex.count(); ++i)
    {
        QModelIndex aIndex = selectedIndex.at(i); // 获取一个模型索引
        QStandardItem *aItem = theModel->itemFromIndex(aIndex); // 获取项数据
        QFont font = aItem->font();
        font.setBold(checked);
        aItem->setFont(font);
    }
}


void MainWindow::on_actQuit_triggered()
{
    this->close();
}


void MainWindow::on_actSaveAs_triggered()
{
    // 保存为文件
    QString curPath = QCoreApplication::applicationDirPath();
    QString aFileName = QFileDialog::getSaveFileName(this, "选择一个文件", curPath, "井斜数据文件(*.txt);;所有文件(*.*)");
    if (aFileName.isEmpty())
        return;

    QFile aFile(aFileName);
    if(!(aFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)))
        return; // 以读写、覆盖原有内容方式打开文件

    QTextStream aStream(&aFile);
    QStandardItem *aItem;
    int i, j;
    QString str;
    ui->plainTextEdit->clear();
    // 获取表头文字
    for (i = 0; i < theModel->columnCount(); ++i)
    {
        aItem = theModel->horizontalHeaderItem(i); // 获取表头的项数据
        str = str + aItem->text() + "\t\t"; // 以 TAB 隔开
    }

    aStream << str << "\n"; // 文件里需要加入换行符 \n
    ui->plainTextEdit->appendPlainText(str);
    // 获取数据区文字
    for (i = 0; i < theModel->rowCount(); ++i)
    {
        str = "";
        for (j = 0; j < theModel->columnCount() - 1; ++j)
        {
            aItem = theModel->item(i,j);
            str = str+aItem->text() + QString::asprintf("\t\t");
        }
        aItem = theModel->item(i,j); // 最后一列是逻辑型
        if (aItem->checkState() == Qt::Checked)
            str = str + "1";
        else
            str = str + "0";
        ui->plainTextEdit->appendPlainText(str);
        aStream << str << "\n";
    }
}


void MainWindow::on_actPreview_triggered()
{
    // 数据模型预览
}

