#include "common.h"

DBHelper::DBHelper()
{

}

DBHelper& DBHelper::getInstance()
{
    static DBHelper obj;
    return obj;
}

bool DBHelper::openDB()
{
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("netdisk.db");
    if(!db.open())
    {
        qDebug()<<"数据库打开失败"<<db.lastError().text();
        return false;
    }
    else
    {
        creatTable();
        return true;
    }
}

void DBHelper::creatTable()
{
    //用户表
    QString userSql=R"(CREATE TABLE IF NOT EXISTS user(
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    username TEXT UNIQUE,
                    password TEXT,
                    role TEXT,
                    total_size INTERER DEFAULT 0))";
    //文件记录表
    QString fileSql=R"(CREATE TABLE IF NOT EXISTS file_record(
                    fid INTEGER PRIMARY KEY AUTOINCREMENT,
                    uid INTEGER,
                    file_name TEXT,
                    file_type TEXT,
                    file_size INTEGER,
                    save_path TEXT,
                    upload_time TEXT,
                    md5 TEXT))";
    //传输日志表
    QString logSql=R"(CREATE TABLE IF NOT EXISTS transfer_log(
                   lid INTEGER PRIMARY KEY AUTOINCREMENT,
                   uid INTEGER,
                   opt_type TEXT,
                   file_name TEXT,
                   opt_time TEXT"))";
    execSql(userSql);
    execSql(fileSql);
    execSql(logSql);
}

bool DBHelper::execSql(QString sql)
{
    QSqlQuery q;
    if(!q.exec(sql))
    {
        qDebug()<<"sql执行失败"<<sql<<q.lastError().text();
        return false;
    }
    else
        return true;
}

QSqlQuery DBHelper::querySql(QString sql)
{
    QSqlQuery q;
    q.exec(sql);
    return q;
}


