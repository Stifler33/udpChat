#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <QMainWindow>
//#include <QObject>
#include <QWidget>
#include <QtNetwork/QtNetwork>

class Exchange : public QMainWindow
{
    Q_OBJECT
    QUdpSocket *localUdpSocket = nullptr;
    QUdpSocket *remoteUdpSocket = nullptr;
    int remotePort;
    int localPort;
    void connect();
    void disconnect();
    void readDatagram();
    void sendMessage();

public:
    Exchange();
};

#endif // EXCHANGE_H
