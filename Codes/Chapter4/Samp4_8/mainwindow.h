#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    // 自定义类型
    // 枚举类型 treeItemType，创建节点时用作type参数，自定义类型必须大于1000
    enum treeItemType{itTopItem= 1001, itGroupItem, itImageItem};
    enum treeColumn{colItem = 0, colItemType=1}; // 目录树的编号
private:
    Ui::MainWindow *ui;

    QLabel *labFileName; // 用于状态栏文件名显示
    QPixmap curPixmap; // 当前的图片
    float pixRatio; // 当前图片缩放比例

private:
    void initTree(); // 目录树初始化
    void addFolderItem(QTreeWidgetItem *parItem, QString dirName); // 添加目录
    QString getFinalFolderName(const QString &fullPathName); // 提取目录名称
    void addImageItem(QTreeWidgetItem *parItem, QString aFileName); // 添加图片
    void displayImage(QTreeWidgetItem *item); // 显示一个图片节点的图片
    void changeItemCaption(QTreeWidgetItem *item); // 遍历改变节点标题

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;


private slots:
    void on_actAddFolder_triggered();
    void on_actAddFile_triggered();
    void on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void on_actDeleteItem_triggered();
    void on_actTraverseItem_triggered();
    void on_actZoomFitH_triggered();
    void on_actZoomFitW_triggered();
    void on_actZommIn_triggered();
    void on_actZoomOut_triggered();
    void on_actZoomRealSize_triggered();
    void on_actDockVisible_toggled(bool arg1);
    void on_actDockFloat_triggered(bool checked);
    void on_dockWidget_visibilityChanged(bool visible);
    void on_dockWidget_topLevelChanged(bool topLevel);
};
#endif // MAINWINDOW_H
