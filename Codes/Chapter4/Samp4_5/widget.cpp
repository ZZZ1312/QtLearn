#include "widget.h"
#include "./ui_widget.h"
#include <QDateTime>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    fTimer = new QTimer(this);
    fTimer->stop();
    fTimer->setInterval(1000); // 设置定时周期，单位：毫秒
    ui->spinInterval->setValue(1000);
    ui->btnTimerStop->setEnabled(false);
    connect(fTimer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));

    ui->progressBar->setValue(0);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnCurrentDateTime_clicked()
{
    // 获取当前日期时间，为三个专用编辑器设置日期时间数据，并转换为字符串
    QDateTime currentDateTime = QDateTime::currentDateTime();
    ui->timeEdit->setTime(currentDateTime.time());
    ui->editTime->setText(currentDateTime.toString("hh:mm:ss"));
    ui->dateEdit->setDate(currentDateTime.date());
    ui->editDate->setText(currentDateTime.toString("yyyy-MM-dd"));
    ui->dateTimeEdit->setDateTime(currentDateTime);
    ui->editDateTime->setText(currentDateTime.toString("yyyy-MM-dd hh:mm:ss"));
}


void Widget::on_btnSetDateTime_clicked()
{
    // 字符串转换为QDateTime
    QString str = ui->editDateTime->text();
    str = str.trimmed();
    if (!str.isEmpty())
    {
        QDateTime dateTime = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");
        ui->dateTimeEdit->setDateTime(dateTime);
    }
}


void Widget::on_calendarWidget_selectionChanged()
{
    // 在日历上选择日期
    QDate date = ui->calendarWidget->selectedDate();
    QString str = date.toString("yyyy年M月d日");
    ui->editCalendar->setText(str);
}

void Widget::on_timer_timeout()
{
    // 定时器响应中断
    QTime currentTime = QTime::currentTime(); // 获取当前时间
    ui->lcdHour->display(currentTime.hour()); // 显示 小时
    ui->lcdMinutes->display(currentTime.minute()); // 显示 分钟
    ui->lcdSeconds->display(currentTime.second()); // 显示 秒
    int value = ui->progressBar->value();

    ++value;
    if (value > 100)
        value = 0;
    ui->progressBar->setValue(value);
}


void Widget::on_btnTimerStart_clicked()
{
    // 启动定时器
    fTimer->start();
    if (!fTimeCounter.isValid())
        fTimeCounter.start();


    // 设置当前的定时期周期
    ui->spinInterval->setValue(fTimer->interval());
    ui->btnTimerStart->setEnabled(false);
    ui->btnTimerStop->setEnabled(true);
    ui->btnSetTimerValue->setEnabled(false);
}


void Widget::on_btnTimerStop_clicked()
{
    // 停止定时器
    fTimer->stop();
    int tmMesc = fTimeCounter.elapsed();
    int ms = tmMesc % 1000;
    int sec = tmMesc / 1000;
    QString str = QString::asprintf("流逝时间: %d 秒, %d 毫秒", sec, ms);
    ui->labElapsedTime->setText(str);
    ui->btnTimerStart->setEnabled(true);
    ui->btnTimerStop->setEnabled(false);
    ui->btnSetTimerValue->setEnabled(true);
}


void Widget::on_btnSetTimerValue_clicked()
{
    int ms = ui->spinInterval->value();
    fTimer->setInterval(ms);
}

