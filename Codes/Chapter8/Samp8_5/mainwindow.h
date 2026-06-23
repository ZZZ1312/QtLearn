#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>

class QWGraphicsView;
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

private slots:
    void on_mouseMovePoint(QPoint point);

    void on_mouseRightClicked(QPoint point);

    void on_mouseClicked(QPoint point);

    void on_mouseDoubleClicke(QPoint point);

    void on_keyPress(QKeyEvent *event   ); // 按键

    void on_actItem_Ellipse_triggered();

    void on_actZoomIn_triggered();

    void on_actZoomOut_triggered();

    void on_actRestore_triggered();

    void on_actRotateLeft_triggered();

    void on_actEdit_Front_triggered();

    void on_actEdit_Back_triggered();

    void on_actGroup_triggered();

    void on_actGroupBreak_triggered();

    void on_actEdit_Delete_triggered();

    private:
    Ui::MainWindow *ui;

    static const int ItemId = 1; // 图形项自定义数据的Key
    static const int ItemDesciption = 2; // 图形项自定义数据的Key
    int seqNum = 0; // 用于图形项的编号，每个图形项有一个编号
    int frontZ = 0; // 用于 bring to front
    int backZ = 0; // 用于 bring to back
    QGraphicsScene *scene;
    QLabel *labViewCord;
    QLabel *labSceneCord;
    QLabel *labItemCord;
    QLabel *labItemInfo;

    QWGraphicsView *view;

};
#endif // MAINWINDOW_H
