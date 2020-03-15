#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMessageBox>
#include <functional>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_tcpClientPtr = new TcpClientWrapper(this);
    m_parserPtr = new MessageParser(this);
    m_commandsPtr = new PclCommands(this);
    m_tcpClientPtr->setMessageParserPtr(m_parserPtr);
    ui->connectButton->setState(false);
    ui->linePort->setStyleSheet(lineEditStyle);
    ui->lineIp->setStyleSheet(lineEditStyle);
    ui->linePort->setText("9991");
    ui->lineIp->setText("emb2.extcam.xyz");

    connect(m_commandsPtr,&PclCommands::setStateSignal,
            ui->light,&LightWidget::setOnOff);

    connect(m_commandsPtr,&PclCommands::setColorSignal,
            ui->light,&LightWidget::setColorSlot);


    connect(m_tcpClientPtr,&TcpClientWrapper::isConnected,this,[this](bool _state){
        if(! _state)
            ui->light->setOnOff(_state);
    });

    connect(ui->connectButton,&ConnectButton::clicked,
            this,[this](bool _connect){
        //if(!checkForCorrectInput()){
        //    QMessageBox::warning(this,tr("Error in input"),tr("Check for correct Input in ip or port!"));
        //    ui->connectButton->setState(false);
        //    return;
        //}

        if(_connect)
            m_tcpClientPtr->connectToHost(ui->lineIp->text(),
                                          ui->linePort->text().toUInt());
        else
            m_tcpClientPtr->disconnectFromHost();
    });


    connect(m_tcpClientPtr,&TcpClientWrapper::isConnected,
            ui->connectButton,&ConnectButton::setState);


    addRegisteredCommands();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkForCorrectInput()
{
    bool isCorrectIp = false;
    bool isCorrectPort = false;
    QRegularExpression ipPattern("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    QString addr = ui->lineIp->text();
    QRegularExpressionMatch mre = ipPattern.match(addr);
    QStringList count = mre.capturedTexts();

    if ((count.size() > 0) && (count.contains(addr)))
       isCorrectIp = true;

    QRegularExpression addrPattern("^()([1-9]|[1-5]?[0-9]{2,4}|6[1-4][0-9]{3}|65[1-4][0-9]{2}|655[1-2][0-9]|6553[1-5])$");
    QString port = ui->linePort->text();
    mre = addrPattern.match(port);
    count = mre.capturedTexts();
    if ((count.size() > 0) && (count.contains(port)))
       isCorrectPort = true;


   return isCorrectIp & isCorrectPort;
}

void MainWindow::addRegisteredCommands()
{
   m_parserPtr->registerCommand(PclCommands::On,
                                std::bind(&PclCommands::onCommand,
                                          m_commandsPtr,
                                          std::placeholders::_1));

   m_parserPtr->registerCommand(PclCommands::Off,
                                std::bind(&PclCommands::offCommand,
                                          m_commandsPtr,
                                          std::placeholders::_1));

   m_parserPtr->registerCommand(PclCommands::Color,
                                std::bind(&PclCommands::colorCommand,
                                          m_commandsPtr,
                                          std::placeholders::_1));
}
