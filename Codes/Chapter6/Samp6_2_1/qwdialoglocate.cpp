#include "qwdialoglocate.h"
#include "ui_qwdialoglocate.h"

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

void QWDialogLocate::closeEvent(QCloseEvent *event)
{
    // 窗口关闭事件，发射信号使 actLocateCell 启用
    emit changeActionEnable(true);
}

void QWDialogLocate::showEvent(QCloseEvent *event)
{
    // 窗口显示事件，发射信号使 actLocateCell 禁用
    emit changeActionEnable(false);
}

void QWDialogLocate::on_btnSetText_clicked()
{
    // 发射信号，定位到单元格并设置字符串
    int row = ui->spinRow->value(); // 行号
    int col = ui->spinColumn->value(); // 列号
    QString text = ui->lineEdit->text(); // 文字
    emit changeCellText(row, col, text); // 发射信号
    if (ui->chkRowInc->isChecked())
    {
        int value = ui->spinRow->value();
        int newValue = value + 1;
        if (newValue < ui->spinRow->maximum()){
            ui->spinRow->setValue(newValue);
        }
    }
    if (ui->chkColInc->isChecked())
    {
        int value = ui->spinColumn->value();
        int newValue = ++value;
        if (newValue < ui->spinColumn->maximum())
            ui->spinColumn->setValue(newValue);
    }
}

void QWDialogLocate::setSpinRange(int rowCount, int colCount)
{
    // 响应主窗口信号，更新 spinBox 的值
    ui->spinColumn->setRange(0,colCount);
    ui->spinRow->setRange(0, rowCount);
}

void QWDialogLocate::setSpinValue(int rowNo, int colNo)
{
    ui->spinColumn->setValue(colNo);
    ui->spinRow->setValue(rowNo);
}
