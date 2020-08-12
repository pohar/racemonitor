#include "RaceClient.h"
#include "ui_MainWindow.h"
#include <QTime>
#include <QFontDatabase>

RaceClient::RaceClient(QWidget *parent) :
    QMainWindow(parent)
  , udpSocket(this)
    , ui(new Ui::MainWindow)
  ,host("192.168.0.213")
  ,updater(this)
{
    qDebug("Start!");
    //ui->label_LapValid->setText("Valid lap");
    bool ret=udpSocket.bind( /* host, */ 7755);
    if(!ret)
    {
        qDebug("Bind failed!");
        qDebug(udpSocket.errorString().toLocal8Bit());
        //return;
     }

    int id = QFontDatabase::addApplicationFont(":/fonts/fonts/digital-7.mono.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont digitalfont(family);


    connect(&udpSocket, &QUdpSocket::readyRead, this, &RaceClient::readData);
    connect(&updater, SIGNAL(timeout()), this, SLOT(UpdateUI()));
    updater.start(10/*INTERVAL_MS*/);
    ui->setupUi(this);
    ui->label_LapTime->setFont(digitalfont);
    ui->label_LapTime->setStyleSheet("QLabel { background-color : black; color : white; font: 50pt;}");
}

RaceClient::~RaceClient()
{
    delete ui;
}

void RaceClient::readData()
{
// QByteArray buffer;
// buffer.resize(udpSocket.pendingDatagramSize());
// TODO assert datagram size == packet_t size
 //qDebug("readData!");

 QHostAddress sender;
 quint16 senderPort;

// udpSocket.readDatagram(buffer.data(), buffer.size() , &sender, &senderPort );
 udpSocket.readDatagram((char *)&gameinfo, sizeof(gameinfo) , &sender, &senderPort );
 //packet_t gameinfo

 //qDebug() << "Message from:" << sender.toString << " port:" << senderPort;
 qDebug("current_lap_valid: %d", gameinfo.isLapValid);
 qDebug("lap_time_current_self: %.3f\n", gameinfo.lap_time_current_self);
 qDebug("lap_time_previous_self: %.3f\n", gameinfo.lap_time_previous_self);
 qDebug("time_delta_best_self: %.3f\n", gameinfo.time_delta_best_self);
 qDebug("MY lap time: %d", gameinfo.myelapsed);
 qDebug("MY lap_time_previous: %d\n", gameinfo.myLastLapTime);

}

void RaceClient::UpdateUI()
{
    if(gameinfo.isLapValid)
    {
        ui->label_LapValid->show();
        ui->label_LapInvalid->hide();
    }
    else
    {
        ui->label_LapValid->hide();
        ui->label_LapInvalid->show();
    }

    QTime laptime(0,0);  //(54533 /*gameinfo.lap_time_current_self*/);
    ui->label_LapTime->setText( laptime.addMSecs(34523).toString("mm:ss.zzz") );
    //ui->progressBar_LapPerc->value();
}
