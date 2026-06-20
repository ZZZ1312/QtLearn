#include "qwdialoglocate.h"
#include "ui_qwdialoglocate.h"
#include "mainwindow.h"
#include <QCloseEvent>

QWDialogLocate::QWDialogLocate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QWDialogLocate)
{
    ui->setupUi(this);
}

QWDialogLocate::~QWDialogLocate()
{
    delete ui;
}

void QWDialogLocate::setSpinRange(int rowCount, int colCount)
{
    ui->spinBoxColumn->setRange(0, colCount);
    ui->spinBoxRow->setRange(0, rowCount);
}

void QWDialogLocate::setSpinValue(int rowNo, int colNo)
{
    ui->spinBoxRow->setValue(rowNo);
    ui->spinBoxColumn->setValue(colNo);
}

void QWDialogLocate::on_btnSetText_clicked()
{
    // 定位到单元格，并设置字符串
    int row = ui->spinBoxRow->value(); // 行号
    int col = ui->spinBoxColumn->value(); // 列号
    MainWindow *parWind = static_cast<MainWindow*>(parentWidget()); // 获取主窗口
    parWind->setACellText(row, col, ui->lineEdit->text());
    if (ui->chkRowInc->isChecked())
        ui->spinBoxRow->setValue( 1 + ui->spinBoxRow->value());
    if (ui->chkColInc->isChecked())
        ui->spinBoxColumn->setValue(1 + ui->spinBoxColumn->value());
}

void QWDialogLocate::closeEvent(QCloseEvent *event)
{
    MainWindow *parWind = static_cast<MainWindow*>(parentWidget()); // 获取父窗口指针
    parWind->setActLocateEnabele(true); // 启用 actLocateCell
    parWind->setDlgLocateNull(); // 将窗口指针设置为 nullptr
    event->accept();
}

