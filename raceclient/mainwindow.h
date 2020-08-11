#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
//#include <QHost>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void readData();

private:
    QUdpSocket udpSocket;
    Ui::MainWindow *ui;
    QHostAddress host;
};

#endif // MAINWINDOW_H
