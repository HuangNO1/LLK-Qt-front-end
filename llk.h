#ifndef LLK_H
#define LLK_H

#include "chatmessage.h"
#include "mylabel.h"
#include "chatmainwindow.h"
#include "settingdialog.h"
#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QDesktopWidget>
#include <QDialog>
#include <QFile>
#include <QGraphicsOpacityEffect>
#include <QGroupBox>
#include <QLCDNumber>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QModelIndex>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QResizeEvent>
#include <QScrollBar>
#include <QSlider>
#include <QSpinBox>
#include <QString>
#include <QSystemTrayIcon>
#include <QTextEdit>
#include <QTextStream>
#include <QTimer>
#include <QToolButton>
#include <QVBoxLayout>
#include <QtCore>
#include <QtGui>
#include <QAbstractNativeEventFilter>
#include <QCursor>
#include <windows.h>
#include <QButtonGroup>
#include <QObjectUserData>
#include <QSortFilterProxyModel>
#include "itemdelegate.h"
#include "signoutdialog.h"
#include "blockuserdialog.h"
#define PADDING 5

// 判斷滑鼠的在視窗的位置
enum Direction
{
    UP = 0,
    DOWN = 1,
    LEFT,
    RIGHT,
    LEFTTOP,
    LEFTBOTTOM,
    RIGHTBOTTOM,
    RIGHTTOP,
    NONE
};
static enum Direction dir;

namespace Ui
{
class LLK;
}

class LLK : public QMainWindow, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    explicit LLK(QWidget *parent = nullptr);
    ~LLK();
    // 紀錄訊息
    //void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    //void dealMessageTime(QString curMsgTime);

protected:
    void resizeEvent(QResizeEvent *event); // 視窗被改變大小
    // 拖拽窗口

    //void keyPressEvent(QKeyEvent *event); // 按數字鍵盤和鍵盤的 Enter鍵事件

private:
    Ui::LLK *ui;
    bool maxWindow;                         // 判斷視窗是否以最大化
    QDesktopWidget *desktop;                // 使視窗置中
    bool isDrag;                            // 移動窗口的標記
    QPoint mouseStartPoint;                 // 滑鼠初始位置
    QPoint windowTopLeftPoint;              // 窗口初始位置
    void region(const QPoint &cursorPoint); // 縮放事件
    //QLabel *title;                         // 邊框

    // 無窗口下的拖動與縮放
private:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    //bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void region(const QPoint &cursorPoint, bool &activeFlag);
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);
    QPoint m_pointRelative;

    // 構建最小化、最大化、關閉按鈕
    QToolButton *minButton;
    QToolButton *closeButton;
    QToolButton *maxButton;

    // 聊天框
    CHATMainWindow *chat;

    Nolabel *setting;     // setting 按鈕
    FRIENDlabel *friendManage; // 好友管理按鈕
    bool isSetting;        // 判斷 setting 是否被按下
    SettingDialog *LLKSetting; // 設定視窗
    SignOutDialog *logout; // 登出視窗選擇窗
    QLabel *gray; // 登出視窗出現後改變聊天視窗
    whitelabel *BlockUser; // 刪除好友
    bool isMANAGE;  // 判斷刪除好友鍵
    BlockUserDialog *BLOCK; // 刪除好友確認視窗


private slots:
    void windowClose(); // 視窗關閉
    void windowMax();   // 視窗最大化按鈕兩段設計
    void windowHide();  // 視窗隱藏

    void push_label(QString); // 按下 label 接收訊號


    void SettingDialogIsClose(); // 設定鍵被關閉

    void LogOut_FROM_LLK(); // 關閉主程序

    void Cancel_LogOut_LLK(); // 取消登出並背景顏色恢復

    void Block_user();
    void Cancel_Block_user();

    // 設計 colseEvent 為最小化至托盤----------------------------------------
    void on_listView_clicked(const QModelIndex &index);

    void on_lineEditSearch_textChanged(const QString &arg1);

public:
    void init(); //初始化函数

    QSystemTrayIcon *tray; //托盤 icon
    QMenu *menu;           //托盤菜單
    QAction *reset;        //菜單實現功能：恢復窗口
    QAction *quit;         //菜單實現功能：退出程序

    /*
protected:
    void closeEvent();//由于要关闭窗口变为隐藏至托盘图标，所以要重写close事件
*/
    // signals:

public slots:
    void TrayIconAction(QSystemTrayIcon::ActivationReason reason); //对托盘图标操作的槽：本代码实现单机图标恢复窗口功能
    //-------------------------------


private:
    QButtonGroup *m_filterButtonGroup;
    ItemDelegate *m_delegate;                 //委托
    QSortFilterProxyModel* m_proxyModel;
    QStandardItemModel *m_model;
    QString totalNum;
    int redNum;
    int blueNum;
    int yellowNum;

    void initData();
    void updateButtonNum();
};

#endif // LLK_H
