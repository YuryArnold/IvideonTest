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
    QRgb color = fromBytesToBE(_message);
    emit setColorSignal(color);
}
