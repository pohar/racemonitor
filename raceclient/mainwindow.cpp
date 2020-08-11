#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , udpSocket(this)
    , ui(new Ui::MainWindow)
  ,host("192.168.0.213")
{
    qDebug("Start!");
    bool ret=udpSocket.bind( /* host, */ 7755);
    if(!ret)
    {
        qDebug("Bind failed!");
        qDebug(udpSocket.errorString().toLocal8Bit());
        //return;
     }

    connect(&udpSocket, &QUdpSocket::readyRead, this, &MainWindow::readData);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readData()
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
