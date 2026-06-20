#ifndef MYSPLASHSCREEN_H
#define MYSPLASHSCREEN_H

#include <QSplashScreen>
#include <QMouseEvent>
#include <QPushButton>

class QProgressBar;


class MySplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    explicit MySplashScreen(const QPixmap &pixmap);

    ~MySplashScreen();

public slots:
    void setProgress(int progress);

protected:
    // 1. 拦截点击，记录位置，阻止默认隐藏
    void mousePressEvent(QMouseEvent *event) override;
private:
    QProgressBar *progressBar;
};

#endif // MYSPLASHSCREEN_H
