#include "udpchat.h"
#include "./ui_udpchat.h"
udpChat::udpChat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::udpChat)
{
    ui->setupUi(this);
    remoteUdpSocket = new QUdpSocket(this);
    localUdpSocket = new QUdpSocket(this);
}

udpChat::~udpChat()
{
    delete ui;
}

void udpChat::on_buttonConnect_clicked()
{
    int localPort = ui->localPort->text().toInt();
    remotePort = ui->remotePort->text().toInt();

    if (localUdpSocket->bind(QHostAddress::LocalHost, localPort)){
        outputText("connect local potr " + ui->localPort->text());
    }else{
        outputText("filed connect local potr");
    }
    connect(localUdpSocket, &QUdpSocket::readyRead, this , &udpChat::readDatagram);
}

void udpChat::readDatagram(){
    QByteArray datagram;
    while (localUdpSocket->hasPendingDatagrams()){
        datagram.resize(localUdpSocket->pendingDatagramSize());
        localUdpSocket->readDatagram(datagram.data(), datagram.size());
        QString resultMessage = datagram.constData();
        outputText("intput message : " + resultMessage);
    }
}

void udpChat::on_buttonSend_clicked()
{
    QByteArray datagram(ui->inputMessage->text().toUtf8(), -1);
    if (remoteUdpSocket->writeDatagram(datagram, QHostAddress::LocalHost,remotePort) < 0){
        outputText("filed send");
    }
    ui->inputMessage->clear();
}

void udpChat::on_buttonDisconnect_clicked()
{
    localUdpSocket->close();
    remoteUdpSocket->close();
    outputText("disconnect");
}

void udpChat::outputText(QString outText){
    ui->dialogWindow->insertPlainText(outText + "\n");
}

void udpChat::on_cleanConsole_clicked()
{
    ui->dialogWindow->clear();
}


void udpChat::on_inputMessage_returnPressed()
{
    on_buttonSend_clicked();
}

