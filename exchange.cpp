#include "exchange.h"
Exchange::Exchange()
{
    remoteUdpSocket = new QUdpSocket(this);
    localUdpSocket = new QUdpSocket(this);
}

void Exchange::connectPort(quint16 port)
{
    if (localUdpSocket->bind(QHostAddress::LocalHost, port)){
        connect(localUdpSocket, &QUdpSocket::readyRead, this, &Exchange::readDatagram);
        emit throwNotification(QString("connect %1 to port").arg(port));
    }else{
        emit throwNotification("error connect:\n" + localUdpSocket->errorString());
    }
}

void Exchange::disconnect()
{
    localUdpSocket->close();
    remoteUdpSocket->close();
    emit throwNotification("disconnect");
}

void Exchange::readDatagram()
{
    QByteArray datagram;
    while (localUdpSocket->hasPendingDatagrams()){
        datagram.resize(localUdpSocket->pendingDatagramSize());
        localUdpSocket->readDatagram(datagram.data(), datagram.size());
    }
    QString resultMessage = datagram.constData();
    emit throwNotification("incoming message : " + resultMessage);
}

void Exchange::sendMessage(const QString &message, quint16 remotePort)
{
    QByteArray datagram(message.toUtf8(), -1);
    if (remoteUdpSocket->writeDatagram(datagram, QHostAddress::LocalHost, remotePort) < 0){
        emit throwNotification("send error\n" + remoteUdpSocket->errorString());
    }
}

