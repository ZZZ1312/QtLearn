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
    void on_btnOpenFile_clicked();

    void on_btnOpenFiles_clicked();

    void on_btnSelectDir_clicked();

    void on_btnSaveFile_clicked();

    void on_btnsSelectColor_clicked();

    void on_btnSelectFont_clicked();

    void on_btnInputString_clicked();

    void on_btnInputInt_clicked();

    void on_btnInputFloat_clicked();

    void on_btnInputItem_clicked();

    void on_btnQuestion_clicked();

    void on_btnInformation_clicked();

    void on_btnWarning_clicked();

    void on_btnCritical_clicked();

    void on_btnAbout_clicked();

    void on_btnClearText_clicked();

    void on_btnAboutQt_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
