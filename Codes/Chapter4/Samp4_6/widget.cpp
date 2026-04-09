#include "widget.h"
#include "./ui_widget.h"
#include <QMap>
#include <QTextBlock>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->comboSimple->setEditable(false);
    ui->chkTextReadOnly->setChecked(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnInit_clicked()
{
    // 初始化列表
    ui->comboSimple->clear();
    for (int i = 0 ; i < 20; ++i)
        ui->comboSimple->addItem(QString::asprintf("Item %d", i));
}



void Widget::on_btnClearItems_clicked()
{
    ui->comboSimple->clear();
}

void Widget::on_btnInitCityAndNo_clicked()
{
    static QMap<QString, int> cityZoneMap;
    if (cityZoneMap.isEmpty())
    {
        cityZoneMap.insert("北京", 10);
        cityZoneMap.insert("上海", 21);
        cityZoneMap.insert("天津", 22);
        cityZoneMap.insert("大连", 411);
        cityZoneMap.insert("锦州", 416);
        cityZoneMap.insert("徐州", 516);
        cityZoneMap.insert("福州", 591);
        cityZoneMap.insert("青岛", 532);
    }

    ui->comboCityAndNo->clear();
    foreach(const QString &str, cityZoneMap.keys())
    {
        ui->comboCityAndNo->addItem(str, cityZoneMap.value(str));
    }
}


void Widget::on_comboSimple_currentTextChanged(const QString &arg1)
{
    ui->txtEdit->appendPlainText(arg1);
}


void Widget::on_comboCityAndNo_currentTextChanged(const QString &arg1)
{
    QString zone = ui->comboCityAndNo->currentData().toString(); // 关联的数据
    ui->txtEdit->appendPlainText(arg1 + ":区号="+zone);
}


void Widget::on_chkWritable_toggled(bool checked)
{
    ui->comboSimple->setEditable(checked);
}


void Widget::on_chkTextReadOnly_toggled(bool checked)
{
    ui->txtEdit->setEnabled(!checked);
}


void Widget::on_btnContentToItems_clicked()
{
    // 文本框中内容逐行添加为comboSimple的项
    QTextDocument *doc = ui->txtEdit->document(); // 文本对象
    int cnt = doc->blockCount(); // 两个回车符之间是一个block
    ui->comboSimple->clear();
    for (int i = 0; i < cnt; ++i)
    {
        QTextBlock textLine = doc->findBlockByLineNumber(i); // 文本中的一段
        QString string = textLine.text();
        ui->comboSimple->addItem(string);
    }
}


void Widget::on_btnClearText_clicked()
{
    // 清除文本框内容
    ui->txtEdit->clear();
}

