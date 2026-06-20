#include "qformdoc.h"
#include "ui_qformdoc.h"
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>

QFormDoc::QFormDoc(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QFormDoc)
{
    ui->setupUi(this);

    this->setWindowTitle("New Doc"); // 窗口标题
    this->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除
}

QFormDoc::~QFormDoc()
{
    QMessageBox::information(this, "消息", "文档窗口被释放");
    delete ui;
}

void QFormDoc::loadFormFile(const QString &aFileName)
{
    // 打开文件
    QFile aFile(aFileName);
    if (aFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream aStream(&aFile); // 用文本流读取文件
        ui->plainTextEdit->clear();
        ui->plainTextEdit->setPlainText(aStream.readAll()); // 读取文本文件
        aFile.close();
        mCurrentFile = aFileName; // 保存当前文件名
        QFileInfo fileInfo(aFileName); // 文件信息
        QString str = fileInfo.fileName(); // 去除路径后的文件名
        this->setWindowTitle(str);
        mFileOpened = true;
    }
}

QString QFormDoc::currentFileName()
{
    return mCurrentFile;
}

bool QFormDoc::isFileOpened()
{
    return mFileOpened;
}

void QFormDoc::textCut()
{
    ui->plainTextEdit->cut();
}

void QFormDoc::textCopy()
{
    ui->plainTextEdit->copy();
}

void QFormDoc::textPaste()
{
    ui->plainTextEdit->paste();
}


