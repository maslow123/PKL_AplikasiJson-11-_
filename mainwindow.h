#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QVariant>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>
#include <QModelIndex>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void MySlot();
    void MySlot2();
    void on_tableViewdb_activated(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_tableView_2_activated(const QModelIndex &index);

    void on_load_button_clicked();

private:
    Ui::MainWindow *ui;
    void setTable(QJsonArray jsonArray);
    QTimer *timer;

};

#endif // MAINWINDOW_H
