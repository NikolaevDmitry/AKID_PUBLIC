#include "database.h"


Database::Database(QString connectionName, QString hostName, QString databaseName, QObject *parent) : QObject(parent) //
{    
    qDebug() << "Database:          start";
    this->connectionName = connectionName;
    this->hostName       = hostName;
    this->databaseName   = databaseName;

    db = QSqlDatabase::addDatabase("QOCI",connectionName);  //"QODBC"
    //db = QSqlDatabase::addDatabase("QODBC",connectionName);
    //db.setHostName(this->hostName);
    db.setDatabaseName(this->databaseName);
}


Database::~Database()
{
    //db.close();
    //QSqlDatabase::removeDatabase(this->connectionName); //QSqlDatabase::defaultConnection
    //db.removeDatabase(this->connectionName);
    qDebug()<< "(!!!) Удаление объекта БД";
}

void Database::setDB(QString hostName, QString databaseName, QString userName, QString password)
{
    this->hostName      = hostName;
    this->databaseName  = databaseName;
    this->userName      = userName;
    this->password      = password;
}



void Database::connectionDB(const QString &userName, const QString &password) {
    //qDebug() << "Database_thread: connectionDB: thread =" << QThread::currentThreadId();

    this->userName = userName;
    this->password = password;

    db.setUserName(this->userName);
    db.setPassword(this->password);

    ///////////////////////////////////////////////////////////////////////////
//    db.setHostName("localhost");
//    db.setPort(1521);
//    db.setDatabaseName("akid");
//    db.setUserName(this->userName);
//    db.setPassword(this->password);
    ///////////////////////////////////////////////////////////////////////////

    qDebug() << "connectionDB: connectionName = " << this->connectionName;
    qDebug() << "connectionDB: databaseName   = " << this->databaseName;
//    qDebug() << "connectionDB: hostName       = " << this->hostName;
//    qDebug() << "connectionDB: userName       = " << this->userName;
//    qDebug() << "connectionDB: hostName       = " << this->password;

    /// сообщение менеджеру о начале соединения
    emit signalConnectionDB_BEGIN(this->connectionName);

    if (!db.open()) {
        emit signalConnectionDB_FALSE(this->connectionName);

        qDebug() << "_________________________>";        
        qDebug() << this->databaseName;
        qDebug() << "Error DB: "       << db.lastError().text();
        qDebug() << "ConnectionError:" << db.lastError().ConnectionError;
        //qDebug() << "driverText"       << db.lastError().driverText();
        //qDebug() << QSqlDatabase::drivers();
        qDebug() << "_________________________<";
    } else {
        emit signalConnectionDB_TRUE(this->connectionName);

        qDebug() << "ConnectionError:"<<db.lastError().text(); //ConnectionError
        qDebug() << " -> DB connect! ("<<this->databaseName << "| thread =" << QThread::currentThreadId() << " )";
    }
}



/// ?
void Database::closeDB()
{
    if(db.isOpen()){
        db.close();
        qDebug()<<"Закрывается БД: " << db.connectionName() << db.isOpen();
        //QSqlDatabase::removeDatabase(this->connectionName);
    }
}
