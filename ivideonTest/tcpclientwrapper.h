#ifndef TCPCLIENTWRAPPER_H
#define TCPCLIENTWRAPPER_H

#include <QTcpSocket>
#include <QTimer>
#include <messageparser.h>

class TcpClientWrapper : public QObject
{
    Q_OBJECT
public:
    explicit TcpClientWrapper(QObject* parent = nullptr);
    virtual ~TcpClientWrapper();
    void connectToHost(const QString _ip, quint16 _port);
    void disconnectFromHost();
    void setMessageParserPtr(MessageParser* _parser);

signals:
    void isConnected(bool);

private slots:
     void readyReadSlot();
     void connectedSlot();
     void disconnectedSlot();

private:
    QTcpSocket* m_socketPtr;
    MessageParser* m_parserPtr;
    QTimer timeOfConnectionObserve;
};

#endif // TCPCLIENTWRAPPER_H
