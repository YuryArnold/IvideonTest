#ifndef PCLCOMMANDS_H
#define PCLCOMMANDS_H
#include <QObject>
#include <QRgb>

class PclCommands : public QObject
{
    Q_OBJECT
public:
    enum PClStates{
        On = 0x12,
        Off = 0x13,
        Color = 0x20
    };

signals:
    void setStateSignal(bool _state);
    void setColorSignal(QRgb _color);

public:
    explicit PclCommands(QObject* parent = nullptr);
    void onCommand(QByteArray& _message);
    void offCommand(QByteArray& _message);
    void colorCommand(QByteArray& _message);
};

#endif // PCLCOMMANDS_H
