#include "messageparser.h"
#include <QDebug>
#include "frombytestobe.h"

MessageParser::MessageParser(QObject *parent) : QObject(parent),
    m_lenOfInfMes(2),
    m_lenOfInfPlusId(3)
{

}

void MessageParser::consumeData(const QByteArray &_message)
{
    QByteArray message;
    if (!m_unaccomplishedBuffer.isEmpty()){
        message = m_unaccomplishedBuffer;
        m_unaccomplishedBuffer.clear();
    }
    message.push_back(_message);
    int ind = 0;
    int bytesLeft = message.length();
    while(bytesLeft >= m_lenOfInfPlusId) {
        auto code = message[ind++];
        auto subPart = message.mid(ind,2);
        auto len = fromBytesToBE(subPart);
        ind += m_lenOfInfMes;
        auto data = message.mid(ind,len);
        if(data.length() < len){
            ind -=m_lenOfInfPlusId;
            break;
        }
        ind+=len;
        bytesLeft -= (m_lenOfInfPlusId + len);
        if(m_messageCommands.contains(code))
            m_messageCommands[code](data);
        else {
            qDebug()<<"Unknown command with type "<<code<<" has arrived.";
        }
    }
    m_unaccomplishedBuffer.push_back(message.mid((ind)));
}

void MessageParser::registerCommand(quint32 _id, std::function<void (QByteArray &)> _command)
{
    if(!m_messageCommands.contains(_id))
        m_messageCommands[_id] = _command;
}



