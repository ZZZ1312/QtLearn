#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDate>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitterMain);
    // 状态栏初始化创建
    labCellIndex = new QLabel("当前单元格坐标: ", this);
    labCellIndex->setMinimumWidth(250);
    labCellType = new QLabel("当前单元格类型: ", this);
    labCellType->setMinimumWidth(200);
    labStudID = new QLabel("学生ID: ", this);
    labStudID->setMinimumWidth(200);

    ui->statusbar->addWidget(labCellIndex);
    ui->statusbar->addWidget(labCellType);
    ui->statusbar->addWidget(labStudID);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->chkEditable->setChecked(true);
    ui->chkRowHeader->setChecked(true);
    ui->chkColumnHeader->setChecked(true);
    ui->chkDiffLine->setChecked(false);
    ui->rBtnRowSelectable->setChecked(true);
    ui->spinLineNumber->setValue(20);

    on_rBtnRowSelectable_clicked();
    on_chkEditable_toggled(true);
    on_chkRowHeader_clicked(true);
    on_chkColumnHeader_clicked(true);
    on_chkDiffLine_clicked(false);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSetHeader_clicked()
{
    // 设置表头
    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText << "姓 名" << "性 别" << "出生日期" << "民 族" << "分数" << "是否党员";
    ui->tableWidget->setColumnCount(headerText.length());
    for (int i = 0; i < ui->tableWidget->columnCount(); ++i)
    {
        headerItem = new QTableWidgetItem(headerText.at(i));
        QFont font = headerItem->font();
        font.setBold(true);
        font.setPointSize(12);

        headerItem->setForeground(QBrush(Qt::red)); // 字体颜色
        headerItem->setFont(font); // 设置字体
        ui->tableWidget->setHorizontalHeaderItem(i, headerItem);
    }
}


void MainWindow::on_btnInitTableData_clicked()
{
    // 初始化表格数据
    QString strName, strSex;
    bool isParty = false;
    QDate birth;
    birth.setDate(1980, 4, 7); // 初始化一个日期
    ui->tableWidget->clearContents(); // 只清除工作区，不清除表头
    int rows = ui->tableWidget->rowCount(); // 数据区行数
    for (int i = 0; i < rows; ++i)
    {
        strName = QString::asprintf("学生%d", i);
        strSex = ((i % 2) == 0) ? "男" : "女";
        createItemARow(i, strName, strSex, birth, "汉族", isParty, 70);
        birth = birth.addDays(20);
        isParty = !isParty;
    }

}

void MainWindow::createItemARow(int rowNo, const QString &name, const QString &sex, const QDate &brith, const QString &nation, bool isPM, int score)
{
    // 为一行的单元格创建Items
    QTableWidgetItem *item;
    QString str;
    uint StudID = 201605000; // 学号基数
    // 姓名
    item = new QTableWidgetItem(name, MainWindow::ctName);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    StudID += rowNo; // 学号 = 基数 + 行号
    item->setData(Qt::UserRole, QVariant(StudID));
    ui->tableWidget->setItem(rowNo, MainWindow::colName, item);
    // 性别
    QString iconPath(":/images/icons/");
    iconPath += (sex == "男") ? "male.png" : "female.png";
    QIcon icon(iconPath);
    item = new QTableWidgetItem(sex, MainWindow::ctSex);
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo, MainWindow::colSex, item);
    // 出生日期
    str = brith.toString("yyyy-MM-dd");
    item = new QTableWidgetItem(str, MainWindow::ctBrith);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo, MainWindow::colBrith, item);
    // 民族
    item = new QTableWidgetItem(nation, MainWindow::ctNation);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo, MainWindow::colNation, item);
    // 是否党员
    item = new QTableWidgetItem("党员", MainWindow::ctPartyM);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    Qt::CheckState checkStatus = isPM ? Qt::Checked : Qt::Unchecked;
    item->setCheckState(checkStatus);
    item->setBackground(Qt::yellow);
    ui->tableWidget->setItem(rowNo, MainWindow::colPartM, item);
    // 分数
    str.setNum(score);
    item = new QTableWidgetItem(str, MainWindow::ctScore);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(rowNo, MainWindow::colScore, item);
    if (ui->tableWidget->rowCount() > 0)
        ui->tableWidget->selectRow(0);
}


