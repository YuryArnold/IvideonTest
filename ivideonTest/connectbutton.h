#ifndef CONNECTBUTTON_H
#define CONNECTBUTTON_H

#include <QPushButton>
#include "styles.h"

class ConnectButton : public QPushButton
{
    enum State {
        disconnect,
        waiting,
        connect
    };

    Q_OBJECT
public:
    explicit ConnectButton(QWidget* parent = nullptr);
    virtual ~ConnectButton();

public slots:
    void setState(bool _state);

signals:
    void setOnSignal(bool);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);

private:
    int m_insideState;
    bool wasSetOn;
    State m_state;
    void changeButtonByState();
};

#endif // CONNECTBUTTON_H


