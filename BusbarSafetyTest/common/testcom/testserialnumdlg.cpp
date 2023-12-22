/*
 *
 *
 *  Created on: 2018年10月1日
 *      Author: Lzy
 */
#include "testserialnumdlg.h"
#include "ui_testserialnumdlg.h"

TestSerialNumDlg::TestSerialNumDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestSerialNumDlg)
{
    ui->setupUi(this);
    init();
    this->setWindowTitle(tr("请输入被测模块序列号"));
    ui->dcwBox->hide();
    mItem->isGnd = false;
    mItem->isIr = true;
    mItem->isAcw = true;
    ui->gndBox->setChecked(false);
    ui->irBox->setChecked(true);
    ui->acwBox->setChecked(true);
}

TestSerialNumDlg::~TestSerialNumDlg()
{
    delete ui;
}

void TestSerialNumDlg::init()
{
    TestConfig *con = TestConfig::bulid();
    con->initConfig();
    mItem = &(con->item->sn);
    ui->dateEdit->setDate(QDate::currentDate());

    ui->opLineEdit->setText(mItem->op);
    ui->cnLineEdit->setText(mItem->cn);
    ui->clientLineEdit->setText(mItem->clientName);
    ui->clearRadioButton->setChecked(mItem->snClear);
    if(!mItem->name.isEmpty()) ui->typeComboBox->setCurrentText(mItem->name);
//    if(!mItem->batch.isEmpty()) ui->batchComboBox->setCurrentText(mItem->batch);
    ui->batchLineEdit->setText(mItem->batch);
    if(!mItem->purpose.isEmpty()) ui->purposeComboBox->setCurrentText(mItem->purpose);
}

bool TestSerialNumDlg::getSerialNum()
{
    bool ret  = ui->addRadioButton->isChecked();
    if(ret) {
        int data = ui->snLineEdit->text().toInt() + 1;
        QString str = QString::number(data);
        ui->snLineEdit->setText(str);
    } else {
        ui->snLineEdit->clear();
    }

    return ret;
}


void TestSerialNumDlg::on_purposeComboBox_currentTextChanged(const QString &arg1)
{
    QString str = arg1 + "_" + ui->batchLineEdit->text();
    ui->statusLab->setText(str);
}


bool TestSerialNumDlg::inputCheck()
{
    //bool ret = false;
    QString str = ui->snLineEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("请输入产品条码"));
        return false;
    } else {
//        ret = cm_isDigitStr(str);
//        if(!ret) {
//            CriticalMsgBox box(this, tr("产品条码应是纯数字，请重新输入!!"));
//            return false;
//        } else {
            mItem->sn = str;
//        }
    }

    str = ui->opLineEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("请输入操作员!!!"));
        return false;
    } else {
        mItem->op = str;
    }

    str = ui->cnLineEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("请输入电脑号!!!"));
        return false;
    } else {
        mItem->cn = str;
    }

    str = ui->clientLineEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("请输入客户名称!!!"));
        return false;
    } else {
        mItem->clientName = str;
    }
    str = ui->batchLineEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("请输入订单编号!!!"));
        return false;
    } else {
        mItem->batch = str;
    }

    mItem->date = ui->dateEdit->date();
//    mItem->batch = ui->batchLineEdit->text();
    mItem->name = ui->typeComboBox->currentText();
    mItem->purpose = ui->purposeComboBox->currentText();
    mItem->snClear = ui->clearRadioButton->isChecked();
    mItem->errStop = ui->errStopCheckBox->isChecked();
    mItem->isSave = ui->saveCheckBox->isChecked();
    mItem->isGnd = ui->gndBox->isChecked();
    mItem->isIr = ui->irBox->isChecked();
    mItem->isDcw = ui->dcwBox->isChecked();
    mItem->isAcw = ui->acwBox->isChecked();

    return true;
}

void TestSerialNumDlg::on_okBtn_clicked()
{
    bool ret = inputCheck();
    if(ret) {
        this->close();
        TestConfig::bulid()->saveConfig(mItem);
        this->accept();
    }
}

void TestSerialNumDlg::on_cancelBtn_clicked()
{
    this->close();
}


void TestSerialNumDlg::on_typeComboBox_currentIndexChanged(int index)
{
    switch(index){
    case StartBox:
    {
        mItem->isGnd = false;
        mItem->isIr = true;
        mItem->isAcw = true;
        ui->gndBox->setChecked(false);
        ui->irBox->setChecked(true);
        ui->acwBox->setChecked(true);
    }break;
    case InsertBox:{
        mItem->isGnd = false;
        mItem->isIr = true;
        mItem->isAcw = true;
        ui->gndBox->setChecked(false);
        ui->irBox->setChecked(true);
        ui->acwBox->setChecked(true);
    }break;
    case BusWay:{
        mItem->isGnd = false;
        mItem->isIr = true;
        mItem->isAcw = true;
        ui->gndBox->setChecked(false);
        ui->irBox->setChecked(true);
        ui->acwBox->setChecked(true);
    }break;
    default:{
        mItem->isGnd = false;
        mItem->isIr = true;
        mItem->isAcw = true;
        ui->gndBox->setChecked(false);
        ui->irBox->setChecked(true);
        ui->acwBox->setChecked(true);
    }break;
    }
}
