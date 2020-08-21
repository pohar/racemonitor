#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include "..\common\common.h"
#include <QTimer>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class RaceClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit RaceClient(QWidget *parent = 0);
    ~RaceClient();

public slots:
    void readData();
    void UpdateUI();

protected:
    void SetLabelFontStlye(QLabel* label, QFont& font);
    
private:
    QUdpSocket udpSocket;
    Ui::MainWindow *ui;
    QHostAddress host;
    packet_t gameinfo;
    QTimer updater;
};

#endif // MAINWINDOW_H
