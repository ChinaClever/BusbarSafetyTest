/*
 * BasicSql.cpp
 *
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "basicsql.h"
#include "common.h"


BasicSql::BasicSql(QObject *parent) :
    QObject(parent)
{
    initDb();
    //标记表
    QString cmd = "create table if not exists markingtable("
                  "name TEXT primary key not null,"
                  "marking TEXT not null);";
    QSqlQuery query;
    if(!query.exec(cmd))
        throwError(query.lastError());
}

/**
 * @brief 删除
 * @param condition
 */
void BasicSql::remove(const QString &condition)
{
    QSqlQuery query;
    if(!query.exec(QString("DELETE FROM %1 WHERE %2").arg(tableName()).arg(condition))) {
        qDebug()<< "remove:" << query.lastError();
        throwError(query.lastError());
    }
}


/**
 * @brief 获取最大ID
 * @param idName
 * @return
 */
int BasicSql::maxId(const QString &idName)
{
    int max_id = 0;
    QSqlQuery query;
    if(query.exec(QString("select max(%1) from %2").arg(idName).arg(tableName())))
    {
        if(query.next())
            max_id = query.value(0).toInt();
    } else {
        qDebug()<< "maxId:" << query.lastError();
    }
    return max_id;
}


/**
 * @brief 获取最大ID
 * @param idName
 * @return
 */
int BasicSql::maxId(const QString &idName, const QString &condition)
{
    int max_id = 0;
    QSqlQuery query;
    if(query.exec(QString("select max(%1) from %2 %3").arg(idName).arg(tableName()).arg(condition)))
    {
        if(query.next())
            max_id = query.value(0).toInt();
    } else
        qDebug()<< "maxId:" << query.lastError();
    return max_id;
}

/**
 * @brief 函数返回指定列的值的数目
 * @param column_name
 * @return
 */
int BasicSql::count(const QString &column_name, const QString &condition)
{
    int count = -1;
    QSqlQuery query;
    if(query.exec(QString("select count(DISTINCT %1) from %2 %3").arg(column_name).arg(tableName()).arg(condition))){
        if(query.next())
            count = query.value(0).toInt();
    } else
        qDebug()<< "sqlcom count:" << query.lastError();
    return count;
}


/**
 * @brief 函数返回列的所有值
 * @param column_name 列名
 * @param condition 条件
 * @return
 */
QStringList BasicSql::listColumn(const QString &column_name, const QString &condition)
{
    QStringList list;
    QSqlQuery query;
    if(query.exec(QString("select DISTINCT %1 from %2 %3").arg(column_name).arg(tableName()).arg(condition))){
        while(query.next())
            list << query.value(0).toString();
    } else
        qDebug()<< "sqlcom listColumnStr:" << query.lastError();
    return list;
}


QVector<int> BasicSql::listColumnToInt(const QString &column_name, const QString &condition)
{
    QStringList list = listColumn(column_name, condition);
    QVector<int> items;
    for(int i=0; i<list.size(); ++i)
        items << list[i].toInt();

    return items;
}


bool BasicSql::updateColumn(const QString& column_name, double value, const QString &condition)
{
    bool ret = false;
    QSqlQuery query;
    ret = query.exec(QString("update  %1 set %2=%3 %4").arg(tableName()).arg(column_name).arg(value).arg(condition));
    if(!ret)
        qDebug()<< "sqlcom updateColumn 1:" << query.lastError();
    return ret;
}

bool BasicSql::updateColumn(const QString& column_name, const QString& value, const QString &condition)
{
    bool ret = false;
    QSqlQuery query;
    ret = query.exec(QString("update  %1 set %2=\"%3\" %4").arg(tableName()).arg(column_name).arg(value).arg(condition));
    if(!ret)
        qDebug()<< "sqlcom updateColumn 2:" << query.lastError();
    return ret;
}

/**
 * @brief 函数返回id列的所有值
 * @param condition 查询条件
 * @return
 */
QVector<int> BasicSql::selectIds(const QString &condition)
{
    return listColumnToInt("id", condition);
}


/**
 * @brief 异常
 * @param err
 */
void BasicSql::throwError(const QSqlError &err)
{
    qCritical() << "Sql_Error:" << err.text() << err.type();
}

bool BasicSql::clear()
{
//        QString cmd = QString("truncate table %1").arg(tableName());
    QString cmd = QString("DROP  table %1").arg(tableName());
    QSqlQuery query(cmd);
    bool ret = query.exec(cmd);
    if(!ret){
        qDebug()<< "sqlcom clear :" << query.lastError();
    } else {
        createTable();
    }

    return ret;
}

/**
 * @brief BasicSql::tableMarking
 * @return
 */
QString BasicSql::tableMarking()
{
    QString cmd = QString("SELECT * from markingtable where name = \"%1\"").arg(tableName());
    QSqlQuery query(cmd);
    if(query.exec(cmd)){
        if(query.next())
            return query.value(1).toString();
    } else {
        throwError(query.lastError());
    }
    return "";
}

/**
 * @brief BasicSql::setTableMarking
 * @param marking
 */
void BasicSql::setTableMarking(const QString &marking)
{
    QString ori = tableMarking();
    QString cmd = ori.isEmpty()?"insert into markingtable (name,marking) values(%1,%2)":"update markingtable set marking = %2 where name = \"%1\"";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName()).arg(marking)))
        throwError(query.lastError());
}

/**
 * @brief 数据库初始化
 */
void BasicSql::initDb()
{
    static bool s_initDbFinshed = false;
    if(s_initDbFinshed == false){
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(cm_pathOfData("BusbarSafetytest.db"));
        if (!db.open()) { //打开数据库
            qDebug() << "init Db error !!!";
        }
        s_initDbFinshed = true;
    }
}


/**
 * @brief 根据日期来查询
 */
void DB_selectTableByTime(QString &name, QString &start, QString &end, QList<QStringList> &list)
{
    QSqlQuery query;
    QString cmd = QString("select * from %1 where date Between \'%2\' and  \'%3\'").arg(name).arg(start).arg(end);
    bool ret = query.exec(cmd);
    if(ret)
    {
        while(query.next())
        {
            QStringList strList;
            int columnNum = query.record().count(); //获取每条记录中属性（即列）的个数
            for(int i=0; i<columnNum; ++i)
                strList << query.value(i).toString();
            list.append(strList);
        }
    }
    else
        qDebug() << cmd << "Err";
}


/**
 * @brief 获取日志时间链表
 * @return
 */
bool db_select_dateList(const QString &tableName, QStringList &dateList)
{
    QString str = QString("select * from %1").arg(tableName);

    QSqlQuery query;
    query.setForwardOnly(true); // 为了节省内存开销
    bool ret = query.exec(str);
    if(ret)
    {
        while(query.next()) //开始就先执行一次next()函数，那么query 指向结果集的第一条记录
        {
            str = query.value(1).toString();  //日期
            if(!dateList.contains(str))
                dateList << str; // 加入链表中
        }
    }
    else
        qDebug() << "db_select_dateList err: " << str;

    return ret;
}
