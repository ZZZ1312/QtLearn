#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <memory>
QT_BEGIN_NAMESPACE
namespace Ui {
    class Widget;
}
QT_END_NAMESPACE
class CPerson;

class Widget : public QWidget
{
    Q_OBJECT
private:
    std::unique_ptr<CPerson> boy;
    std::unique_ptr<CPerson> girl;

private slots:
    void on_ageChanged(int value);
    void on_spin_valueChanged(int arg1);
    //  界面按钮的槽函数
    void on_btnClear_clicked();
    void on_btnBoyInc_clicked();
    void on_btnGirlInc_clicked();
    void on_btnClassInfo_clicked();

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
