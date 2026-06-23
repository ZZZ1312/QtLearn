#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    ui->tabWidget->clear();
    ui->tabWidget->setTabsClosable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::openTextByIODevice(const QString &aFileName)
{
    //用IODevice的方式打开文件
    QFile aFile(aFileName);
    if (!aFile.exists()) // 文件不存在
    {
        QMessageBox::warning(this, "警告", "文件不存在");
        return false;
    }

    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "警告", "无法打开指定文件");
        return false;
    }

    QPlainTextEdit *edit = new QPlainTextEdit();
    edit->setPlainText(aFile.readAll());

    QFileInfo fileInfo(aFile);
    QString pureFileName = fileInfo.fileName();
    ui->tabWidget->addTab(edit, pureFileName);
    aFile.close();
    return true;
}

void MainWindow::on_actOpen_triggered()
{
    // 打开文件
    QString curPath = QDir::currentPath();
    QString dlgTitle("打开一个文件");
    QString filter("程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)");
    QString aFileName = QFileDialog::getOpenFileName(this,
                                                     dlgTitle,
                                                     curPath,
                                                     filter);
    if (aFileName.isEmpty())
    {
        QMessageBox::warning(this, "警告", "未选择文件");
        return;
    }

    openTextByIODevice(aFileName);
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    QWidget *widget = ui->tabWidget->widget(index);

    ui->tabWidget->removeTab(index);
    widget->deleteLater();
}

bool MainWindow::saveTextByIODevice(const QString &fullPath)
{
    // 用 IODevice 方式保存文本文件
    QFile aFile(fullPath);
    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }
    QPlainTextEdit *plainTextEdit = static_cast<QPlainTextEdit*>(ui->tabWidget->currentWidget());
    QString content = plainTextEdit->toPlainText();
    QByteArray contentBytes = content.toUtf8();
    aFile.write(contentBytes, contentBytes.length());
    aFile.close();
    return true;
}
void MainWindow::on_actSaveOther_triggered()
{
    // QFile另存为
    QString curPath = QDir::currentPath();
    QString dlgTitle{"另存为一个文件"};
    QString filter{"h文件(*.h);;c++文件(*.cpp);;所有文件(*.*)"};
    QString fullPath = QFileDialog::getSaveFileName(
        this, dlgTitle, curPath, filter);
    if (fullPath.isEmpty())
        return;
    saveTextByIODevice(fullPath);
}

bool MainWindow::openTextByStream(const QString& fullPath)
{
    // 用 QTextStream 打开文本文件
    QFile aFile(fullPath);
    if (!aFile.exists()) // 文件不存在
    {
        return false;
    }

    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream aStream(&aFile); // 用文本流读取文件
    aStream.setAutoDetectUnicode(true); // 自动检测 Unicode，才能显示汉字

    QPlainTextEdit *editor = new QPlainTextEdit{};
    editor->setPlainText(aStream.readAll());

    QFileInfo fileInfo(aFile);
    QString pureFileName = fileInfo.fileName();
    ui->tabWidget->addTab(editor, pureFileName);
    aFile.close();
    return true;
}

void MainWindow::on_actStreamOpen_triggered()
{
    // 用 QTextStream 打开文本文件
    // 打开文件
    QString curPath = QDir::currentPath();
    QString dlgTitle("打开一个文件");
    QString filter("程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)");
    QString aFileName = QFileDialog::getOpenFileName(this,
                                                     dlgTitle,
                                                     curPath,
                                                     filter);
    if (aFileName.isEmpty())
    {
        QMessageBox::warning(this, "警告", "未选择文件");
        return;
    }

    openTextByStream(aFileName);
}

bool MainWindow::saveTextByStream(const QString &fullPath)
{
    // 用 QTextStream 保存文本文件
    QFile aFile(fullPath);
    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream aStream(&aFile); // 用文本流读取文件
    aStream.setAutoDetectUnicode(true); // 自动检测 Unicode
    QPlainTextEdit *editor = static_cast<QPlainTextEdit*>(ui->tabWidget->currentWidget());
    QString content = editor->toPlainText();
    aStream << content;
    aFile.close();
    return true;
}

void MainWindow::on_actStreamSaveOther_triggered()
{
    // QFile另存为
    QString curPath = QDir::currentPath();
    QString dlgTitle{"另存为一个文件"};
    QString filter{"h文件(*.h);;c++文件(*.cpp);;所有文件(*.*)"};
    QString fullPath = QFileDialog::getSaveFileName(
        this, dlgTitle, curPath, filter);
    if (fullPath.isEmpty())
        return;
    saveTextByStream(fullPath);
}

