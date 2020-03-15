#include "pclcommands.h"
#include <QColor>
#include <algorithm>
#include <QRgb>
#include "frombytestobe.h"

PclCommands::PclCommands(QObject *parent) : QObject (parent)
{

}

void PclCommands::onCommand(QByteArray& _message)
{
    emit setStateSignal(true);
}

void PclCommands::offCommand(QByteArray& _message)
{
    emit setStateSignal(false);
}

void PclCommands::colorCommand(QByteArray& _message)
{
    QRgb color = qRgb(int{_message[0]},
                      int{_message[1]},
                      int{_message[2]});

    emit setColorSignal(color);
}
