#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QLabel>
#include <QSpacerItem>

class QWDialogHeaders;
class QWDialogLocate;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_actSetRowColumn_triggered();

    void on_actSetHeaders_triggered();

    void on_tableView_clicked(const QModelIndex &index);

    void on_actLocateCell_triggered();

    void setACellTextSlot(int row, int column, const QString &text); // 设置单元格内容信号

    void setActLocateEnable(bool enable); // 设置 actTab_locate 的 enable 属性

signals:
    void cellIndexChanged(int rowNo, int colNo); // 当单元格发生变化

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;
    QLabel *labCellPos;
    QLabel *labContent;
    QSpacerItem *horizontalSpacer;

    QWDialogHeaders *dlgSetHeaders = nullptr;
};
#endif // MAINWINDOW_H
