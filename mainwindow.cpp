#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "time.h"
#include "redis.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("json");
    db.setUserName("root");
    db.setPassword("");
    if (db.open()){
        qDebug() << "Berhasil konek database";
    }else{
        qDebug() <<"Koneksi Gagal";
    }
    //siap untuk mengambil data PHP
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr,SIGNAL(finished(QNetworkReply*)),&eventLoop,SLOT(quit()));
    //mengambil data php dari alamat..
    QNetworkRequest req(QUrl(QString("http://localhost/api/ApplicationApi.php")));
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();
    if(reply -> error() == QNetworkReply::NoError){
        QByteArray strReply = reply ->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply);
        QJsonObject object = jsonResponse.object();
        if(object.value("data").isUndefined()){
            qDebug()<<"Gagal";
        }
        QJsonArray jsonArray = object.value("data").toArray();
        this ->setTable(jsonArray);
    }
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(MySlot()));
    timer -> start(1000);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(MySlot2()));
    timer -> start(60000);
  }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTable(QJsonArray jsonArray)
{

}

void MainWindow::MySlot()
{
    int cnt = 0;
    QEventLoop eventLoop;
    // selesai
    QNetworkAccessManager mgr;
    QObject::connect(&mgr,SIGNAL(finished(QNetworkReply*)),&eventLoop,SLOT(quit()));
    //http request
    QNetworkRequest req(QUrl(QString("http://localhost/api/ApplicationApi.php")));
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();
    if(reply -> error() == QNetworkReply::NoError){
        QByteArray strReply = reply ->readAll();

        //parse json
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply);
        QJsonObject object = jsonResponse.object();
        if(object.value("data").isUndefined()){
            qDebug()<<"Eror";
            }
        QJsonArray jsonArray = object.value("data").toArray();
        QStandardItemModel *model = new QStandardItemModel(1,3,this);
        model -> setHorizontalHeaderItem(0,new QStandardItem(QString("Point")));
        model -> setHorizontalHeaderItem(1,new QStandardItem(QString("Value")));
        model -> setHorizontalHeaderItem(2,new QStandardItem(QString("Epochtime")));
        ui -> tableView -> setModel(model);
        foreach(const QJsonValue &value,jsonArray){
              redis rds;
              QJsonObject jsonObj = value.toObject();
              if(!jsonObj["Point"].isNull()&& !jsonObj["Value"].isNull() &&
                 !jsonObj["Epochtime"].isNull()){
                 QString pointt = jsonObj["Point"].toString();
                 QString valuee = jsonObj["Value"].toString();
                 QString epochh = jsonObj["Epochtime"].toString();
                 QStringList result1 = rds.reqRedis("HSET data point '"+pointt+"'","127.0.0.1", 6379);
                 QStringList result2 = rds.reqRedis("HSET data value '"+valuee+"'","127.0.0.1", 6379);
                 QStringList result3 = rds.reqRedis("HSET data epoch '"+epochh+"'","127.0.0.1", 6379);
                 QStandardItem *point =new QStandardItem(pointt);
                 model->setItem(cnt,0,point); //mengambil NIS dari database
                 QStandardItem *tes =new QStandardItem(valuee);
                 model ->setItem(cnt,1,tes);//mengambil data Nama dari database
                 QStandardItem *epoch =new QStandardItem(epochh);
                 model -> setItem(cnt,2,epoch);//mengambil data Kelas dari database
                 cnt++;
                 }
              }
    }else{
        QMessageBox msgBox;
        msgBox.setText("Koneksi tidak terhubung ! Harap periksa koneksi anda !");
        msgBox.exec();
      }
   }
void MainWindow::MySlot2()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("json");
    db.setUserName("root");
    db.setPassword("");
    db.open();
    QEventLoop eventLoop;
    // selesai
    QNetworkAccessManager mgr;
    QObject::connect(&mgr,SIGNAL(finished(QNetworkReply*)),&eventLoop,SLOT(quit()));
    //http request
    QNetworkRequest req(QUrl(QString("http://localhost/api/ApplicationApi.php")));
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();
    if(reply -> error() == QNetworkReply::NoError){
        QByteArray strReply = reply ->readAll();
        //parse json
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply);
        QJsonObject object = jsonResponse.object();
        if(object.value("data").isUndefined()){
            qDebug()<<"Eror";
            }
        QJsonArray jsonArray = object.value("data").toArray();
        foreach(const QJsonValue &value,jsonArray){
            QJsonObject jsonObj = value.toObject();
            if(!jsonObj["Point"].isNull()&& !jsonObj["Value"].isNull() &&
               !jsonObj["Epochtime"].isNull()){
               QString pointt = jsonObj["Point"].toString();
               QString valuee = jsonObj["Value"].toString();
               QString epochh = jsonObj["Epochtime"].toString();
               QSqlQuery query;
               query.prepare("INSERT INTO aplikasi(Point,Value,Epochtime)VALUES('"+pointt+"','"+valuee+"','"+epochh+"')");
               if(query.exec()){
                    qDebug()<<"=============================="<<endl;
                    qDebug()<<"Point:"<<pointt<<endl<<
                              "Value:"<<valuee<<endl<<
                              "Epochtime:"<<epochh<<endl;
                    qDebug()<<"=============================="<<endl;
                    QMessageBox msg;
                    msg.setText("Data berhasil ditambahkan , silahkan menunggu 1 menit berikutnya !");
                    msg.exec();
               }else{
                    QMessageBox msg;
                    msg.setText("Data gagal ditambahkan!");
                    msg.exec();
                   }
                }
            }
        }
    }
void MainWindow::on_load_button_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from aplikasi");
    if(query.exec()){
        model->setQuery(query);
        ui->tableViewdb->setModel(model);
        qDebug() << (model->rowCount());
       }
  }

