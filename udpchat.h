#ifndef UDPCHAT_H
#define UDPCHAT_H

#include <QMainWindow>
#include <QWidget>
#include <QtNetwork/QtNetwork>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QVBoxLayout>
QT_BEGIN_NAMESPACE
namespace Ui { class udpChat; }
QT_END_NAMESPACE
class QPushButton;
class QUdpSocket;
class udpChat : public QMainWindow
{
    Q_OBJECT

public:
    udpChat(QWidget *parent = nullptr);
    ~udpChat();

private slots:

    void on_buttonConnect_clicked();

    void on_buttonSend_clicked();

    void on_buttonDisconnect_clicked();

    void on_cleanConsole_clicked();

    void on_inputMessage_returnPressed();

private:
    void outputText(QString outText);
    int remotePort;
    Ui::udpChat *ui;
    QUdpSocket *localUdpSocket = nullptr;
    QUdpSocket *remoteUdpSocket = nullptr;
    void readDatagram();
};
#endif // UDPCHAT_H
