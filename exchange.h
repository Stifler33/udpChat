#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <QtNetwork/QtNetwork>
class Exchange : public QObject
{
    Q_OBJECT
    QUdpSocket *localUdpSocket = nullptr;
    quint16 localPort;
public:
    Exchange();
signals:
    void haveMessage(QString &message);
    void throwNotification(QString notification);
public slots:
    void readDatagram();
    void connectPort(quint16 port);
    void disconnect();
};

class Sender : public QObject
{
    Q_OBJECT
    QUdpSocket *remoteUdpSocket = nullptr;
public:
    Sender();
signals:
    void throwNotification(QString notification);
public slots:
    void sendMessage(const QString &message, quint16 remotePort);
};

#endif // EXCHANGE_H
