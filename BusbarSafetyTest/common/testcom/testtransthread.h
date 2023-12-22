#ifndef TESTTRANSTHREAD_H
#define TESTTRANSTHREAD_H

#include "testresultwid.h"

enum TestResisEnum {
    ConnectReady = 1,//1
    Reset = 2,
    ChoseeFile = 3,
    StepTotal = 4,
    Test = 5,
    ReadData = 6
};

class TestTransThread : public QObject
{
    Q_OBJECT
public:
    explicit TestTransThread(QObject *parent = nullptr);

    QString sentStep(int step, int i , QString & command, int extra = 1);
    QString sentResisCommand(int command, int extra);

signals:

protected slots:
    void initFunSLot();

private:
    SerialPort *mSerial;
    SerialPort *mSerialGND;
};

#endif // TESTTRANSTHREAD_H
