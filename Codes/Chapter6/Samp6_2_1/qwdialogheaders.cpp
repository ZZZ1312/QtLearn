#include "qwdialogheaders.h"
#include "ui_qwdialogheaders.h"
#include <QMessageBox>

QWDialogHeaders::QWDialogHeaders(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QWDialogHeaders)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = this->windowFlags();
    this->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);

    model = new QStringListModel;
    ui->listView->setModel(model);
}

QWDialogHeaders::~QWDialogHeaders()
{
    QMessageBox::information(this, "提示", "设置表头标题对话框被删除");
    delete ui;
}

void QWDialogHeaders::setHeaderList(QStringList &header)
{
    model->setStringList(header);
}

QStringList QWDialogHeaders::headerList()
{
    return model->stringList();
}
