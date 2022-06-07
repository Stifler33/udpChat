#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <QMainWindow>
#include <QWidget>
#include <QtNetwork/QtNetwork>
class Exchange : public QMainWindow
{
    Q_OBJECT
    QUdpSocket *localUdpSocket = nullptr;
    QUdpSocket *remoteUdpSocket = nullptr;
    quint16 localPort;
public:
    Exchange();
    bool connectPort(quint16 port);
    void disconnect();
    bool sendMessage(const QString &message, quint16 remotePort);
signals:
   void readDatagram(QString &resultMessage);
};

#endif // EXCHANGE_H
