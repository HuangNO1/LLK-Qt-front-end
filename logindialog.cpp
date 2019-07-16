#include "logindialog.h"
#include "mylabel.h"
#include "ui_logindialog.h"
#include <QFile>
#include <QFont>
#include <QIcon>
#include <QLabel>
#include <QPalette>
#include <QParallelAnimationGroup>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QSpinBox>
#include <QString>
#include <QStyle>
#include <QWidget>
#include <QColor>

loginDialog::loginDialog(QWidget *parent) : QDialog(parent),
                                            ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::FramelessWindowHint);
    // 設計Qwidget邊框
    this->setStyleSheet("QWidget { border-top-left-radius:15px;border-top-right-radius:5px;"
                        "border-bottom-right-radius:15px;border-bottom-left-radius:5px;}");
    // 無邊框窗口
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    //int wide = width();//獲取界面的寬度
    // 構建最小化、最大化、關閉按鈕
    minButton = new QToolButton(this);
    closeButton = new QToolButton(this);
    // QToolButton *maxButton= new QToolButton(this);

    // 獲取最小化、關閉按鈕圖標
    QPixmap minPix = QPixmap(":/images/icon/min.png");
    QPixmap closePix = QPixmap(":/images/icon/close.png");
    // QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);

    // 設置最小化、關閉按鈕圖標
    minButton->setIcon(minPix);
    closeButton->setIcon(closePix);
    // maxButton->setIcon(maxPix);

    // 設置最小化、關閉按鈕在界面的位置
    minButton->setGeometry(555, 0, 21, 21);
    closeButton->setGeometry(580, 0, 21, 21);
    // maxButton->setGeometry(wide-45,5,20,40);
    /*
    // 設置鼠標移至按鈕上的提示信息
    minButton->setToolTip(tr("最小化"));
    closeButton->setToolTip(tr("关闭"));
    maxButton->setToolTip(tr("最大化"));
*/
    //設置最小化、關閉按鈕的樣式
    minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");
    // maxButton->setStyleSheet("background-color:transparent;");

    connect(closeButton, SIGNAL(clicked()), this, SLOT(windowClose()));
    connect(minButton, SIGNAL(clicked()), this, SLOT(showMinimized()));
    // connect(maxButton, SIGNAL(clicked()), this, SLOT(winmax()));

    // 設置窗口 icon title
    QIcon icon(":/images/icon/LLK.png");
    setWindowIcon(icon);
    setWindowTitle(QStringLiteral("LLK"));

    // 登入畫面淡入的動畫
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();

    // 設置 START MESSAGE label 樣式
    my_label = new Mylabel("START  MESSAGE", this);
    my_label->setGeometry(QRect(160, 270, 301, 51));
    my_label->setAlignment(Qt::AlignCenter); // 文字居中
    my_label->setStyleSheet("QLabel { background-color : rgb(102, 184, 255); color : white}");

    QFont ft;
    ft.setPointSize(16);
    ft.setFamily("Corbel");
    my_label->setFont(ft);

    // 設置 label_icon 的 image
    QPixmap *pixmap = new QPixmap(":/images/icon/LLK.png");
    pixmap->scaled(ui->label_icon->size(), Qt::KeepAspectRatio);
    ui->label_icon->setScaledContents(true);
    ui->label_icon->setPixmap(*pixmap);

    connect(my_label, SIGNAL(clicked(QString)), this, SLOT(button_click(QString)));

    // 設置 login_label

    login_label = new Mylabel("Login", this);
    login_label->setGeometry(QRect(330, 310, 221, 41));
    login_label->setAlignment(Qt::AlignCenter); // 文字居中
    login_label->setStyleSheet("QLabel { background-color : rgb(102, 184, 255); color : white;}");

    QFont ft_login;
    ft_login.setPointSize(14);
    ft_login.setFamily("Corbel");
    login_label->setFont(ft_login);
    login_label->setVisible(false);

    connect(login_label, SIGNAL(clicked(QString)), this, SLOT(button_click(QString)));

    // 設置 register_label
    register_label = new Mylabel("Register", this);
    register_label->setGeometry(QRect(50, 310, 221, 41));
    register_label->setAlignment(Qt::AlignCenter); // 文字居中
    register_label->setStyleSheet("QLabel { background-color : rgb(102, 184, 255); color : white;}");
    register_label->setFont(ft_login);
    register_label->setVisible(false);
    connect(register_label, SIGNAL(clicked(QString)), this, SLOT(button_click(QString)));

    // 設置 username password 的 label textEdit
    ui->usrlabel->setVisible(false);
    ui->pwdlabel->setVisible(false);
    ui->usrlineEdit->setVisible(false);
    ui->pwdlineEdit->setVisible(false);

    // 設置 invalid_label
    ui->invalid_label->setVisible(false);

    // 設置 setting_label
    QPixmap *pixmap_setting = new QPixmap(":/images/icon/settings_black.png");
    setting_label = new scrollLabel(pixmap_setting, this);
    setting_label->setGeometry(QRect(10, 10, 51, 51));
    setting_label->setScaledContents(true);
    setting_label->setVisible(false);
    setting_label->setText("");
    connect(setting_label, SIGNAL(clicked(QString)), this, SLOT(button_click(QString)));

    // 設置 登入的 lineEdit
    ui->usrlineEdit->setStyleSheet("QLineEdit { padding : 2px; }");
    ui->pwdlineEdit->setStyleSheet("QLineEdit { padding : 2px; }");

    // 設置 register 的介面控件-----------------------
    QFont ft_r_mylabel;
    ft_r_mylabel.setPointSize(16);
    ft_r_mylabel.setFamily("Corbel");

    confirm_regiter = new Mylabel("Confirm", this);
    confirm_regiter->setGeometry(QRect(390, 350, 341, 51));
    confirm_regiter->setAlignment(Qt::AlignCenter); // 文字居中
    confirm_regiter->setStyleSheet("QLabel { background-color : rgb(102, 184, 255); color : white}");
    confirm_regiter->setFont(ft_r_mylabel);
    confirm_regiter->setVisible(false);
    connect(confirm_regiter, SIGNAL(clicked(QString)), this, SLOT(button_click(QString)));

    cancel_register = new Mylabel("Cancel", this);
    cancel_register->setGeometry(QRect(30, 350, 341, 51));
    cancel_register->setAlignment(Qt::AlignCenter); // 文字居中
    cancel_register->setStyleSheet("QLabel { background-color : rgb(102, 184, 255); color : white}");
    cancel_register->setFont(ft_r_mylabel);
    cancel_register->setVisible(false);
    connect(cancel_register, SIGNAL(clicked(QString)), this, SLOT(button_click(QString)));

    usrname_r_label = new QLabel("Username", this);
    usrname_r_label->setGeometry(QRect(240, 80, 121, 31));
    usrname_r_label->setFont(ft_r_mylabel);
    usrname_r_label->setVisible(false);

    pwdname_r_label = new QLabel("Password", this);
    pwdname_r_label->setGeometry(QRect(240, 140, 131, 31));
    pwdname_r_label->setFont(ft_r_mylabel);
    pwdname_r_label->setVisible(false);

    con_pwdname_r_label = new QLabel("Confirm Password", this);
    con_pwdname_r_label->setGeometry(QRect(240, 200, 201, 31));
    con_pwdname_r_label->setFont(ft_r_mylabel);
    con_pwdname_r_label->setVisible(false);

    emailname_r_label = new QLabel("E-mail", this);
    emailname_r_label->setGeometry(QRect(240, 260, 111, 31));
    emailname_r_label->setFont(ft_r_mylabel);
    emailname_r_label->setVisible(false);

    QFont ft_r_invaildlabel;
    ft_r_invaildlabel.setPointSize(9);
    ft_r_invaildlabel.setFamily("Corbel");
    invaild_r_label = new QLabel("invaild", this);
    invaild_r_label->setGeometry(QRect(240, 320, 491, 16));
    invaild_r_label->setFont(ft_r_invaildlabel);
    invaild_r_label->setVisible(false);

    QFont ft_r_lineeditlabel;
    ft_r_lineeditlabel.setPointSize(10);
    ft_r_lineeditlabel.setFamily("Noto Sans CJK TC Bold");
    usrname_r_lineedit = new QLineEdit(this);
    usrname_r_lineedit->setGeometry(QRect(460, 80, 271, 31));
    usrname_r_lineedit->setFont(ft_r_lineeditlabel);
    usrname_r_lineedit->setStyleSheet("QLineEdit { padding: 2px;}");
    usrname_r_lineedit->setPlaceholderText("Username");
    usrname_r_lineedit->setVisible(false);

    pwdname_r_lineedit = new QLineEdit(this);
    pwdname_r_lineedit->setGeometry(QRect(460, 140, 271, 31));
    pwdname_r_lineedit->setFont(ft_r_lineeditlabel);
    pwdname_r_lineedit->setStyleSheet("QLineEdit { padding: 2px;}");
    pwdname_r_lineedit->setEchoMode(QLineEdit::Password);
    pwdname_r_lineedit->setPlaceholderText("Password");
    pwdname_r_lineedit->setVisible(false);

    con_pwdname_r_lineedit = new QLineEdit(this);
    con_pwdname_r_lineedit->setGeometry(QRect(460, 200, 271, 31));
    con_pwdname_r_lineedit->setFont(ft_r_lineeditlabel);
    con_pwdname_r_lineedit->setStyleSheet("QLineEdit { padding: 2px;}");
    con_pwdname_r_lineedit->setEchoMode(QLineEdit::Password);
    con_pwdname_r_lineedit->setPlaceholderText("Password");
    con_pwdname_r_lineedit->setVisible(false);

    emailname_r_lineedit = new QLineEdit(this);
    emailname_r_lineedit->setGeometry(QRect(460, 260, 271, 31));
    emailname_r_lineedit->setFont(ft_r_lineeditlabel);
    emailname_r_lineedit->setStyleSheet("QLineEdit { padding: 2px;}");
    emailname_r_lineedit->setPlaceholderText("E-mail");
    emailname_r_lineedit->setVisible(false);

    // 頭像
    Avatar_label = new Nolabel("avatar", this);
    Avatar_label->setScaledContents(true);
    Avatar_label->setPixmap(*pixmap);
    Avatar_label->setGeometry(QRect(30, 100, 180, 180));
    Avatar_label->setStyleSheet("QLabel {border-radius: 90px;}");
    Avatar_label->setVisible(false);

    // 註冊成功label
    register_success_icon = new QLabel("", this);
    QPixmap *pixmap_success_register = new QPixmap(":/images/icon/success.png");
    register_success_icon = new scrollLabel(pixmap_setting, this);
    register_success_icon->setGeometry(QRect(50, 50, 251, 251));
    register_success_icon->setPixmap(*pixmap_success_register);
    register_success_icon->setScaledContents(true);
    register_success_icon->setVisible(false);

    register_success_text = new QLabel("SUCCESS", this);
    register_success_text->setGeometry(QRect(330, 140, 341, 81));
    register_success_text->setStyleSheet("QLabel { color : green;}");
    QFont ft_r_success;
    ft_r_success.setPointSize(30);
    ft_r_success.setFamily("corbel");
    register_success_text->setFont(ft_r_success);
    register_success_text->setVisible(false);

    registerSuccess = false;
    //------------------------------------------------

}


loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::button_click(QString data)
{
    qDebug() << "slot mylabel's signal";
    if (data == QString::fromStdString("START  MESSAGE")) // START MESSAGE 鈕被按
    {

        QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
        animation->setDuration(700);
        animation->setStartValue(1);
        animation->setEndValue(0);
        animation->start();
        my_label->setVisible(false);
        ui->label_icon->setVisible(false);
        QTime reachTime = QTime::currentTime().addMSecs(700); // 700 毫秒
        while (QTime::currentTime() < reachTime)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.7sec
        }
        my_label->setVisible(false);
        ui->label_icon->setVisible(false);
        Server = new ConnectToServer(this);
        ui->label->setGeometry(QRect(-3, -6, 611, 25));
        login_label->setVisible(true);
        register_label->setVisible(true);
        ui->usrlabel->setVisible(true);
        ui->pwdlabel->setVisible(true);
        ui->usrlineEdit->setVisible(true);
        ui->pwdlineEdit->setVisible(true);
        ui->invalid_label->setVisible(true);
        setting_label->setVisible(true);
        QPropertyAnimation *animation1 = new QPropertyAnimation(this, "windowOpacity");
        animation1->setDuration(700);
        animation1->setStartValue(0);
        animation1->setEndValue(1);
        animation1->start();
        reachTime = QTime::currentTime().addMSecs(700); // 700 毫秒
        while (QTime::currentTime() < reachTime)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.7sec
        }
        Server->show();
        Server->setIsOpen(true);
    }
    if (data == QString::fromStdString("")) // setting 被按
    {
        Server = new ConnectToServer(this);
        if (Server->getIsOpen() == false)
        {
            Server->show();
            Server->setIsOpen(true);
        }

        //this->hide();
    }
    if (data == QString::fromStdString("Login")) // 登入鈕被按
    {
        Server->close();               // 關掉 Server
        Server->hide();
        if (Server->getFlag() == true) // 連網成功
        {
            QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
            animation->setDuration(700);
            animation->setStartValue(1);
            animation->setEndValue(0);
            animation->start();
            // 延遲執行時間，看到變化效果
            QTime reachTime = QTime::currentTime().addMSecs(700); // 700 毫秒
            while (QTime::currentTime() < reachTime)
            {
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.7sec
            }
            Server->close();
            Server->hide();
            accept(); // 登入成功
        }
    }
    if (data == QString::fromStdString("Register")) // 註冊被按
    {
        Server->close(); // 關掉 Server
        Server->hide();
        if (Server->getFlag() == true)
        {
            QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
            animation->setDuration(700);
            animation->setStartValue(1);
            animation->setEndValue(0);
            animation->start();
            QTime reachTime = QTime::currentTime().addMSecs(700); // 700 毫秒
            while (QTime::currentTime() < reachTime)
            {
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.7sec
            }
            // 消除原視窗
            this->setFixedSize(757, 430);
            ui->label->setGeometry(QRect(0, 0, 761, 31));
            login_label->setVisible(false);
            register_label->setVisible(false);
            ui->usrlabel->setVisible(false);
            ui->pwdlabel->setVisible(false);
            ui->usrlineEdit->setVisible(false);
            ui->pwdlineEdit->setVisible(false);
            ui->invalid_label->setVisible(false);
            setting_label->setVisible(false);
            // 加載新註冊頁面
            minButton->setGeometry(705, 0, 21, 21);
            closeButton->setGeometry(730, 0, 21, 21);
            Avatar_label->setVisible(true);
            ui->label->setGeometry(QRect(0, 0, 761, 31));
            confirm_regiter->setVisible(true);
            cancel_register->setVisible(true);
            usrname_r_label->setVisible(true);
            pwdname_r_label->setVisible(true);
            con_pwdname_r_label->setVisible(true);
            emailname_r_label->setVisible(true);
            invaild_r_label->setVisible(true);
            usrname_r_lineedit->setVisible(true);
            pwdname_r_lineedit->setVisible(true);
            con_pwdname_r_lineedit->setVisible(true);
            emailname_r_lineedit->setVisible(true);
            QPropertyAnimation *animation1 = new QPropertyAnimation(this, "windowOpacity");
            animation1->setDuration(700);
            animation1->setStartValue(0);
            animation1->setEndValue(1);
            animation1->start();
            reachTime = QTime::currentTime().addMSecs(700); // 700 毫秒
            while (QTime::currentTime() < reachTime)
            {
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.7sec
            }
        }
    }
    if (data == QString::fromStdString("Cancel") || data == QString::fromStdString("Confirm")) // 取消註冊 && 成功註冊
    {
        qDebug() << "register dialog";
        registerSuccess = true;                                                   // test
        if (data == QString::fromStdString("Confirm") && registerSuccess == true) // 註冊成功畫面
        {
            Avatar_label->setVisible(false);
            confirm_regiter->setVisible(false);
            cancel_register->setVisible(false);
            usrname_r_label->setVisible(false);
            pwdname_r_label->setVisible(false);
            con_pwdname_r_label->setVisible(false);
            emailname_r_label->setVisible(false);
            invaild_r_label->setVisible(false);
            usrname_r_lineedit->setVisible(false);
            pwdname_r_lineedit->setVisible(false);
            con_pwdname_r_lineedit->setVisible(false);
            emailname_r_lineedit->setVisible(false);
            register_success_icon->setVisible(true);
            register_success_text->setVisible(true);
            QTime reachTime = QTime::currentTime().addMSecs(700); // 700 毫秒
            while (QTime::currentTime() < reachTime)
            {
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.7sec
            }
        }
        QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
        animation->setDuration(700);
        animation->setStartValue(1);
        animation->setEndValue(0);
        animation->start();
        QTime reachTime = QTime::currentTime().addMSecs(700); // 700 毫秒
        while (QTime::currentTime() < reachTime)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.7sec
        }
        this->setFixedSize(606, 371);
        Avatar_label->setVisible(false);
        confirm_regiter->setVisible(false);
        cancel_register->setVisible(false);
        usrname_r_label->setVisible(false);
        pwdname_r_label->setVisible(false);
        con_pwdname_r_label->setVisible(false);
        emailname_r_label->setVisible(false);
        invaild_r_label->setVisible(false);
        usrname_r_lineedit->setVisible(false);
        pwdname_r_lineedit->setVisible(false);
        con_pwdname_r_lineedit->setVisible(false);
        emailname_r_lineedit->setVisible(false);
        register_success_icon->setVisible(false);
        register_success_text->setVisible(false);

        ui->label->setGeometry(QRect(-3, -6, 611, 25));
        login_label->setVisible(true);
        register_label->setVisible(true);
        ui->usrlabel->setVisible(true);
        ui->pwdlabel->setVisible(true);
        ui->usrlineEdit->setVisible(true);
        ui->pwdlineEdit->setVisible(true);
        ui->invalid_label->setVisible(true);
        setting_label->setVisible(true);
        minButton->setGeometry(555, 0, 21, 21);
        closeButton->setGeometry(580, 0, 21, 21);
        QPropertyAnimation *animation1 = new QPropertyAnimation(this, "windowOpacity");
        animation1->setDuration(700);
        animation1->setStartValue(0);
        animation1->setEndValue(1);
        animation1->start();
        reachTime = QTime::currentTime().addMSecs(700); // 700 毫秒
        while (QTime::currentTime() < reachTime)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.7sec
        }
        Server->show();
        Server->setIsOpen(true);
        registerSuccess = false; // 初始化
    }
}

