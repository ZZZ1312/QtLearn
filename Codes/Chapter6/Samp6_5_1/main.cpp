#include "mainwindow.h"
#include <QApplication>
#include "mysplashscreen.h"
#include <QPixmap>
#include <QThread> // 模拟耗时用
#include <QProgressBar>
#include <QTimer>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 1. 加载你的启动图片
    QPixmap originalPixmap(":/images/images/back.png");
    QTransform transform;
    transform.scale(0.25, 0.25); // X轴和Y轴都缩放到 0.25 倍
    // 使用 transform 变换图片
    // 注意：这种方法默认就是高质量缩放
    QPixmap scaledPixmap = originalPixmap.transformed(transform, Qt::SmoothTransformation);

    MySplashScreen splash(scaledPixmap);
    splash.show();

    MainWindow w;

    QTimer *progressTimer = new QTimer(&splash);
    int *currentProgress = new int{0};
    QObject::connect(progressTimer, &QTimer::timeout,[&w, &splash, progressTimer, currentProgress]{
        *currentProgress += 20;
        splash.setProgress(*currentProgress);

        if (*currentProgress >= 100)
        {
            progressTimer->stop();

            // 延迟一小会
            QTimer::singleShot(20, [&w, &splash, currentProgress]{
                splash.finish(&w);
                w.show();
                delete currentProgress;
            });
        }
    });

    progressTimer->start(1000);

    return a.exec();
}