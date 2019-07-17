#include "llk.h"
#include "ui_llk.h"

LLK::LLK(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::LLK)
{
    ui->setupUi(this);
    /*
    // 設定 scrollbar 樣式
    QFile file(":/qss/qss/scrollbar.qss");
    file.open(QFile::ReadOnly);
    ui->listWidget->verticalScrollBar()->setStyleSheet(file.readAll());
    */
    /*
    QFile file(":/style/qss/scrollbar.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    ui->listWidget->verticalScrollBar()->setStyleSheet(stylesheet);
    file.close();
    */
    // 無邊框窗口
    setWindowFlags(Qt::FramelessWindowHint);
    //如果啟用了滑鼠追蹤，即使沒有按下按鈕，控件也會接收到鼠標移動事件。
    setMouseTracking(true);
    /*当前窗口顯示為頂級窗口，如果沒有這句的話，窗口就可能會出現在底層
     *，被别的頁面層覆蓋而看不到了.
    */
    this->activateWindow();
    int wide = width(); //獲取界面的寬度
    // 構建最小化、最大化、關閉按鈕
    minButton = new QToolButton(this);
    closeButton = new QToolButton(this);
    maxButton = new QToolButton(this);
    maxWindow = false; // 初始化數值，表示視窗還沒做大化

    // 獲取最小化、關閉按鈕圖標
    QPixmap minPix = QPixmap(":/images/icon/min.png");
    QPixmap closePix = QPixmap(":/images/icon/close.png");
    QPixmap maxPix = QPixmap(":/images/icon/max.png");

    // 設置最小化、關閉按鈕圖標
    minButton->setIcon(minPix);
    closeButton->setIcon(closePix);
    maxButton->setIcon(maxPix);

    // 設置最小化、關閉按鈕在界面的位置
    minButton->setGeometry(wide - 66, 0, 21, 21);
    maxButton->setGeometry(wide - 45, 0, 21, 21);
    closeButton->setGeometry(wide - 24, 0, 21, 21);

    // 設置鼠標移至按鈕上的提示信息
    minButton->setToolTip(tr("Minimize"));
    closeButton->setToolTip(tr("close"));
    maxButton->setToolTip(tr("Maximize"));

    //設置最小化、關閉按鈕的樣式
    minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");
    maxButton->setStyleSheet("background-color:transparent;");

    connect(closeButton, SIGNAL(clicked()), this, SLOT(windowHide()));
    connect(maxButton, SIGNAL(clicked()), this, SLOT(windowMax()));
    connect(minButton, SIGNAL(clicked()), this, SLOT(showMinimized()));

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

    // 設計 colseEvent 為最小化至托盤
    init(); // 初始化


    // 聊天框-----------------------------------------
    chat = new CHATMainWindow(this);
    chat->setGeometry(301, 90, 651, 490);
    chat->show();

    // 聊天列表----------------------------------------
    initData();
    //updateButtonNum();

    m_delegate = new ItemDelegate(this);
    /*
    m_filterButtonGroup = new QButtonGroup(this);

    // 设置互斥
    m_filterButtonGroup->setExclusive(true);

    m_filterButtonGroup->addButton(ui->allBtn);
    m_filterButtonGroup->addButton(ui->redBtn);
    m_filterButtonGroup->addButton(ui->blueBtn);
    m_filterButtonGroup->addButton(ui->yellowBtn);

    // 连接信号槽
    connect(m_filterButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));
*/
    ui->listView->setItemDelegate(m_delegate);       //为视图设置委托
    ui->listView->setSpacing(0);                   //为视图设置控件间距
    m_proxyModel = new QSortFilterProxyModel(ui->listView);
    m_proxyModel->setSourceModel(m_model);
    m_proxyModel->setFilterRole(Qt::UserRole);
    m_proxyModel->setDynamicSortFilter(true);
    ui->listView->setModel(m_proxyModel);            //为委托设置模型
    ui->listView->setViewMode(QListView::ListMode); //设置Item列表显示
    ui->listView->setDragEnabled(false);            //控件不允许拖动

    isSetting = false;
    setting = new Nolabel("setting", this);
    setting->setGeometry(0, 20, 71, 71);
    QPixmap *pixmap = new QPixmap(":/images/icon/Setting_before_clicked.png");
    pixmap->scaled(setting->size(), Qt::KeepAspectRatio);
    setting->setScaledContents(true);
    setting->setPixmap(*pixmap);
    setting->setStyleSheet("QLabel {background-color: rgb(255, 255, 255);"
                           "border-left: 0.5px solid #d7d6e3;padding: 20px;}");
    connect(setting, SIGNAL(clicked(QString)), this, SLOT(push_label(QString)));

    friendManage = new Nolabel("friendManage", this);
    friendManage->setGeometry(ui->label_manage->x(), ui->label_manage->y(), 71, 71);
    pixmap = new QPixmap(":/images/icon/menu_showFriend.png");
    pixmap->scaled(friendManage->size(), Qt::KeepAspectRatio);
    friendManage->setScaledContents(true);
    friendManage->setPixmap(*pixmap);
    friendManage->setStyleSheet("QLabel {background-color: rgb(255, 255, 255);"
                           "border-right: 0.5px solid #d7d6e3;padding: 20px;}");
    connect(friendManage, SIGNAL(clicked(QString)), this, SLOT(push_label(QString)));


    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    LLKSetting = new SettingDialog(this);
    LLKSetting->setGeometry(ui->listView->x(), ui->listView->y(), ui->listView->width(), ui->listView->height());
    LLKSetting->setVisible(false);
    connect(LLKSetting, SIGNAL(isCloseSetting()), this, SLOT(SettingDialogIsClose()));
}

