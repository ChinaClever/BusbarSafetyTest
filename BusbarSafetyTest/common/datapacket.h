#ifndef DATAPACKET_H
#define DATAPACKET_H
#include <QtCore>
#include "serialportdlg.h"

enum sTestType{
    StartBox,
    InsertBox,
    BusWay

};
enum sTestStep{
    GNDTest = 1,
    IRTest,
    ACWTest

};
enum sTestFile{
    GNDFile = 1,
    ACWFile = 1,
    IRFile

};
struct sSnItem
{
    QString name;
    QString op; // 操作员
    QString cn; // 电脑号
    QString sn; // 产品条码

    QString clientName; // 客户名称
    QString batch; // 批次
    QString purpose;
    QDate date;

    bool isGnd; // 接地测试
    QString gnd; // 接地测试结果

    bool isIr; //绝缘测试
    QString ir; // 绝缘测试结果

    bool isDcw; //直流耐压测试
    QString dcw; // 直流耐压测试结果

    bool isAcw; //交流耐压测试
    QString acw; // 交流耐压测试结果

    bool snClear;
    bool errStop;
    bool isSave;
};

struct sTestProgress
{
    sTestProgress() {okNum=errNum=finishNum=0; allNum=10;}

    int allNum;
    int okNum;
    int errNum;
    int finishNum;
    QString status;
};



/**
 * @brief 测试数据结构体
 */
struct sTestDataItem
{
    sTestDataItem(){id=0;}

    int id;
    bool status; // 状态

    QString item; // 检查项目
    QString subItem; // 测试项目描述

    QString expect; // 期望值
    QString measured; // 实测值
    QString result; // 结果
};

struct sTestConfigItem
{
    sTestConfigItem() {mode=0;}
    SerialPort *serial; // 串口对象
    SerialPort *serialGND; // 串口对象

    int mode;
    sSnItem sn;
    sTestProgress progress;

    QList<sTestDataItem> dataItem;
    QList<QStringList> logList;
    QList<sTestDataItem> logItems;
};

struct sProgress
{
    sProgress() {step=0;}

    uchar step; // 步骤
    uchar recordstep; // 记录启动步骤
    QString time;
    QList<bool> pass;
    QStringList status;

    uchar result;    // 最终结果
    QTime startTime;

    QString softwareType;
    QString companyName;
    QString protocolVersion;

    QString productType;
    QString productSN;
    QString macAddress;
    QString softwareVersion;
    QString gnd;
    QString ir;
    QString dcw;
    QString acw;
    QString clientName;
    QString testTime;
    QString testStartTime;
    QString testEndTime;
    QStringList no, itemName;
    QList<bool> uploadPass;
    uchar uploadPassResult;
};


/**
 * 数据包
 */
class sDataPacket
{
    sDataPacket();
public:
    static sDataPacket *bulid();
    bool delay(int s);
    void init();
    sProgress *getPro() {return pro;}

protected:

    sProgress *pro;
};



#endif // DATAPACKET_H
