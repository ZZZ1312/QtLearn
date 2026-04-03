#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private slots:
    void on_btnCal_clicked();

    void on_btnDecTrans_clicked();

    void on_btnBinTrans_clicked();

    void on_btnHexTrans_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
