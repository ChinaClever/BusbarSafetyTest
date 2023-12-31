#include "dblogs.h"

DbLogs::DbLogs()
{
    createTable();
}


DbLogs *DbLogs::bulid()
{
    static DbLogs* sington = nullptr;
    if(sington == nullptr)
        sington = new DbLogs();
    return sington;
}


void DbLogs::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "passed         VCHAR,"
            "clientname     VCHAR,"
            "batch          VCHAR,"
            "purpose        VCHAR,"
            "cn             VCHAR,"
            "gnd            VCHAR,"
            "ir             VCHAR,"
            "dcw            VCHAR,"
            "acw            VCHAR,"
            "sn             VCHAR);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName())))
    {
        throwError(query.lastError());
    }
}

bool DbLogs::insertItem(DbLogItem &item)
{
    bool ret = false;
//    item.id = maxId()+1;
    QString cmd = "insert into %1 (id, date, time, cn, clientname, batch, purpose, sn, gnd, ir, dcw, acw, passed) "
                  "values(:id,:date,:time,:cn,:clientname,:batch,:purpose,:sn,:gnd,:ir,:dcw,:acw,:passed)";
    ret = modifyItem(item,cmd.arg(tableName()));
    if(ret)
        emit itemChanged(item.id,Insert);

    return ret;
}


bool DbLogs::modifyItem(const DbLogItem &item, const QString &cmd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare(cmd);
//    query.bindValue(":id",item.id);
    query.bindValue(":date",item.date);
    query.bindValue(":time",item.time);
    query.bindValue(":cn",item.cn);
    query.bindValue(":clientname",item.clientName);
    query.bindValue(":batch",item.batch);
    query.bindValue(":purpose",item.type);
    query.bindValue(":sn",item.sn);
    query.bindValue(":gnd",item.gnd);
    query.bindValue(":ir",item.ir);
    query.bindValue(":dcw",item.dcw);
    query.bindValue(":acw",item.acw);
    query.bindValue(":passed",item.passed);
    ret = query.exec();
    if(!ret)
        throwError(query.lastError());
    return ret;
}

void DbLogs::selectItem(QSqlQuery &query, DbLogItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.cn = query.value("cn").toString();
    item.clientName = query.value("clientname").toString();
    item.batch = query.value("batch").toString();
    item.type = query.value("purpose").toString();
    item.sn = query.value("sn").toString();
    item.gnd = query.value("gnd").toString();
    item.ir = query.value("ir").toString();
    item.dcw = query.value("dcw").toString();
    item.acw = query.value("acw").toString();
    item.passed = query.value("passed").toString();
}
