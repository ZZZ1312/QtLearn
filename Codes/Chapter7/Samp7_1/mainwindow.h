#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    bool openTextByIODevice(const QString &fullPath);

    bool saveTextByIODevice(const QString &fullPath);

    bool openTextByStream(const QString &fullPath);

    bool saveTextByStream(const QString &fullPath);
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_actOpen_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_actSaveOther_triggered();

    void on_actStreamOpen_triggered();

    void on_actStreamSaveOther_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