void MainWindow::on_btnSetRow_clicked()
{
    // 设置行数
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(ui->spinLineNumber->value());
}

void MainWindow::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    // 当前选择单元格发生变化时的响应
    QTableWidgetItem *item = ui->tableWidget->item(currentRow, currentColumn);
    if (item == nullptr)
        return;
    labCellIndex->setText(QString::asprintf("当前单元格坐标: %d行, %d列", currentRow, currentColumn));
    int cellType = item->type(); // 获取单元格的类型
    labCellType->setText(QString::asprintf("当前单元格类型: %d", cellType));
    item = ui->tableWidget->item(currentRow, MainWindow::colName); // 第1列的item
    int ID = item->data(Qt::UserRole).toInt(); // 读取用户自定义数据
    labStudID->setText(QString::asprintf("学生ID: %d", ID));
}


void MainWindow::on_btnInsert_clicked()
{
    // 插入一行
    int curRow = ui->tableWidget->currentRow();
    ui->tableWidget->insertRow(curRow);
    createItemARow(curRow, "新学生", "男", QDate::fromString("1990-1-1", "yyyy-M-d"), "苗族", true);
    ui->tableWidget->selectRow(curRow);
}


void MainWindow::on_btnAppend_clicked()
{
    // 末尾追加一行
    int curRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(curRow);
    createItemARow(curRow, "新生", "女",
        QDate::fromString("2000-1-1", "yyyy-M-d"), "壮族", false);
    ui->tableWidget->selectRow(curRow);
}


void MainWindow::on_btnDelete_clicked()
{
    // 删除当前行及其items
    int curRow = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(curRow); // 删除当前行及其items
    int rowCount = ui->tableWidget->rowCount();
    if (curRow < rowCount)
        ui->tableWidget->selectRow(curRow);
    else
        if (rowCount > 0)
            ui->tableWidget->selectRow(rowCount - 1);
}


void MainWindow::on_chkEditable_toggled(bool checked)
{
    // 设置编辑模式
    if (checked)
        ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked |
                                         QAbstractItemView::SelectedClicked);
    else
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}



void MainWindow::on_chkRowHeader_clicked(bool checked)
{
    // 是否显示行表头
    ui->tableWidget->horizontalHeader()->setVisible(checked);
}


void MainWindow::on_chkColumnHeader_clicked(bool checked)
{
    // 是否显示列表头
    ui->tableWidget->verticalHeader()->setVisible(checked);
}


void MainWindow::on_chkDiffLine_clicked(bool checked)
{
    // 间隔行底色
    ui->tableWidget->setAlternatingRowColors(checked);
}


void MainWindow::on_rBtnRowSelectable_clicked()
{
    // 行选择模式
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void MainWindow::on_rBtnColumnSelectable_clicked()
{
    // 列选择模式
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
}


void MainWindow::on_btnTableToText_clicked()
{
    // 将所有单元格的内容提取字符串，显示在PlainTextEdit组件里
    QString str;
    QTableWidgetItem *cellItem;
    ui->plainTextEdit->clear();
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        str = QString::asprintf("第 %d 行: ", i+1);
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j)
        {
            cellItem = ui->tableWidget->item(i, j); // 获取单元格的Item
            str += cellItem->text() + "    "; // 字符串链接
        }
        cellItem = ui->tableWidget->item(i, colPartM); // 最后一列
        if (cellItem->checkState() == Qt::Checked)
            str += "党员";
        else
            str += "群众";
        ui->plainTextEdit->appendPlainText(str);
    }

}

