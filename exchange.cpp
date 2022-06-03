#include "exchange.h"

void Exchange::connect()
{
    localPort = ui->localPort->text().toInt();
}

Exchange::Exchange()
{
    remoteUdpSocket = new QUdpSocket(this);
    localUdpSocket = new QUdpSocket(this);
}
