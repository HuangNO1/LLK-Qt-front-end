#include "connecttoserver.h"
#include "ui_connecttoserver.h"

ConnectToServer::ConnectToServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectToServer)
{
    ui->setupUi(this);

    // 無邊框窗口
    // setWindowFlags(Qt::FramelessWindowHint);
    // setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    QIcon icon(":/images/icon/LLK.png");
    setWindowIcon(icon);
    setWindowTitle(QStringLiteral("Connect Server"));

    // 固定窗口
    this->setFixedSize(this->width(), this->height());

    // 設置 Connect mylabel

    Connect = new Mylabel("Connect",this);
    Connect->setGeometry(QRect(50, 160, 100, 51));
    Connect->setAlignment(Qt::AlignCenter); // 文字居中
    Connect->setStyleSheet("QLabel { background-color : rgb(102, 184, 255); color : white;}");

    // 設置 Quit mylabel
    Quit = new Mylabel("Quit",this);
    Quit->setGeometry(QRect(240, 160, 100, 51));
    Quit->setAlignment(Qt::AlignCenter); // 文字居中
    Quit->setStyleSheet("QLabel { background-color : rgb(102, 184, 255); color : white;}");
    // 設字體
    QFont ft;
    ft.setPointSize(14);
    ft.setFamily("Corbel");
    Connect->setFont(ft);
    Quit->setFont(ft);
    // 關視窗事件
    connect(Quit, SIGNAL(clicked(QString)), this, SLOT(closeWindows(QString)));

    ui->Server_lineEdit->setText(Ip);
    ui->Port_spinBox->setValue(Port);

    ui->portlabel->setVisible(true);
    ui->serverlabel->setVisible(true);
    ui->Port_spinBox->setVisible(true);
    ui->Server_lineEdit->setVisible(true);
    Connect->setVisible(true);

    QPixmap *pixmap = new QPixmap(":/images/icon/success.png");
    pixmap->scaled(ui->label_connectSuccess->size(), Qt::KeepAspectRatio);
    ui->label_connectSuccess->setScaledContents(true);
    ui->label_connectSuccess->setPixmap(*pixmap);
    ui->label_connectSuccess->setVisible(false);

    ui->label_descript->setText(tr("SUCCESS"));
    ui->label_descript->setAlignment(Qt::AlignCenter); // 文字居中
    ui->label_descript->setStyleSheet("QLabel { color : green;}");
    ft.setPointSize(16);
    ft.setFamily("Corbel");
    ui->label_descript->setFont(ft);
    ui->label_descript->setVisible(false);

    connect(Connect, SIGNAL(clicked(QString)), this, SLOT(createDataRecvWS(QString)));
    connect(Connect, SIGNAL(clicked(QString)), this, SLOT(restore(QString)));

    dataRecvWS = Q_NULLPTR;
    connectStatus = false;
    m_timer = new QTimer();
}

ConnectToServer::~ConnectToServer()
{
    isOpen = false; // 窗口關閉
    delete ui;
}

void ConnectToServer::closeWindows(QString data)
{
    if(data == QString::fromStdString("Quit"))
    {
        QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
        animation->setDuration(500);
        animation->setStartValue(1);
        animation->setEndValue(0);
        animation->start();
        // 延遲執行時間，看到變化效果
        QTime reachTime = QTime::currentTime().addMSecs(500); // 500 毫秒
        while (QTime::currentTime() < reachTime)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.5sec
        }
        Ip = ui->Server_lineEdit->text();
        Port = ui->Port_spinBox->value();
        this->close();
        isOpen = false; // 窗口關閉
    }
}


void ConnectToServer::restore(QString data)
{
    /*
    if(data == QString::fromStdString("Change"))
    {
        ui->portlabel->setVisible(true);
        ui->serverlabel->setVisible(true);
        ui->Port_spinBox->setVisible(true);
        ui->Server_lineEdit->setVisible(true);
        ui->label_connectSuccess->setVisible(false);
        ui->label_descript->setVisible(false);
        Connect->setText(tr("Connect"));
    }
    */
}

bool ConnectToServer::getIsOpen()
{
    return isOpen;
}
void ConnectToServer::setIsOpen(bool newIsOpen)
{
    isOpen = newIsOpen;
}
void ConnectToServer::closeEvent(QCloseEvent *event)
{
    isOpen = false;
    qDebug() << "ConnectServer close";
}

bool ConnectToServer::getFlag()
{
    return connectStatus;
}

