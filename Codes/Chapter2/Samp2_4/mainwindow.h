#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QFontComboBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *fLabCurFile; // 状态栏里显示当前文件的Label
    QProgressBar *progressBar1; // 状态栏上的进度条
    QSpinBox *spinFontSize; // 字体大小 spinBox
    QFontComboBox *comboFont; // 字体名称 comboBox

private:
    void initUi(); // 代码实现的UI初始化
    void iniSignalSlots(); // 关联信号与槽

private slots:
    void on_actFontBold_triggered(bool checked);
    void on_txtEdit_copyAvailable(bool b);
    void on_txtEdit_selectionChanged();
    // 自定义槽函数
    void on_spinFontSize_valueChanged(int aFontSize); // 改变字体大小
    void on_comboFont_currentTextChanged(const QString &arg); // 选择字体

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
