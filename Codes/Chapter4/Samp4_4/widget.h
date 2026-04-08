#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPalette>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
private:
    Ui::Widget *ui;

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;


private slots:
    void on_sliderRed_valueChanged(int value);
    void on_dial_valueChanged(int value);
    void on_radioDec_clicked();
    void on_radioBin_clicked();
    void on_radioOct_clicked();
    void on_radioHex_clicked();
};
#endif // WIDGET_H
