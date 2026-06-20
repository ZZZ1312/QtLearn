#ifndef QWDIALOGLOCATE2H_H
#define QWDIALOGLOCATE2H_H

#include <QDialog>

namespace Ui {
class QWDialogLocate;
}

class QWDialogLocate : public QDialog
{
    Q_OBJECT
private:
    void closeEvent(QCloseEvent *event);

    void showEvent(QCloseEvent *event);

private slots:
    void on_btnSetText_clicked();

public slots:
    void setSpinValue(int rowNo, int colNo);

signals:
    void changeCellText(int row, int column, const QString &text);

    void changeActionEnable(bool en);

public:
    explicit QWDialogLocate(QWidget *parent = nullptr);
    ~QWDialogLocate();

    void setSpinRange(int rowCount, int colCount); // 设置最大值
private:
    Ui::QWDialogLocate *ui;
};

#endif // QWDIALOGLOCATE2H_H
