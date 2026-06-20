#include "mysplashscreen.h"
#include <QApplication>

#include <QProgressBar>

MySplashScreen::MySplashScreen(const QPixmap &pixmap)
    : QSplashScreen(pixmap)
{
    // 创建一个进度条，并把 splash 设为它的父对象！
    progressBar = new QProgressBar(this);

    // 设置进度条的位置和大小（根据你的背景图尺寸来调整）
    progressBar->setGeometry(40, pixmap.height() - 40, pixmap.width() - 40, 15);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
}

MySplashScreen::~MySplashScreen()
{

}

void MySplashScreen::setProgress(int progress)
{
    if (progress < 0)
        progress = 0;
    else if (progress > 100)
        progress = 100;

    progressBar->setValue(progress);
}

void MySplashScreen::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->lower();
        event->accept();
    }
}