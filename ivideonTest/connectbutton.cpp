#include "connectbutton.h"
#include <QMouseEvent>

ConnectButton::ConnectButton(QWidget *parent):QPushButton (parent)
{
    m_state = disconnect;
    wasSetOn = false;
    changeButtonByState();
}

ConnectButton::~ConnectButton()
{

}

void ConnectButton::setState(bool _state)
{
    m_state = (!_state)?disconnect:connect;
    wasSetOn = _state;
    changeButtonByState();
}


void ConnectButton::mousePressEvent(QMouseEvent *event)
{
    if(m_state == waiting){
        return;
    }

    if(event->button() == Qt::LeftButton){
        m_state = waiting;
        changeButtonByState();
    }

    wasSetOn = !wasSetOn;
    emit clicked(wasSetOn);
}

void ConnectButton::changeButtonByState()
{
    switch (m_state) {

        case disconnect :
            setText("Connect");
            setStyleSheet(Off);
            break;

        case waiting :
            setText("Waiting");
            break;

        case connect :
            setText("Disconnect");
            setStyleSheet(On);
            break;

        default :
            setText("Undefined");

    }
}
