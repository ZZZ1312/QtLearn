#include "qdlglogin.h"
#include "ui_qdlglogin.h"
#include <QSettings>
#include <QCryptographicHash>
#include <QByteArray>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPixmap>

QDlgLogin::QDlgLogin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QDlgLogin)
{
    ui->setupUi(this);

    QPixmap pixmap(":/images/images/back.png");
    QPixmap scaledPixmap = pixmap.scaled(632, 355, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->labBackground->setPixmap(scaledPixmap);
    ui->labBackground->setScaledContents(true); // 开启自动缩放

    ui->editPwd->setEchoMode(QLineEdit::Password); // 设置为密码输入模式
    this->setAttribute(Qt::WA_DeleteOnClose); // 设置为关闭时删除
    this->setWindowFlags(Qt::SplashScreen); // 设置为 Splash Screen
    readSettings(); // 读取存储的用户名和密码
}

QDlgLogin::~QDlgLogin()
{
    delete ui;
}

void QDlgLogin::on_btnEnsure_clicked()
{
    // "确定" 按钮
    QString username = ui->editUser->text().trimmed();
    QString pwd = ui->editPwd->text().trimmed();
    QString encryptPWD = encrypt(pwd);
    if ((username==m_user) && (encryptPWD == m_pwd))
    {
        writeSettings();
        this->accept(); // 对话框 accept，关闭对话框
    }
    else
    {
        ++m_tryCount; // 错误次数
        if (m_tryCount > 3)
        {
            QMessageBox::critical(this, "错误", "输入次数太多，强行退出");
            this->reject();
        }
        else
        {
            QMessageBox::warning(this, "错误提示", "用户名或密码错误");
        }
    }
}

void QDlgLogin::readSettings()
{
    // 读取存储的用户名和密码，密码是经过加密的
    QString organization = "WWB-Qt"; // 用于注册表
    QString appName = "samp6_5";
    QSettings settings(organization, appName);
    bool saved = settings.value("saved", false).toBool(); // 读取Saved
    m_user = settings.value("Username", "user").toString(); // 读取用户名
    QString defaultPSWD = encrypt("12345"); // 默认密码“12345”加密后的数据
    m_pwd = settings.value("PWD", defaultPSWD).toString(); // 读取PWD
    if (saved)
        ui->editUser->setText(m_user);
    ui->chkSaveUser->setChecked(saved);
}

void QDlgLogin::writeSettings()
{
    // 保存用户名，密码等设置
    QSettings settings("WWB-Qt", "samp6_5"); // 注册表键组
    settings.setValue("Username", m_user);
    settings.setValue("PWD", m_pwd);
    settings.setValue("saved", ui->chkSaveUser->isChecked());
}

QString QDlgLogin::encrypt(const QString &str)
{
    // 字符串 MD5 算法加密
    QByteArray data;
    data.append(str.toUtf8());
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(data);
    QByteArray resultArray = hash.result(); // 返回最终的散列
    QString md5 = resultArray.toHex(); // 转换为16进制字符串
    return md5;
}

void QDlgLogin::mousePressEvent(QMouseEvent *event)
{
    // 鼠标按键被按下
    if (event->button() == Qt::LeftButton)
    {
        m_moving = true;
        m_lastPos = (event->globalPosition() - pos()).toPoint(); // 记录下鼠标相对于窗口的位置
    }
    return QDialog::mousePressEvent(event);
}

void QDlgLogin::mouseMoveEvent(QMouseEvent *event)
{
    // 鼠标按下左键移动
    if (m_moving && (event->buttons() & Qt::LeftButton) &&
        (event->globalPosition() - m_lastPos).manhattanLength() > QApplication::startDragDistance())
    {
        move((event->globalPosition() - m_lastPos).toPoint());
        m_lastPos = (event->globalPosition() - pos()).toPoint();
    }
    return QDialog::mouseMoveEvent(event);
}

void QDlgLogin::mouseReleaseEvent(QMouseEvent *event)
{
    // 鼠标按键释放
    m_moving = false; // 停止移动
}



