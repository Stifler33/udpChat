#include "udpchat.h"
#include "./ui_udpchat.h"
udpChat::udpChat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::udpChat)
{
    ui->setupUi(this);
    exchange = new Exchange;
    exchange->moveToThread(&threadExchange);
    connect(&threadExchange, &QThread::finished, exchange, &QObject::deleteLater);
    threadExchange.start();
}
udpChat::~udpChat()
{
    delete ui;
    threadExchange.quit();
    threadExchange.wait();
}

void udpChat::showDatagram(QString &message)
{
    outputText("incoming message : " + message);
}

void udpChat::on_buttonConnect_clicked()
{
    quint16 localPort = ui->localPort->text().toInt();
    if (exchange->connectPort(localPort)){
        connect(exchange, &Exchange::haveMessage, this, &udpChat::showDatagram);
        outputText(QString("connect %1 port").arg(localPort));
    }
}

void udpChat::on_buttonSend_clicked()
{
    if (!exchange->sendMessage(ui->inputMessage->text(), ui->remotePort->text().toInt())){
        outputText("send failed");
    }
    ui->inputMessage->clear();
}

void udpChat::on_buttonDisconnect_clicked()
{
    exchange->disconnect();
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

