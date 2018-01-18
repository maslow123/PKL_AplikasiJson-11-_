#ifndef MYTIMER_H
#define TIME_H
#include <QObject>
#include <QTimer>
#include <QtCore>
#include <QDebug>
#include <QTableView>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
class MyTimer : public QObject
{
    Q_OBJECT

public:
    MyTimer();
    QTimer *timer;

public slots:
    void MySlot();
};

#endif
