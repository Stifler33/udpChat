#include "udpchat.h"
#include "./ui_udpchat.h"
udpChat::udpChat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::udpChat)
{
    ui->setupUi(this);
    exchange = new Exchange;
    sender = new Sender;

    exchange->moveToThread(&threadExchange);
    sender->moveToThread(&threadSender);

    connect(&threadExchange, &QThread::finished, exchange, &QObject::deleteLater);
    connect(&threadSender, &QThread::finished, exchange, &QObject::deleteLater);

    connect(this, &udpChat::pressSendMessage, sender, &Sender::sendMessage);
    connect(sender, &Sender::throwNotification, this, &udpChat::outputText);
    connect(this, &udpChat::pressDisconnect, exchange, &Exchange::disconnect);
    connect(exchange, &Exchange::throwNotification, this, &udpChat::outputText);
    connect(this, &udpChat::connectToPort, exchange, &Exchange::connectPort);

    threadExchange.start();
    threadSender.start();
}
udpChat::~udpChat()
{
    delete ui;
    threadExchange.quit();
    threadExchange.wait();
    threadSender.quit();
    threadSender.wait();
}

void udpChat::showDatagram(QString &message)
{
    outputText("incoming message : " + message);
}

void udpChat::on_buttonConnect_clicked()
{
    quint16 localPort = ui->localPort->text().toInt();
    emit connectToPort(localPort);
}

void udpChat::on_buttonSend_clicked()
{
    emit pressSendMessage(ui->inputMessage->text(), ui->remotePort->text().toInt());
    ui->inputMessage->clear();
}

void udpChat::on_buttonDisconnect_clicked()
{
    emit pressDisconnect();
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

