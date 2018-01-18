#include "redis.h"

redis::redis()
{

}

QStringList redis::reqRedis(QString command, QString address, int port)
{
    qDebug() << command;
    QStringList result;
    int dbNumber = 0;
    if(client.isConnected()) {client.disconnect();}
    if (client.connect(address, port)) {
        result = client.query(QString("SELECT %1").arg(dbNumber));
        if(result.at(0) != "string" || result.at(1) != "OK") {
            result.append("Error"); result.append(QString("Can't select database %1").arg(dbNumber));
            if(client.isConnected()) {client.disconnect();}
        } else {
            result = client.query(command);
        }
    } else {
        result.append("Error"); result.append("Redis Not Connect ..");
    }
    return result;
}

