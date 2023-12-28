#include "datapacket.h"


sDataPacket::sDataPacket()
{
    pro = new sProgress();
}


sDataPacket *sDataPacket::bulid()
{
    static sDataPacket* sington = nullptr;
    if(sington == nullptr)
        sington = new sDataPacket();
    return sington;
}

void sDataPacket::init()
{
    pro->step = 0;
    pro->result = 0;
    pro->pass.clear();
    pro->status.clear();

    pro->startTime = QTime::currentTime();

    pro->productType.clear();
    pro->productSN.clear();
    pro->macAddress.clear();
    pro->clientName.clear();
    pro->testTime.clear();
    pro->softwareType = "BusbarSafetyTest";
    pro->companyName = "clever";
    pro->protocolVersion = "V1.0";
    pro->testStartTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    pro->testEndTime.clear();
    pro->no.clear();
    pro->itemName.clear();
    pro->uploadPass.clear();
    pro->softwareVersion.clear();
    pro->acw.clear();
    pro->dcw.clear();
    pro->gnd.clear();
    pro->ir.clear();
}
bool sDataPacket::delay(int s)
{
    bool ret = true;
    for(int i=0; i<s; ++i) {
        QThread::msleep(100);
    }

    return ret;
}
// bool sDataPacket::updatePro(const QString &str, bool pass, int sec)
// {
//     pro->time = QTime::currentTime().toString("hh:mm:ss");
//     pro->pass << pass;
//     pro->itPass << pass;

//     pro->item << str;
//     pro->status << str;

//     pro->uploadPass << pass;
//     pro->itemName << str;

//     return pass;
// }
