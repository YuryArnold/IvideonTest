#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H
#include <QObject>
#include <QByteArray>
#include <QList>

class MessageParser : public QObject
{
    Q_OBJECT
public:
    explicit MessageParser(QObject* parent = nullptr);
    void consumeData(const QByteArray& _message);
    void registerCommand(quint32 _id, std::function<void(QByteArray& _message)> _command);

private:
    QHash<quint32,std::function<void(QByteArray& _message)>> m_messageCommands;
    QByteArray m_unaccomplishedBuffer;
    uint16_t m_lenOfInfMes;
    uint16_t m_lenOfInfPlusId;
};

#endif // MESSAGEPARSER_H
