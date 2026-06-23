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
private:
    void iniGraphicsSystem(); // 创建 Graphics View 的各项

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_mouseMovePoint(QPoint point);

    void on_mouseClicked(QPoint point);

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QLabel *labViewCord;
    QLabel *labSceneCord;
    QLabel *labItemCord;
    QLabel *labViewSize;
    QLabel *labSceneRect;
    QWGraphicsView *graphicsView;
};

#endif // MAINWINDOW_H
