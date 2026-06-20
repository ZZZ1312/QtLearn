#ifndef QDLGLOGIN_H
#define QDLGLOGIN_H

#include <QDialog>

namespace Ui {
class QDlgLogin;
}

class QDlgLogin : public QDialog
{
    Q_OBJECT
private:
    void readSettings(); // 读取设置，注册表

    void writeSettings(); // 写入设置，注册表

    QString encrypt(const QString &str); // 字符串加密

protected:
    // 用于鼠标拖动窗口的鼠标事件
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);
public:
    explicit QDlgLogin(QWidget *parent = nullptr);

    ~QDlgLogin();

private slots:
    void on_btnEnsure_clicked();

private:
    Ui::QDlgLogin *ui;

    bool m_moving = false; // 表示窗口是否在鼠标操作下的移动
    QPoint m_lastPos; // 上一次鼠标的位置
    QString m_user = "user"; // 初始化用户名
    QString m_pwd = "12345"; // 初始化用户名，未加密
    int m_tryCount = 0; // 试错次数
};

#endif // QDLGLOGIN_H
