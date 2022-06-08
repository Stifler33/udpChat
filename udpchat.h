#ifndef UDPCHAT_H
#define UDPCHAT_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QString>
#include "exchange.h"
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
public slots:
    void showDatagram(QString &message);
private slots:

    void on_buttonConnect_clicked();

    void on_buttonSend_clicked();

    void on_buttonDisconnect_clicked();

    void on_cleanConsole_clicked();

    void on_inputMessage_returnPressed();

private:
    void outputText(QString outText);
    Ui::udpChat *ui;
    Exchange *exchange;
};
#endif // UDPCHAT_H
