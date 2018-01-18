#ifndef MYTIMER2_H
#define TIME2_H
#include <QObject>
#include <QTimer>
#include <QtCore>
#include <QDebug>
#include <QTableView>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
class MyTimer2 : public QObject
{
    Q_OBJECT
public:
    MyTimer2();
    QTimer *timer;

public slots:
    void MySlot2();
};

#endif
