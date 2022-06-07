#include "exchange.h"
#include <iostream>
Exchange::Exchange()
{
    remoteUdpSocket = new QUdpSocket(this);
    localUdpSocket = new QUdpSocket(this);
}

bool Exchange::connectPort(quint16 port)
{
    if (localUdpSocket->bind(QHostAddress::LocalHost, port)){
        connect(localUdpSocket, &QUdpSocket::readyRead, this,&Exchange::readDatagram);
        return true;
    }
    return false;
}

void Exchange::disconnect()
{
    localUdpSocket->close();
    remoteUdpSocket->close();
}

void Exchange::readDatagram(QString &resultMessage)
{
    QByteArray datagram;
    while (localUdpSocket->hasPendingDatagrams()){
        datagram.resize(localUdpSocket->pendingDatagramSize());
        localUdpSocket->readDatagram(datagram.data(), datagram.size());
    }
    resultMessage = datagram.constData();
}

bool Exchange::sendMessage(const QString &message, quint16 remotePort)
{
    QByteArray datagram(message.toUtf8(), -1);
    if (remoteUdpSocket->writeDatagram(datagram, QHostAddress::LocalHost, remotePort) < 0){
        std::cout << remoteUdpSocket->errorString().toStdString();
        return false;
    }
    return true;
}

