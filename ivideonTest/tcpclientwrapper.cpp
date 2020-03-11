#include "tcpclientwrapper.h"
#include <QHostAddress>

TcpClientWrapper::TcpClientWrapper(QObject *parent) : QObject(parent)
{
    m_socketPtr = new QTcpSocket(this);

    connect(m_socketPtr, &QTcpSocket::readyRead,
            this, &TcpClientWrapper::readyReadSlot);

    connect(m_socketPtr,QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),
            this,[this](QAbstractSocket::SocketError socketError){
            qDebug()<<"Error in opening connection!"<<m_socketPtr->errorString();
            m_socketPtr->disconnectFromHost();
            m_socketPtr->close();
    });

    timeOfConnectionObserve.setSingleShot(true);
    timeOfConnectionObserve.setInterval(5000);
    connect(&timeOfConnectionObserve,&QTimer::timeout,
            this,&TcpClientWrapper::disconnectedSlot);

    connect(m_socketPtr,&QTcpSocket::connected,
            this,&TcpClientWrapper::connectedSlot);

    connect(m_socketPtr,&QTcpSocket::disconnected,
            this,&TcpClientWrapper::disconnectedSlot);

}

TcpClientWrapper::~TcpClientWrapper()
{
    if(m_socketPtr->isOpen())
        m_socketPtr->disconnectFromHost();
}

void TcpClientWrapper::connectToHost(const QString _ip, quint16 _port)
{
    timeOfConnectionObserve.start();
    m_socketPtr->connectToHost(_ip,_port,QIODevice::ReadOnly,
                               QAbstractSocket::NetworkLayerProtocol::IPv4Protocol);
}

void TcpClientWrapper::disconnectFromHost()
{
    m_socketPtr->disconnectFromHost();
}

void TcpClientWrapper::setMessageParserPtr(MessageParser *_parser)
{
    m_parserPtr = _parser;
}

void TcpClientWrapper::readyReadSlot()
{
    m_parserPtr->consumeData(m_socketPtr->readAll());
}


void TcpClientWrapper::connectedSlot()
{
    timeOfConnectionObserve.stop();
    emit isConnected(true);
}

void TcpClientWrapper::disconnectedSlot()
{
    if(m_socketPtr->isOpen()){
        m_socketPtr->disconnectFromHost();
        m_socketPtr->close();
    }
    emit isConnected(false);
}


