#include "exchange.h"
Exchange::Exchange()
{
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

