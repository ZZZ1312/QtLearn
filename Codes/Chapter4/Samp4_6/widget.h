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
    void on_btnInit_clicked();

    void on_btnClearItems_clicked();

    void on_btnInitCityAndNo_clicked();


    void on_comboSimple_currentTextChanged(const QString &arg1);

    void on_comboCityAndNo_currentTextChanged(const QString &arg1);

    void on_chkWritable_toggled(bool checked);

    void on_chkTextReadOnly_toggled(bool checked);

    void on_btnContentToItems_clicked();

    void on_btnClearText_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
