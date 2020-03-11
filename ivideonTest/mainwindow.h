#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpclientwrapper.h"
#include "messageparser.h"
#include "pclcommands.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool checkForCorrectInput();
    void addRegisteredCommands();

private:
    Ui::MainWindow *ui;
    TcpClientWrapper* m_tcpClientPtr;
    MessageParser* m_parserPtr;
    PclCommands* m_commandsPtr;
};

#endif // MAINWINDOW_H
