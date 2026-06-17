#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringListModel>

class Counter;

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
    void on_btnAddItem_clicked();

    void on_btnInsertItem_clicked();

    void on_btnDeleteItem_clicked();

    void on_btnClear_clicked();

    void on_btnShow_clicked();

    void on_btnClearText_clicked();

    void on_listView_clicked(const QModelIndex &index);

public:
    QStringListModel *theModel;
    Counter  *counter;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
