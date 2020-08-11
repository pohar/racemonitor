#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// my includes
#include <QtMath>
#include <QElapsedTimer>
#include <QUdpSocket>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <tchar.h>
#include <QTimer>
#include "../r3e-api/sample-c/src/r3e.h"
#include "../r3e-api/sample-c/src/utils.h"
#include "../common/common.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTimer updater;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void run();
    void readPendingDatagrams();

private:
    Ui::MainWindow *ui;
    HANDLE map_handle = INVALID_HANDLE_VALUE;
    r3e_shared* map_buffer = NULL;
    clock_t clk_start , clk_last ;
    clock_t clk_delta_ms , clk_elapsed ;
    int err_code ;
    bool mapped_r3e ;
    r3e_float32 ex_lap_time_current_self;
    r3e_float32 ex_lap_distance_fraction;
    QElapsedTimer myCurrentLapTimeStart;
    int myCurrentLapTime;
    int myLastLapTime;
    packet_t sendpacket;
    QUdpSocket udpSocket;
    const QHostAddress host;
    quint16 port;
    bool myinvalid;

    void map_close();
    int map_init();
    bool map_exists();
    HANDLE map_open();
    void onNewLap();

};
#endif // MAINWINDOW_H
