#include "exchange.h"

void Exchange::connect()
{

}

Exchange::Exchange()
{
    remoteUdpSocket = new QUdpSocket(this);
    localUdpSocket = new QUdpSocket(this);
}
