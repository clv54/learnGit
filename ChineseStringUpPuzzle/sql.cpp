#include "sql.h"
#include <QSqlQuery>
#include <QDateTime>

sql::sql()
{
    sql_query = new QSqlQuery();
}

void sql::close()
{
    this->database.close();
}


QList<QString> sql::select(QString tab, QString data)
{
    QList<QString> vData;
    if (!connectDB("qt_sql_default_connection", "Database.db", "root", "123456"))
    {
        qDebug()<<"Errror: Failed to connect to database."<< database.lastError();
    }
    else
    {
        sql_query = new QSqlQuery();
        QString select_sql = QString("select * from %1").arg(tab);
        if(!sql_query->exec(select_sql))
        {
            qDebug()<<sql_query->lastError();
        }
        else
        {
            while(sql_query->next())
            {
                vData.append(sql_query->value(0).toString());
            }
        }
        //qDebug() << vData;
        database.close();
        return vData;
    }
    return vData;
}

QVector<QVector<QString>> sql::selectRecord(QString tab, QString data)
{
    QVector<QVector<QString>> vvData;
    if (!connectDB("qt_sql_default_connection", "Database.db", "root", "123456"))
    {
        qDebug()<<"Errror: Failed to connect to database."<< database.lastError();
    }
    else
    {
        sql_query = new QSqlQuery();

        QString select_sql = QString("select * from %1").arg(tab);
        if(!sql_query->exec(select_sql))
        {
            qDebug()<<sql_query->lastError();
        }
        else
        {
            //int numColumn = sql_query->size();
            while(sql_query->next())
            {
                if (sql_query->value(2).toString().indexOf(data) != -1) {
                    QVector<QString> vData;
                    vData.append(sql_query->value(0).toString());
                    vData.append(sql_query->value(1).toString());
                    vvData.append(vData);
                }
            }
            return vvData;
        }
        //qDebug() << vData;
        //database.close();
    }
    return vvData;
}

// 连接数据库
bool sql::connectDB(QString databaseConnectionName, QString databaseName, QString userName, QString password)
{
    //QSqlDatabase database;
    if (QSqlDatabase::contains(databaseConnectionName))
    {
        database = QSqlDatabase::database(databaseConnectionName);
    } else {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName(databaseName);
        database.setUserName(userName);
        database.setPassword(password);
    }
    //open database
    if (!database.open())
    {
        qDebug()<<"Error: Failed to connect to database."<< database.lastError();
        return false;
    }
    else {
        return true;
    }
}
