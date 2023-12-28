#ifndef TESTCORETHREAD_H
#define TESTCORETHREAD_H

#include "testtransthread.h"
#include "testtransthread.h"
#include "datapacket.h"

class TestCoreThread : public QThread
{
    Q_OBJECT
public:
    explicit TestCoreThread(QObject *parent = nullptr);
    ~TestCoreThread();

    void startThread();

signals:
    void overSig();

protected:
    void run();
    void stopThread();
    //void updateData(int i);
    void conditionExec(bool s);
    void updateProgress(bool status, QString &str);
    bool appendResult(sTestDataItem &item);

    void delayItem(sTestDataItem &item, int s);
    bool testReady();
    bool testGND(QString &recv);
    bool testIR(QString &recv);
    bool testACW(QString &recv);
    bool startTest(sTestDataItem &item,QString & recv , const QString &test , int step , int &stepTotal);

private:
    int mItemId;
    int mTestStep;
    int mStep;
    sTestConfigItem  *mItem;
    TestTransThread *mTrans;
    sProgress *mPro;
    sDataPacket *mPacket;
};

#endif // TESTCORETHREAD_H