void loginDialog::windowClose()
{
    // 登入畫面淡出的動畫
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    // 延遲執行時間，看到變化效果
    QTime reachTime = QTime::currentTime().addMSecs(1000); // 1000 毫秒
    while (QTime::currentTime() < reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 1sec
    }
    this->close();
}

//拖拽操作
void loginDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrag = true;
        //獲得鼠標的初始位置
        mouseStartPoint = event->globalPos();
        //獲得窗口的初始位置
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
}

void loginDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (isDrag)
    {
        //获得鼠标移动的距离
        QPoint distance = event->globalPos() - mouseStartPoint;
        //改变窗口的位置
        this->move(windowTopLeftPoint + distance);
    }
}

void loginDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrag = false;
    }
}

scrollLabel::scrollLabel(const QPixmap *pixmap, QWidget *parent)
    : QLabel(parent)
{
    // 初始化變量
    m_rotateAngle = 0;
    m_enterId = 0;
    m_leaveId = 0;

    pixmap->scaled(this->size(), Qt::KeepAspectRatio);
    m_pixmap = *pixmap;
    // 設置顯示的圖片
    this->setPixmap(m_pixmap);
}

void scrollLabel::enterEvent(QEvent *event)
{
    if (m_leaveId == 0)
    {
        m_enterId = this->startTimer(Time, Qt::PreciseTimer);
        qDebug("enter");
    }
}
void scrollLabel::leaveEvent(QEvent *event)
{
    if (m_enterId == 0)
    {
        m_leaveId = this->startTimer(Time, Qt::PreciseTimer);
        qDebug("leave");
    }
}
void scrollLabel::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_enterId)
    {
        QMatrix matrix;
        m_rotateAngle += FixedAngle;
        // 設置轉的操作
        matrix.rotate(m_rotateAngle);
        // 獲取旋轉後的圖片
        QPixmap temp = m_pixmap.transformed(matrix);
        this->setPixmap(temp);

        // 當轉到一圈後
        if (m_rotateAngle == 60)
        {
            // 歸零定殺死計時器
            m_rotateAngle = 0;
            this->killTimer(m_enterId);
            m_enterId = 0;
        }
    }
    else if (event->timerId() == m_leaveId)
    {
        QMatrix matrix;
        m_rotateAngle -= FixedAngle;
        matrix.rotate(m_rotateAngle);
        QPixmap temp = m_pixmap.transformed(matrix);
        this->setPixmap(temp);

        // 當轉到一圈後
        if (m_rotateAngle == -60)
        {
            // 歸零定殺死計時器
            m_rotateAngle = 0;
            this->killTimer(m_leaveId);
            m_leaveId = 0;
        }
    }
}

void scrollLabel::mouseMoveEvent(QMouseEvent *event)
{
    // no action
    qDebug() << "mouseMoveEvent";
}

void scrollLabel::mousePressEvent(QMouseEvent *event)
{
    // no action
    qDebug() << "mousePressEvent";
}

void scrollLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_enterId == 0)
    {
        m_leaveId = this->startTimer(Time, Qt::PreciseTimer);
        qDebug("leave");

        // 延遲執行時間，看到按壓效果
        QTime reachTime = QTime::currentTime().addMSecs(200); // 200 毫秒
        while (QTime::currentTime() < reachTime)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.2sec
        }
        emit clicked(this->text());
    }
}
