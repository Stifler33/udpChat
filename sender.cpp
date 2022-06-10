#include "exchange.h"

Sender::Sender()
{
    remoteUdpSocket = new QUdpSocket(this);
}

void Sender::sendMessage(const QString &message, quint16 remotePort)
{
    QByteArray datagram(message.toUtf8(), -1);
    if (remoteUdpSocket->writeDatagram(datagram, QHostAddress::LocalHost, remotePort) < 0){
        emit throwNotification("send error\n" + remoteUdpSocket->errorString());
    }
}
