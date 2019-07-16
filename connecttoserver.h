#ifndef CONNECTTOSERVER_H
#define CONNECTTOSERVER_H

#include "mylabel.h"
#include <QComboBox>
#include <QCommandLinkButton>
#include <QDebug>
#include <QDialog>
#include <QEvent>
#include <QFont>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QTime>
#include <QToolButton>
#include <QWidget>
#include <QString>
#include <iostream>
#include <QtCore/QObject>
#include <QWebSocket>
#include <QTimer>


using namespace std;
static QString Ip = QString::fromStdString("127.0.0.1");
static int Port = 8080;
static bool isOpen = false; // 判斷視窗是否打開，避免重複按 setting 開啟
namespace Ui
{
class ConnectToServer;
}

class ConnectToServer : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectToServer(QWidget *parent = nullptr);
    ~ConnectToServer();
    bool getIsOpen();     // 回傳 isOpen
    void setIsOpen(bool); // 設定 isOpen
    bool getFlag();       // 回傳 flag

protected slots:
    void closeWindows(QString);   // 關閉視窗
    void ConnectSuccess(QString); // 連接判斷
    void restore(QString);        // 恢復原來介面

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::ConnectToServer *ui;
    Mylabel *Quit;
    Mylabel *Connect;

    //--連網----------------------------

public slots:
    void createDataRecvWS();    /*-<创建websocket连接 */

private:
    QWebSocket *dataRecvWS;     /*-<websocket类 */
    bool flag;         /*-<websocket连接状态，连接成功：true；断开：false */
    void reconnect();           /*-<周期重连函数 */
    QTimer *m_timer;            /*-<周期重连Timer */


private slots:
    void onConnected();                 /*-<socket建立成功后，触发该函数 */
    void onTextReceived(QString msg);   /*-<收到Sev端的数据时，触发该函数 */
    void onDisConnected();              /*-<socket连接断开后，触发该函数 */

};

#endif // CONNECTTOSERVER_H
