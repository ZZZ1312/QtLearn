#include "dialog.h"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->rBtnBlue, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(ui->rBtnBlack, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(ui->rBtnRed, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_chkBoxUnder_clicked(bool checked)
{
    QFont font = ui->txtEdit->font();
    font.setUnderline(checked);
    ui->txtEdit->setFont(font);
}


void Dialog::on_checkBoxBold_clicked(bool checked)
{
    QFont font = ui->txtEdit->font();
    font.setBold(checked);
    ui->txtEdit->setFont(font);
}


void Dialog::on_chkBoxItalic_clicked(bool checked)
{
    QFont font = ui->txtEdit->font();
    font.setItalic(checked);
    ui->txtEdit->setFont(font);
}

void Dialog::setTextFontColor()
{
    QPalette palette = ui->txtEdit->palette();
    if (ui->rBtnBlue->isChecked())
        palette.setColor(QPalette::Text, Qt::blue);
    else if (ui->rBtnRed->isChecked())
        palette.setColor(QPalette::Text, Qt::red);
    else if (ui->rBtnBlack->isChecked())
        palette.setColor(QPalette::Text, Qt::black);
    else
        palette.setColor(QPalette::Text, Qt::black);
    ui->txtEdit->setPalette(palette);
}

