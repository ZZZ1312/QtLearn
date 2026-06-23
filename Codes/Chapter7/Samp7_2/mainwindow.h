#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QWIntSpinDelegate;
class QWFloatSpinDelegate;
class QWComboBoxDelegate;
class QStandardItemModel;
class QItemSelectionModel;
class QStandardItem;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void resetTable(int rowCount);

    bool saveDataAsStream(const QString &fileName);

    bool openDataAsStream(const QString &fileName);

    bool saveBinaryFile(const QString &fileName);

    bool openBinaryFile(const QString &fileName);

    QList<QStandardItem*> createRow();

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:
    void on_actOpenStm_triggered();

    void on_actSaveStm_triggered();

    void on_actOpenDat_triggered();

    void on_actSaveDat_triggered();

    void on_actAppend_triggered();

    void on_actReset_triggered();
private:
    Ui::MainWindow *ui;

    QLabel *labCellPos;                 // 当前单元格行列号
    QLabel *labCellText;                // 当前单元格内容
    QWIntSpinDelegate *intSpinDelegate;
    QWFloatSpinDelegate *floatSpinDelegate;
    QWComboBoxDelegate *comboBoxDelegate;
    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;


};
#endif // MAINWINDOW_H
