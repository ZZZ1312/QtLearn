#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

private slots:
    void on_chkBoxUnder_clicked(bool checked);

    void on_checkBoxBold_clicked(bool checked);

    void on_chkBoxItalic_clicked(bool checked);

    void setTextFontColor();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
