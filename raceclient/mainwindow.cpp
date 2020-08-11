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
 QByteArray buffer;
 buffer.resize(udpSocket.pendingDatagramSize());

 qDebug("readData!");

 QHostAddress sender;
 quint16 senderPort;

 udpSocket.readDatagram(buffer.data(), buffer.size() /* , &sender, &senderPort */);

 qDebug() << "Message from:" << sender.toString();
 qDebug() << "Message port:" << senderPort;
 qDebug() << "Message:" << buffer;
}
