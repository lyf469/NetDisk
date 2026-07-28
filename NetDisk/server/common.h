#ifndef COMMON_H
#define COMMON_H
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>

class DBHelper
{
public:
    //获取对象
    static DBHelper& getInstance();
    //打开数据库
    bool openDB();
    //创建数据表
    void creatTable();
    //修改语句
    bool execSql(QString sql);
    //查询语句
    QSqlQuery querySql(QString sql);
private:
    DBHelper();
    QSqlDatabase db;
};

#endif // COMMON_H
