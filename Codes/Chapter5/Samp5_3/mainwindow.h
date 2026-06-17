#ifndef MAINWIND_H
#define MAINWIND_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>


class QWIntSpinDelegate;
class QWFloatSpinDelegate;
class QWComboBoxDelegate;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void initModelFromStringList(QStringList&);     // 从 StringList 初始化数据模型

    void setTextAlignment(Qt::AlignmentFlag);
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    // 当前选择单元格发生变化
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actOpenFile_triggered();

    void on_actAppend_triggered();

    void on_actInsert_triggered();

    void on_actRemove_triggered();

    void on_actCenter_triggered();

    void on_actRight_triggered();

    void on_actLeft_triggered();

    void on_actBold_triggered(bool checked);

    void on_actQuit_triggered();

    void on_actSaveAs_triggered();

    void on_actPreview_triggered();

private:
    QLabel *LabCurFile;                     // 当前文件
    QLabel *LabCellPos;                     // 当前单元格行列号
    QLabel *LabCellText;                    // 当前单元格内容
    QStandardItemModel *theModel;           // 数据模型
    QItemSelectionModel *theSelection;      // 选择模型

    QWIntSpinDelegate *intSpinDelegate; // 整数型代理
    QWFloatSpinDelegate *floatSpinDelegate;
    QWComboBoxDelegate *comboBoxDelegate;


    Ui::MainWindow *ui;
};
#endif //
