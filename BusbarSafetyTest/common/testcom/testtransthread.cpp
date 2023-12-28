#include "testtransthread.h"
TestTransThread::TestTransThread(QObject *parent) : QObject(parent)
{
     QTimer::singleShot(300,this,SLOT(initFunSLot()));
}


void TestTransThread::initFunSLot()
{
    mSerial = TestConfig::bulid()->item->serial;
    mSerialGND  = TestConfig::bulid()->item->serialGND;
}

void Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

QString TestTransThread::sentStep(int step , int i , QString & command , int extra)
{
    QByteArray recv;
    if(step == 1)
        command = sentResisCommand(i , extra);//GND
    else
        command = sentResisCommand(i , extra);//IR//ACW

    for(int count = 0 ; count < 3 ; count ++)
    {
        if(recv.isEmpty()){
            if(step == 1)
                mSerialGND->transmit(command.toLatin1(),recv,10);
            else{
                if(mSerial)
                mSerial->transmit(command.toLatin1(),recv,10);
            }

        }
//        else
//            qDebug()<<"recv"<<recv;
        if(!recv.isEmpty())
            break;
        Delay_MSec(1000);
    }
    qDebug()<<"step:"<<step<<"index:"<<i;
    return recv;
}

QString TestTransThread::sentResisCommand(int command , int extra)
{
    QString str;
    switch(command)
    {
        case ConnectReady://1
            str = "*IDN?\r\n";
            break;
        case Reset://2
            str = "RESET\r\n";
            break;
        case ChoseeFile://3
            str = QString("FL %1\r\n").arg(extra);
            break;
        case StepTotal://4
            str = "ST?\r\n";
            break;
        case Test://5
            str = "TEST\r\n";
            break;
        case ReadData://6
            str = QString("RD %1?\r\n").arg(extra);
            break;
    }
    return str ;
}
