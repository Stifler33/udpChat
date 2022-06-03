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
public:
    Exchange();
};

#endif // EXCHANGE_H
