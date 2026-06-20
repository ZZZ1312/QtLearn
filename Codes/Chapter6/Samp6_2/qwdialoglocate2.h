#ifndef QWDIALOGLOCATE2_H
#define QWDIALOGLOCATE2_H

#include <QDialog>

namespace Ui {
class QWDialogLocate2;
}

class QWDialogLocate2 : public QDialog
{
    Q_OBJECT
private:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_btnSetText_clicked();

public:
    explicit QWDialogLocate2(QWidget *parent = nullptr);
    ~QWDialogLocate2();

    void setSpinRange(int rowCount, int colCount); // 设置最大值

    void setSpinValue(int rowNo, int colNo); // 设置初始值

private:
    Ui::QWDialogLocate2 *ui;
};

#endif // QWDIALOGLOCATE2_H
