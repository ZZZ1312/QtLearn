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
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void setACellText(int row, int col, const QString &text);

    void setActLocateEnabele(bool);

    void setDlgLocateNull();

private:
    Ui::MainWindow *ui;

    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;
    QLabel *labCellPos;
    QLabel *labContent;
    QSpacerItem *horizontalSpacer;

    QWDialogHeaders *dlgSetHeaders = nullptr;
    QWDialogLocate *dlgLocate = nullptr;
};
#endif // MAINWINDOW_H
