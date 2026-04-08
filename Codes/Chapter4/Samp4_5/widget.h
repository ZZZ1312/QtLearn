#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
private:
    QTimer *fTimer; // 定时器
    QElapsedTimer fTimeCounter; // 计时器
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private slots:
    void on_btnCurrentDateTime_clicked();

    void on_btnSetDateTime_clicked();

    void on_calendarWidget_selectionChanged();

    void on_timer_timeout(); // 定时器到时间处理槽函数

    void on_btnTimerStart_clicked();

    void on_btnTimerStop_clicked();

    void on_btnSetTimerValue_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
