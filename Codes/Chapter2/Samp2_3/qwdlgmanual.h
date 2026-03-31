#ifndef QWDLGMANUAL_H
#define QWDLGMANUAL_H

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>
#include <QPushButton>

class QWDlgManual : public QDialog
{
    Q_OBJECT
private:
    QCheckBox *chkBoxUnder;
    QCheckBox *chkBoxBold;
    QCheckBox *chkBoxItalic;

    QRadioButton *rBtnBlack;
    QRadioButton *rBtnRed;
    QRadioButton *rBtnBlue;

    QPlainTextEdit *txtEdit;

    QPushButton *btnOK;
    QPushButton *btnCancel;
    QPushButton *btnClose;

private:
    void initUi(); // UI 创建与初始化
    void iniSignalSlots(); // 初始化信号与槽的链接

private slots:
    void on_chkBoxUnder(bool checked); // Underline 的槽函数
    void on_chkBoxItalic(bool checked); // Italic 的槽函数
    void on_chkBoxBold(bool checked); // Bold 的槽函数
    void setTextFontColor(); // 设置字体颜色
    void reflushUI(); // 刷新所有UI
public:
    explicit QWDlgManual(QWidget *parent = nullptr);
    ~QWDlgManual() override;
};
#endif // QWDLGMANUAL_H
