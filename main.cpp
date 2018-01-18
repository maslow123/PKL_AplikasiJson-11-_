#include "mainwindow.h"
#include <QApplication>
#include "redis.h"
#include "time.h"
#include "time2.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    redis rds;
    QStringList result = rds.reqRedis("PING", "127.0.0.1", 6379);
    for (int i = 0; i < result.length(); i++) {
        qDebug() << result.at(i);
    }

    MyTimer mTimer;
    MyTimer2 mTimer2;

    MainWindow w;
    w.show();

    return a.exec();
}