void ConnectToServer::createDataRecvWS(QString){
    dataRecvWS = new QWebSocket();
    qDebug()<<"create websocket!";
    connect(dataRecvWS, &QWebSocket::disconnected, this, &ConnectToServer::onDisConnected, Qt::AutoConnection);
    connect(dataRecvWS, &QWebSocket::textMessageReceived, this, &ConnectToServer::onTextReceived, Qt::AutoConnection);
    connect(dataRecvWS, &QWebSocket::connected, this, &ConnectToServer::onConnected, Qt::AutoConnection);
    connect(m_timer, &QTimer::timeout, this, &ConnectToServer::reconnect, Qt::AutoConnection);
    QString url = tr("ws://") + ui->Server_lineEdit->text() + tr(":") + QString::number(ui->Port_spinBox->value());

    dataRecvWS->open(QUrl(url));
}


/**
 * @breaf 判断连接状态
 * @note  当连接成功后，触发该函数
 */
void ConnectToServer::onConnected(){
    qDebug()<<"DataReveive websocket is already connect!";
    connectStatus = true;
    m_timer->stop();
    qDebug()<<"Address："<<dataRecvWS->peerAddress();
    if(connectStatus == true)
    {
        ui->portlabel->setVisible(false);
        ui->serverlabel->setVisible(false);
        ui->Port_spinBox->setVisible(false);
        ui->Server_lineEdit->setVisible(false);
        //Connect->setText(tr("Change"));
        Connect->setVisible(false);
        QPixmap *pixmap = new QPixmap(":/images/icon/success.png");
        pixmap->scaled(ui->label_connectSuccess->size(), Qt::KeepAspectRatio);
        ui->label_connectSuccess->setScaledContents(true);
        ui->label_connectSuccess->setPixmap(*pixmap);
        ui->label_connectSuccess->setVisible(true);
        ui->label_descript->setText(tr("SUCCESS"));
        ui->label_descript->setStyleSheet("QLabel { color : green;}");
        ui->label_descript->setVisible(true);
        QTime reachTime = QTime::currentTime().addMSecs(1000); // 1000 毫秒
        while (QTime::currentTime() < reachTime)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 1sec
        }
        this->close();
        Connect->setVisible(true);
        ui->portlabel->setVisible(true);
        ui->serverlabel->setVisible(true);
        ui->Port_spinBox->setVisible(true);
        ui->Server_lineEdit->setVisible(true);
        ui->label_connectSuccess->setVisible(false);
        ui->label_descript->setVisible(false);
    }
}

/**
 * @breaf 数据处理函数
 * @param msg，数据信息
 * @note  当收到服务端发送的数据时，触发该函数
 */
void ConnectToServer::onTextReceived(QString msg){
    qDebug()<<"----------------data-----------------";
    qDebug()<<msg;
}

/**
 * @breaf 连接断开
 * @note  当连接断开时，触发该函数
 */
void ConnectToServer::onDisConnected(){
    qDebug()<<"DataReceive websocket is disconnected!!!";
    connectStatus = false;
    m_timer->start(3000);/*-<当连接失败时，触发重连计时器，设置计数周期为3秒 */
    if(connectStatus == false)
    {
        ui->portlabel->setVisible(false);
        ui->serverlabel->setVisible(false);
        ui->Port_spinBox->setVisible(false);
        ui->Server_lineEdit->setVisible(false);
        QPixmap *pixmap = new QPixmap(":/images/icon/error.png");
        pixmap->scaled(ui->label_connectSuccess->size(), Qt::KeepAspectRatio);
        ui->label_connectSuccess->setScaledContents(true);
        ui->label_connectSuccess->setPixmap(*pixmap);
        ui->label_connectSuccess->setVisible(true);
        ui->label_descript->setText(tr("FAIL :("));
        ui->label_descript->setStyleSheet("QLabel { color : red;}");
        ui->label_descript->setVisible(true);
        Connect->setVisible(false);

        QTime reachTime = QTime::currentTime().addMSecs(1000); // 1000 毫秒
        while (QTime::currentTime() < reachTime)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 1sec
        }
        ui->portlabel->setVisible(true);
        ui->serverlabel->setVisible(true);
        ui->Port_spinBox->setVisible(true);
        ui->Server_lineEdit->setVisible(true);
        ui->label_connectSuccess->setVisible(false);
        ui->label_descript->setVisible(false);
        Connect->setVisible(true);
    }
}
void ConnectToServer::reconnect(){
    m_timer->stop();
    qDebug()<<"try to reconnect!";
    dataRecvWS->abort();
    QString url = tr("ws://") + ui->Server_lineEdit->text() + tr(":") + QString::number(ui->Port_spinBox->value());
    //dataRecvWS->open(QUrl(url));

}