LLK::~LLK()
{
    delete ui;
}

void LLK::push_label(QString data)
{
    qDebug() << "is Push";
    if(data == QString::fromStdString("setting"))
    {
        qDebug() << "SETTINGDIALOG";
        if(isSetting == false)
        {
            QPixmap *pixmap = new QPixmap(":/images/icon/Setting_after_clicked.png");
            pixmap->scaled(setting->size(), Qt::KeepAspectRatio);
            setting->setScaledContents(true);
            setting->setPixmap(*pixmap);
            LLKSetting->setVisible(true);
            isSetting = true;
        }
        else {
            QPixmap *pixmap = new QPixmap(":/images/icon/Setting_before_clicked.png");
            pixmap->scaled(setting->size(), Qt::KeepAspectRatio);
            setting->setScaledContents(true);
            setting->setPixmap(*pixmap);
            LLKSetting->setVisible(false);
            isSetting = false;
        }
    }
}

void LLK::SettingDialogIsClose()
{
    LLKSetting->setVisible(false);
    isSetting = false;
    QPixmap *pixmap = new QPixmap(":/images/icon/Setting_before_clicked.png");
    pixmap->scaled(setting->size(), Qt::KeepAspectRatio);
    setting->setScaledContents(true);
    setting->setPixmap(*pixmap);
}

