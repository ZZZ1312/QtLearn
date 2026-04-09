#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private:
    void setActionsForButton();

    void createSelectionPopMenu();

private slots:
    void on_actionInitList_triggered();

    void on_actionInsert_triggered();

    void on_actionDelete_triggered();

    void on_actionSelAll_triggered();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_actionClear_triggered();

    void on_actionAdd_triggered();

    void on_actionSelNone_triggered();

    void on_actionSelInvs_triggered();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
