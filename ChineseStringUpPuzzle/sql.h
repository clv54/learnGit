#ifndef SQL_H
#define SQL_H

#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class sql
{
public:
    sql();

    bool verificationLogin(QString Username, QString Password); // 确认登录
    bool connectDB(QString databaseConnectionName, QString databaseName, QString userName, QString password);   // 连接数据库函数
    void close();

    QList<QString> select(QString tab, QString data); // 查询信息
    QVector<QVector<QString> > selectRecord(QString tab, QString data); // 查询消费信息

    QSqlQuery* sql_query;

private:

    QSqlDatabase database;

};

#endif // SQL_H