// 視窗真正關閉
void LLK::windowClose()
{
    // 畫面淡出的動畫
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

void LLK::windowMax()
{
    // 視窗已最大化
    if (maxWindow == true)
    {
        this->setFixedSize(944, 560);
        // 視窗置中
        QDesktopWidget *desktop = QApplication::desktop(); // =qApp->desktop();也可以
        move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
        this->setFixedSize(944, 560);
        maxWindow = false;
    }
    // 視窗沒最大化
    else
    {
        this->showMaximized();
        maxWindow = true;
    }
}

// 窗口被縮放事件
void LLK::resizeEvent(QResizeEvent *event)
{
    qDebug() << "resize";

    ui->label->setGeometry(0, 0, this->width(), 20);
    ui->label_setting->setGeometry(0, 20, 71, 71);
    ui->lineEditSearch->setGeometry(71, 20, 230, 71);
    ui->listView->setGeometry(0, 91, 301, this->height() - 91);
    ui->listView_noAction->setGeometry(0, 20, this->width(), 71);
    ui->label_Status->setGeometry(301, 20, 261, 71);
    ui->label_EMAIL->setGeometry(563, 20, this->width() - 71, 71);
    ui->label_manage->setGeometry(this->width() - 71, 20, 71, 71);
    chat->setGeometry(301, 91, this->width() - 301, this->height() - 91);
    setting->setGeometry(0, 20, 71, 71);
    friendManage->setGeometry(ui->label_manage->x(), ui->label_manage->y(), 71, 71);
    LLKSetting->setGeometry(ui->listView->x(), ui->listView->y(), ui->listView->width(), ui->listView->height());
    // 設置最小化、關閉按鈕在界面的位置
    minButton->setGeometry(this->width() - 66, 0, 21, 21);
    maxButton->setGeometry(this->width() - 45, 0, 21, 21);
    closeButton->setGeometry(this->width() - 24, 0, 21, 21);
}

void LLK::region(const QPoint &cursorGlobalPoint, bool &activeFlag)
{
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());
    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();
    activeFlag = true;
    if (tl.x() + PADDING + 2 >= x && tl.x() <= x && tl.y() + PADDING + 2 >= y && tl.y() <= y)
    {
        // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if (x >= rb.x() - PADDING - 2 && x <= rb.x() && y >= rb.y() - PADDING - 2 && y <= rb.y())
    {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if (x <= tl.x() + PADDING + 2 && x >= tl.x() && y >= rb.y() - PADDING - 2 && y <= rb.y())
    {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if (x <= rb.x() && x >= rb.x() - PADDING - 2 && y >= tl.y() && y <= tl.y() + PADDING + 2)
    {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if (x <= tl.x() + PADDING && x >= tl.x())
    {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if (x <= rb.x() && x >= rb.x() - PADDING)
    {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if (y >= tl.y() && y <= tl.y() + PADDING)
    {
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else if (y <= rb.y() && y >= rb.y() - PADDING)
    {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else
    {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
        activeFlag = false;
    }
}

// 設計 colseEvent 為最小化至托盤---------------------------------------
void LLK::init()
{
    /****托盤****/
    tray = new QSystemTrayIcon(this);                       /* 初始化托盤对象tray */
    tray->setIcon(QIcon(QPixmap(":/images/icon/LLK.png"))); /* 设定托盤icon，引號内是自定義的png圖片路徑 */
    tray->show();                                           /* 讓托盤icon顯示在系统托盤上 */
    /* 連接信號与槽，實現單擊icon恢復窗口的功能，槽是自定義的槽 */
    QObject::connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(TrayIconAction(QSystemTrayIcon::ActivationReason)));
    /****初始化托盘菜单及功能****/
    menu = new QMenu(this);    /* 初始化menu */
    reset = new QAction(this); /* 初始化恢復窗口 */
    reset->setText("Open LLK");
    QObject::connect(reset, SIGNAL(triggered()), this, SLOT(showNormal())); /* 菜单中的顯示窗口，單擊連接顯示窗口 */
    quit = new QAction(this);                                               /* 初始化退出程序 */
    quit->setText("Quit LLK");
    QObject::connect(quit, SIGNAL(triggered()), this, SLOT(windowClose())); /* 菜单中的退出程序，單擊連接退出 */

    /*
     * qApp，是Qt自带的demo中的知识点，查了一下文档，qApp是Qt中所有app的指针，关闭它就可以关闭当前的程序
     * 之所以不用this，close()，是由于软件要求关闭改为最小化到托盘，所以close()的功能已经不再是关闭窗口的功能，所以要另寻方法
     * 将定义好的菜单加入托盘的菜单模块中
     */
    tray->setContextMenu(menu);
    menu->addAction(reset);
    menu->addAction(quit);
}
/* ***重置關閉close()*** */
// 隱藏
void LLK::windowHide()
{
    // 畫面淡出的動畫
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    // 延遲執行時間，看到變化效果
    QTime reachTime = QTime::currentTime().addMSecs(500); // 500 毫秒
    while (QTime::currentTime() < reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.5sec
    }

    this->hide();
    //this->setVisible(false);
    //this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
}

/*
 * 因为实现的是关闭窗口至系统托盘，所以我们先将窗口hide()隐藏，再忽略关闭窗口功能event->ignore()即可。
 * ***托盘图标槽***
 */
void LLK::TrayIconAction(QSystemTrayIcon::ActivationReason reason)
/* 参数是Qt的保留字，表示对托盘图标的操作，该槽函数功能只实现了单击功能，可以实现其他功能比如双击、中击，具体可查文档或者Qt自带demo(关键字tray) */
{
    //if()
    switch (reason)
    {
    /* 如果对icon進行點擊，則顯示正常大小的窗口 */

    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        /*当前窗口顯示為頂級窗口，如果沒有這句的話，窗口就可能會出現在底層
        *，被别的頁面層覆蓋而看不到了.
        */
        this->activateWindow();
        this->showNormal();
        QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
        animation->setDuration(100);
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->start();
        break;
    }
}

//--------------------------------------------------------------

bool LLK::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
    {
        MSG *msg = (MSG *)message;

        if (msg->message == WM_MOUSEMOVE)
        {
            QPoint pt = cursor().pos();
            bool activeFlag;
            region(pt, activeFlag);
            if (activeFlag)
            {
                /*
                switch (dir)
                {
                case UP:
                case DOWN:
                    SetCursor(QCursor(Qt::SizeVerCursor));
                    break;
                case LEFT:
                case RIGHT:
                    SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
                    break;
                case LEFTTOP:
                case RIGHTBOTTOM:
                    SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE)));
                    break;
                case RIGHTTOP:
                case LEFTBOTTOM:
                    SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW)));
                    break;
                case NONE:
                default:
                    SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
                    return false;
                    break;
                }
                */
                return true;
            }
        }

        if (msg->message == WM_LBUTTONDOWN)
        {
            QPoint pt = cursor().pos();
            bool activeFlag;
            region(pt, activeFlag);
            if (activeFlag)
            {
                if (ReleaseCapture())
                {
                    switch (dir)
                    {
                    case UP:
                        SendMessage((HWND)this->winId(), WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, 0);
                        break;
                    case DOWN:
                        SendMessage((HWND)this->winId(), WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, 0);
                        break;
                    case LEFT:
                        SendMessage((HWND)this->winId(), WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, 0);
                        break;
                    case RIGHT:
                        SendMessage((HWND)this->winId(), WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, 0);
                        break;
                    case LEFTTOP:
                        SendMessage((HWND)this->winId(), WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, 0);
                        break;
                    case RIGHTTOP:
                        SendMessage((HWND)this->winId(), WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, 0);
                        break;
                    case LEFTBOTTOM:
                        SendMessage((HWND)this->winId(), WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, 0);
                        break;
                    case RIGHTBOTTOM:
                        SendMessage((HWND)this->winId(), WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, 0);
                        break;
                    case NONE:
                        return false;
                        break;
                    default:
                        break;
                    }
                    return true;
                }
            }
        }
    }

    return false;
}
void LLK::mousePressEvent(QMouseEvent *event)
{
    QPoint ptMouse = event->globalPos();
    m_pointRelative = ptMouse - mapToGlobal(QPoint(0, 0));
    //点住标题则拖拽
    if (m_pointRelative.ry() < 150)
    {
        if (ReleaseCapture())
            SendMessage((HWND)this->winId(), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
    }

    QMainWindow::mousePressEvent(event);
}
void LLK::mouseDoubleClickEvent(QMouseEvent *event)
{
    QPoint ptMouse = event->globalPos();
    m_pointRelative = ptMouse - mapToGlobal(QPoint(0, 0));
    //双击最大化
    if (m_pointRelative.ry() < 150)
    {
        if (this->windowState() == Qt::MaximumSize)
        {
            showNormal();
        }
        else
        {
            showMaximized();
        }
    }

    QMainWindow::mouseDoubleClickEvent(event);
}

//------------------------
void LLK::initData()
{
    totalNum = 50;
    redNum = 0;
    blueNum = 0;
    yellowNum = 0;

    m_model = new QStandardItemModel();

    for (int i = 0; i < totalNum; ++i) {
        QStandardItem *Item = new QStandardItem;

        ItemData itemData;
        itemData.avatar = QPixmap(":/images/icon/CustomerCopy.png");
        itemData.name = QString("Name %1").arg(i);
        itemData.tel = QString("TEL:1331234567%1").arg(i);
        itemData.ID = QString("HH.jj%1@gmail.com").arg(i);
        int randNum = rand()% 3;
        ItemStatus itemStatus;
        /*
        switch (randNum) {
        case 0:
            itemStatus = S_RED;
            redNum++;
            break;
        case 1:
            itemStatus = S_BLUE;
            blueNum++;
            break;
        case 2:
            itemStatus = S_YELLOW;
            yellowNum++;
            break;
        }*/

        Item->setData(itemStatus,Qt::UserRole);  // 单一存取
        Item->setData(QVariant::fromValue(itemData),Qt::UserRole+1);//整体存取

        m_model->appendRow(Item);      //追加Item


    }
}

void LLK::on_listView_clicked(const QModelIndex &index)
{
    ui->label_Status->setText(m_delegate->getGetName());
    ui->label_EMAIL->setText(m_delegate->getEMAIL());
}

void LLK::on_lineEditSearch_textChanged(const QString &arg1)
{
    QString str = ui->lineEditSearch->text();
}
