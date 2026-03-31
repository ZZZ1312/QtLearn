#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUi();
    iniSignalSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUi()
{
    // 状态栏上添加组件
    fLabCurFile = new QLabel;
    fLabCurFile->setMinimumWidth(150);
    fLabCurFile->setText(tr("当前文件: "));
    ui->statusbar->addWidget(fLabCurFile); // 添加到状态栏

    progressBar1 = new QProgressBar;
    progressBar1->setMaximumWidth(200);
    progressBar1->setMinimum(5);
    progressBar1->setMaximum(50);
    ui->statusbar->addWidget(progressBar1); // 添加到状态栏

    // 工具栏上添加组件
    spinFontSize = new QSpinBox;
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(50);
    spinFontSize->setMinimumWidth(50);
    ui->toolBar->addWidget(new QLabel("字体大小: "));
    ui->toolBar->addWidget(spinFontSize); // SpinBox 添加到工具栏

    ui->toolBar->addSeparator(); // 分隔条
    ui->toolBar->addWidget(new QLabel("字体: "));

    comboFont = new QFontComboBox;
    comboFont->setMinimumWidth(150);
    ui->toolBar->addWidget(comboFont); // 添加到工具栏


    // 初始化数据
    spinFontSize->setValue(ui->txtEdit->font().pointSize());
    progressBar1->setValue(ui->txtEdit->font().pointSize());
    on_txtEdit_copyAvailable(false);
}

void MainWindow::iniSignalSlots()
{
    // 信号与槽的关联
    connect(spinFontSize, SIGNAL(valueChanged(int)), this, SLOT(on_spinFontSize_valueChanged(int)));
    connect(comboFont, SIGNAL(currentTextChanged(const QString &)), this, SLOT(on_comboFont_currentTextChanged(const QString &)));
}

void MainWindow::on_actFontBold_triggered(bool checked)
{
    QTextCharFormat fmt = ui->txtEdit->currentCharFormat();
    if (checked)
        fmt.setFontWeight(QFont::Bold);
    else
        fmt.setFontWeight(QFont::Normal);
    ui->txtEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_txtEdit_copyAvailable(bool b)
{
    // 更新 cut, copy, paste 的enabled属性
    ui->actCut->setEnabled(b);
    ui->actCopy->setEnabled(b);
    ui->actPaste->setEnabled(ui->txtEdit->canPaste());
}

void MainWindow::on_txtEdit_selectionChanged()
{
    // 更新粗体、斜体和下划线3种action的checked属性
    QTextCharFormat fmt;
    fmt = ui->txtEdit->currentCharFormat(); // 获取文字格式
    ui->actFontItalic->setCheckable(fmt.fontItalic()); // 是否斜体
    ui->actFontBold->setChecked(fmt.font().bold()); // 是否粗体
    ui->actFontUnder->setChecked(fmt.fontUnderline()); // 是否有下划线
}

void MainWindow::on_spinFontSize_valueChanged(int aFontSize)
{
    // 改变字体大小的 SpinBox
    QTextCharFormat fmt;
    fmt.setFontPointSize(aFontSize); // 设置字体大小
    ui->txtEdit->mergeCurrentCharFormat(fmt);
    progressBar1->setValue(aFontSize);
}

void MainWindow::on_comboFont_currentTextChanged(const QString &arg)
{
    // FontComboBox的响应，选择字体名称
    QTextCharFormat fmt;
    QStringList fontFamilies;
    fontFamilies << arg;
    fmt.setFontFamilies(fontFamilies);
    ui->txtEdit->mergeCurrentCharFormat(fmt);
}


