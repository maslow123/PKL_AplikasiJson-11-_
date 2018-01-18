#include "time.h"
#include "time2.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "redis.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
int cnt= 0;
MyTimer::MyTimer()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(MySlot()));
    timer -> start(1000);
}

MyTimer2::MyTimer2()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(MySlot2()));
    timer -> start(60000);
}

void MyTimer::MySlot()
{

}
void MyTimer2::MySlot2()
{

}




