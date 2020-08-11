#include "mainwindow.h"
#include "ui_mainwindow.h"



#define ALIVE_SEC 600
#define INTERVAL_MS 100

HANDLE MainWindow::map_open()
{
    return OpenFileMapping(
        FILE_MAP_READ,
        FALSE,
        TEXT(R3E_SHARED_MEMORY_NAME));
}

bool MainWindow::map_exists()
{
    HANDLE handle = map_open();

    if (handle != NULL)
        CloseHandle(handle);

    return handle != NULL;
}

int MainWindow::map_init()
{
    map_handle = map_open();

    if (map_handle == NULL)
    {
        wprintf_s(L"Failed to open mapping");
        return 1;
    }

    map_buffer = (r3e_shared*)MapViewOfFile(map_handle, FILE_MAP_READ, 0, 0, sizeof(r3e_shared));
    if (map_buffer == NULL)
    {
        wprintf_s(L"Failed to map buffer");
        return 1;
    }

    return 0;
}

void MainWindow::map_close()
{
    if (map_buffer) UnmapViewOfFile(map_buffer);
    if (map_handle) CloseHandle(map_handle);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , updater(this)
    , ui(new Ui::MainWindow)
    , udpSocket(this)
    , host(/*"192.168.0.213"*/ /*QHostAddress::LocalHost*/ "192.168.0.242")
    , port(7755)
{
    clk_start = 0, clk_last = 0;
    clk_delta_ms = 0, clk_elapsed = 0;
    err_code = 0;
    mapped_r3e = FALSE;
    myCurrentLapTime=-1;
    myLastLapTime=-1;
    myCurrentLapTimeStart.invalidate();
    qDebug("Looking for RRRE64.exe...\n");
    bool utpbindres=udpSocket.bind(host, 7755);

    if(!utpbindres)
    {
        qDebug("udpSocket.bind FAILED\n");
        qDebug(udpSocket.errorString().toLocal8Bit());
        //return;
    }

    connect(&updater, SIGNAL(timeout()), this, SLOT(run()));
    connect(&udpSocket,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()));

    updater.start(INTERVAL_MS);

    ui->setupUi(this);
}

void MainWindow::readPendingDatagrams()
{
    QHostAddress sender;
    quint16 port;
    while (udpSocket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(),datagram.size(),&sender,&port);
       qDebug() <<"Message From :: " << sender.toString();
       qDebug() <<"Port From :: "<< port;
       qDebug() <<"Message :: " << datagram;
   }
}

void MainWindow::run()
{
    if(1)
    {
        clk_elapsed = (clock() - clk_start) / CLOCKS_PER_SEC;
        if (clk_elapsed >= ALIVE_SEC)
            return;

        clk_delta_ms = (clock() - clk_last) / CLOCKS_PER_MS;
        if (clk_delta_ms < INTERVAL_MS)
        {
            Sleep(1);
            return;
        }

        clk_last = clock();

        if (!mapped_r3e && is_r3e_running() && map_exists())
        {
            qDebug("Found RRRE64.exe, mapping shared memory...\n");

            err_code = map_init();
            if (err_code)
                return;// err_code;

            qDebug("Memory mapped successfully\n");

            mapped_r3e = TRUE;
            clk_start = clock();
        }

        if (mapped_r3e)
        {
/*            if (map_buffer->gear > -2)
            {
                qDebug("Gear: %i\n", map_buffer->gear);
            }

            if (map_buffer->engine_rps > -1.f)
            {
                qDebug("RPM: %.3f\n", map_buffer->engine_rps * RPS_TO_RPM);
                qDebug("Speed: %.3f km/h\n", map_buffer->car_speed * MPS_TO_KPH);
            }
*/
            qDebug("current_lap_valid: %d",map_buffer->current_lap_valid);
            qDebug("lap_time_current_self: %.3f\n", map_buffer->lap_time_current_self);
            if(
                    ((map_buffer->lap_time_current_self!=-1) & (map_buffer->lap_time_current_self < ex_lap_time_current_self)) // lap becoming invalid
                    |((ex_lap_time_current_self ==-1) & (map_buffer->lap_time_current_self!=-1)) )
            {
                onNewLap();
            }
            ex_lap_time_current_self = map_buffer->lap_time_current_self;
            qDebug("lap_time_previous_self: %.3f", map_buffer->lap_time_previous_self);
            qDebug("time_delta_best_self: %.3f\n", map_buffer->time_delta_best_self);

            int myelapsed = myCurrentLapTimeStart.elapsed();
            qDebug("MY lap_time: %d", myelapsed);
            qDebug("MY lap_time_previous: %d\n", myLastLapTime);

            qDebug("\n");

            sendpacket.isLapValid = map_buffer->current_lap_valid;
            sendpacket.lap_time_current_self = map_buffer->lap_time_current_self;
            sendpacket.lap_time_previous_self = map_buffer->lap_time_previous_self;
            sendpacket.time_delta_best_self = map_buffer->time_delta_best_self;
            sendpacket.myelapsed = myelapsed;
            sendpacket.myLastLapTime = myLastLapTime;

        }
    }

    int sent = udpSocket.writeDatagram((const char *)&sendpacket, sizeof(sendpacket), host, port);
    //qDebug("Bytes sent: %d", sent);
    if(sent==-1)
    {
        qDebug(udpSocket.errorString().toLocal8Bit());
    }
}

MainWindow::~MainWindow()
{
    map_close();

    qDebug("All done!");

    delete ui;
}

void MainWindow::onNewLap()
{
    myLastLapTime = myCurrentLapTimeStart.restart();
}
