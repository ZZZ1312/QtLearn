#include "widget.h"
#include "./ui_widget.h"
#include <QColorDialog>
#include <QCoreApplication>
#include <QDir>
#include <QFileDialog>
#include <QFontDialog>
#include <QLineEdit>
#include <QInputDialog>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnOpenFile_clicked()
{
    // 打开一个文件，
    QString curPath = QDir::currentPath(); // 获取应用程序当前目录
    QString dlgTitle("选择一个文件");
    QString filter("文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)");
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

    ui->plainTextEdit->appendPlainText(QString("选择的一个文件"));
    if (!aFileName.isEmpty())
        ui->plainTextEdit->appendPlainText(aFileName);
}

void Widget::on_btnOpenFiles_clicked()
{
    // 选择多个文件
    QString curPath = QDir::currentPath();
    QString dlgTitle("选择多个文件");
    QString filter("文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)");
    QStringList fileList = QFileDialog::getOpenFileNames(this, dlgTitle, curPath, filter);
    for (int i =  0; i < fileList.count(); ++i)
        ui->plainTextEdit->appendPlainText(fileList.at(i));
}

void Widget::on_btnSelectDir_clicked()
{
    // 选择文件夹
    QString curPath = QCoreApplication::applicationDirPath();
    QString dlgTitle("选择一个目录");
    QString selectedDir = QFileDialog::getExistingDirectory(
        this,
        dlgTitle,
        curPath,
        QFileDialog::ShowDirsOnly);
    if (!selectedDir.isEmpty())
        ui->plainTextEdit->appendPlainText(selectedDir);
}

void Widget::on_btnSaveFile_clicked()
{
    // 保存文件
    QString curPath = QCoreApplication::applicationDirPath();
    QString dlgTitle("保存文件");
    QString filter("h 文件(*.h);;C++文件(*.cpp);;所有文件(*.*)");
    QString aFileName = QFileDialog::getSaveFileName(
        this,
        dlgTitle,
        curPath,
        filter);
    if (!aFileName.isEmpty())
        ui->plainTextEdit->appendPlainText(aFileName);
}

void Widget::on_btnsSelectColor_clicked()
{
    // 选择颜色
    QPalette pal = ui->plainTextEdit->palette(); // 获取现有 Palette
    QColor iniColor = pal.color(QPalette::Text); // 现有的文字颜色
    QColor color = QColorDialog::getColor(iniColor, this, "选择颜色");
    if (color.isValid())
    {
        pal.setColor(QPalette::Text, color);
        ui->plainTextEdit->setPalette(pal);
    }
}


void Widget::on_btnSelectFont_clicked()
{
    // 选择字体
    QFont iniFont = ui->plainTextEdit->font();
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, iniFont);
    if (ok)
        ui->plainTextEdit->setFont(font);
}


void Widget::on_btnInputString_clicked()
{
    // 输入字符串
    QString dlgTitle("输入文字对话框");
    QString txtLabel("请输入文件名：");
    QString defaultInput("新建文件.txt");
    QLineEdit::EchoMode echoMode = QLineEdit::Normal;
    bool ok = false;
    QString text = QInputDialog::getText(
        this,
        dlgTitle,
        txtLabel,
        echoMode,
        defaultInput,
        &ok);
    if (ok && !text.isEmpty())
        ui->plainTextEdit->appendPlainText(text);
}

void Widget::on_btnInputInt_clicked()
{
    // 输入整数
    QString dlgTitle("输入整数对话框");
    QString txtLabel("设置字体大小：");
    int defaultValue = ui->plainTextEdit->font().pointSize();
    int minValue = 6, maxValue = 50, stepValue = 1;
    bool ok = false;
    int inputValue = QInputDialog::getInt(this, dlgTitle, txtLabel, defaultValue, minValue, maxValue, stepValue, &ok);
    if (ok)
    {
        QFont font = ui->plainTextEdit->font();
        font.setPointSize(inputValue);
        ui->plainTextEdit->setFont(font);
    }
}

void Widget::on_btnInputFloat_clicked() {
    // 输入浮点数
    QString dlgTitle("输入浮点数对话框");
    QString txtLabel("输入一个浮点数：");
    float defaultValue = 3.13;
    float minValue = 0, maxValue = 10000;
    int decimals = 2; // 小数点位数
    bool ok = false;
    float inputValue =
        QInputDialog::getDouble(this, dlgTitle, txtLabel, defaultValue, minValue,
                                               maxValue, decimals, &ok);
    if (ok) {
        QString str = QString::asprintf("输入了一个浮点数:%.2f", inputValue);
        ui->plainTextEdit->appendPlainText(str);
    }
}

void Widget::on_btnInputItem_clicked()
{
    // 条目选择输入
    QStringList items;
    items << "优秀" << "良好" << "合格" << "不合格";
    QString dlgTitle("条目选择对话框");
    QString txtLabel("请选择级别:");
    int curIndex = 0; // 初始选择项
    bool editable = true; // ComboBox是否可编辑
    bool ok = false;
    QString text = QInputDialog::getItem(
        this,
        dlgTitle,
        txtLabel,
        items,
        curIndex,
        editable,
        &ok);
    if (ok && !text.isEmpty())
    {
        QString str = QString("选择的条目: %1").arg(text);
        ui->plainTextEdit->appendPlainText(str);
    }
}

void Widget::on_btnInformation_clicked()
{
    // information
    QString dlgTitle("information消息框");
    QString strInfo("文件已经打开，字体大小已设置");
    QMessageBox::information(this, dlgTitle, strInfo,
                            QMessageBox::Ok, QMessageBox::NoButton);
}

void Widget::on_btnWarning_clicked()
{
    // warning
    QString dlgTitle("warning消息框");
    QString strInfo("文件内容已修改");
    QMessageBox::warning(this, dlgTitle, strInfo);
}

void Widget::on_btnCritical_clicked()
{
    // critical
    QString dlgTitle("critical消息框");
    QString strInfo("有不明程序访问网络");
    QMessageBox::critical(this, dlgTitle, strInfo);
}

void Widget::on_btnAbout_clicked()
{
    // about
    QString dlgTitle("about消息框");
    QString strInfo("我开发的数据查看软件 V1.0\n保留所有版权");
    QMessageBox::about(this, dlgTitle, strInfo);
}

void Widget::on_btnQuestion_clicked()
{
    QString dlgTitle("Question消息框");
    QString strInfo("文件已被修改，是否保存修改？");
    QMessageBox::StandardButton defaultBtn = QMessageBox::NoButton;
    QMessageBox::StandardButton result; // 返回选择的按钮
    result = QMessageBox::question(this, dlgTitle, strInfo,
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                   defaultBtn);
    switch (result)
    {
    case QMessageBox::Yes:
        ui->plainTextEdit->appendPlainText("Question 消息框：Yes被选择");
        break;
    case QMessageBox::No:
        ui->plainTextEdit->appendPlainText("Question 消息框：No被选择");
        break;
    case QMessageBox::Cancel:
        ui->plainTextEdit->appendPlainText("Question 消息框：Cancel 被选择");
        break;
    default:
        ui->plainTextEdit->appendPlainText("Question 消息框：无选择");
    }
}
void Widget::on_btnClearText_clicked()
{
    ui->plainTextEdit->clear();
}

void Widget::on_btnAboutQt_clicked()
{
    // Qt信息
    QMessageBox::aboutQt(this);
}