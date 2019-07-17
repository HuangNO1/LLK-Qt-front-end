#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    // 無邊框窗口
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

    //控件設置
    QPixmap *avatar = new QPixmap(":/images/icon/LLK.png");
    avatar->scaled(ui->avatar_label->size(), Qt::KeepAspectRatio);
    ui->avatar_label->setScaledContents(true);
    ui->avatar_label->setPixmap(*avatar);
    ui->avatar_label->setGeometry(20,20,71,71);
    ui->username->setText("Huang Po-Hsun");
    ui->username->setGeometry(100, 40, 191, 41);

    QFont ft;
    ft.setPointSize(15);
    ft.setFamily("Corbel");


    connectNetWork = new whitelabel("Connect To Server", this);
    connectNetWork->setGeometry(QRect(0, 121, 301, 60));
    connectNetWork->setAlignment(Qt::AlignLeft); // 文字靠左
    connectNetWork->setStyleSheet("QLabel { background-color : white; color : black;padding:15px;}");
    connectNetWork->setFont(ft);
    connect(connectNetWork, SIGNAL(clicked(QString)), this, SLOT(button_click(QString)));

    SignOut = new whiteToRedlabel("Log Out", this);
    SignOut->setGeometry(QRect(0, 181, 301, 60));
    SignOut->setAlignment(Qt::AlignLeft); // 文字靠左
    SignOut->setStyleSheet("QLabel { background-color : white; color : black;padding:15px;}");
    SignOut->setFont(ft);
    connect(SignOut, SIGNAL(clicked(QString)), this, SLOT(button_click(QString)));
    clickLogout = false;

    //Server = new
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::button_click(QString data)
{
    if (data == QString::fromStdString("Connect To Server")) // connectNetWork 鈕被按
    {
        qDebug() << "Connect To Server";
        //Server = new ConnectToServer(this);
        this->setVisible(false);
        connectNetWork->setAlignment(Qt::AlignLeft); // 文字靠左
        connectNetWork->setStyleSheet("QLabel { background-color : white; color : black;padding:15px;}");
        clickLogout = false;
    }
    if(data == QString::fromStdString("Log Out")) // SignOut 鈕被按
    {
        qDebug() << "Log Out";
        this->setVisible(false);
        SignOut->setAlignment(Qt::AlignLeft); // 文字靠左
        SignOut->setStyleSheet("QLabel { background-color : white; color : black;padding:15px;}");
        clickLogout = true;
    }
    emit isCloseSetting();
}

void SettingDialog::resizeEvent(QResizeEvent *event)
{
    ui->background_label->setGeometry(0,0,301,121);
    ui->avatar_label->setGeometry(20,20,71,71);
    ui->username->setGeometry(100, 40, 191, 41);
    connectNetWork->setGeometry(QRect(0, 121, 301, 60));
    SignOut->setGeometry(QRect(0, 181, 301, 60));
    ui->label->setGeometry(0, this->height() - 50, 201, 41);
    connectNetWork->setAlignment(Qt::AlignLeft); // 文字靠左
    connectNetWork->setStyleSheet("QLabel { background-color : white; color : black;padding:15px;}");
    SignOut->setAlignment(Qt::AlignLeft); // 文字靠左
    SignOut->setStyleSheet("QLabel { background-color : white; color : black;padding:15px;}");
}

