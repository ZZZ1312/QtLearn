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


};
#endif // WIDGET_H
