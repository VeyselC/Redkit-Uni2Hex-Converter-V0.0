#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowTitle("ReDkIt Uni2Hex Converter V0.0");
    this->setWindowIcon(QIcon("://images/favicon.ico"));
    ui->setupUi(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    timer->start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerSlot()
{
//    int count = ui->lineEdit->text().size();
    QString osman4 = ui->lineEdit->text();
    QString osman5;
    int k=0;
    for(int j=0;j<osman4.size();j++)
    {//CR,LF ayıklanıyor.
        if(osman4[j] != 0x000A && osman4[j] != 0x000D)        //CR veya Lf varsa
            osman5[k++] = osman4[j];
    }
    int count = osman5.size();

    if(count > 10)
        ui->label->setStyleSheet("QLabel { background-color : red; color : white; }");
    else
        ui->label->setStyleSheet("QLabel { background-color : green;color : yellow;}");

    ui->label->setText(QString::number(count));
}

void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit_2->clear();
    HexString.clear();
    RusString.clear();

    QString osman4 = ui->lineEdit->text();
    int k=0;
    for(int j=0;j<osman4.size();j++)
    {
        if(osman4[j] != 0x000A && osman4[j] != 0x000D)        //CR veya Lf varsa
            RusString[k++] = osman4[j];
    }
    QTextCodec *codec = QTextCodec::codecForName("UTF-16");

    QByteArray encodedString = codec->fromUnicode(RusString);
    QString osman,osman2,osman3;
    for(int i=0; i<encodedString.size();i++)
        osman[i] = encodedString[i] ;
    osman2 = osman.toLatin1().toHex().toUpper();
    HexString = "0x";
    for(int i=4; i<osman2.size();i+=4)
    {
        osman3[2]=osman2[i];
        osman3[3]=osman2[i+1];
        osman3[0]=osman2[i+2];
        osman3[1]=osman2[i+3];
        if(i != osman2.size()-4)
        HexString  = QString(HexString + osman3 +",0x");
        else
            HexString  = QString(HexString + osman3);
    }

    ui->lineEdit_2->setText(HexString);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    HexString.clear();
    RusString.clear();

    QString osman10 = ui->lineEdit_2->text();
    QString osman11,osmancinlijapon;

    osman10.replace(QString("0X"), QString(""),Qt::CaseInsensitive);
    osman10.replace(QString(","), QString(""),Qt::CaseInsensitive);
    unsigned int sayac=0;


    for(int i=0; i<osman10.size();i+=4)
    {
        osman11[2]=osman10[i];
        osman11[3]=osman10[i+1];
        osman11[0]=osman10[i+2];
        osman11[1]=osman10[i+3];
        if(i != osman10.size()-4)
        osmancinlijapon  = QString(osmancinlijapon + osman11);
        else
            osmancinlijapon  = QString(osmancinlijapon + osman11);
    }



    while(sayac < osmancinlijapon.size())
    {
        if((osmancinlijapon[sayac] >= 0x30 && osmancinlijapon[sayac] <= 0x39) || (osmancinlijapon[sayac] >= 0x41 && osmancinlijapon[sayac] <= 0x46) || (osmancinlijapon[sayac] >= 0x61 && osmancinlijapon[sayac] <= 0x66))
                sayac++;
        else
        {
            QMessageBox::information(
                this,
                tr("ReDkIt Uni2Hex V0.0"),
                tr("HEX code FAIL FAIL "));
            break;
        }
    }
    QByteArray array (osmancinlijapon.toStdString().c_str());

    QByteArray text =  QByteArray::fromHex(array);
    text.data();            // returns "Qt is great!"
    QTextCodec *codec = QTextCodec::codecForName("UTF-16");
    QString encodedString = codec->toUnicode(text);


    ui->lineEdit->setText(encodedString);

}















