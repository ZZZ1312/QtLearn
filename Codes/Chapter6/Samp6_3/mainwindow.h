#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

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


protected:
    void paintEvent(QPaintEvent *event) override;

    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;

    QPixmap *pixmap;


    // QWidget interface
protected:

private slots:
    void on_actEmbeddedWindget_triggered();
    void on_actIndependentWidget_triggered();
    void on_actEmbeddeddMainWindow_triggered();
    void on_actIndependentMainWindow_triggered();
    void on_tabWidget_tabCloseRequested(int index);
    void on_tabWidget_currentChanged(int index);
};
#endif // MAINWINDOW_H
