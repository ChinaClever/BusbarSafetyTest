﻿#include "logwid.h"
#include "dblogs.h"

LogWid::LogWid(QWidget *parent) : LogComWid(parent)
{

}


/**
 * @brief 获取表对象
 * @return
 */
BasicSql *LogWid::getDb()
{
    return  DbLogs::bulid();
}

/**
 * @brief 初始化表格
 */
void LogWid::initTable()
{
    QString table = getDb()->tableName();
    this->refreshTable(table);

    mTableTile = tr("测试记录日志");
    setGroupBoxTitle(mTableTile);

    mHeadList.clear();
    mHeadList << tr("编号") << tr("日期") << tr("时间")
              << tr("结果") << tr("客户名称") << tr("订单编号")
              << tr("产品类型") << tr("电脑号") << tr("接地电阻")
              << tr("绝缘电阻") << tr("直流耐压") << tr("交流耐压")
              << tr("产品条码");

    model->setHeaders(mHeadList);
}
