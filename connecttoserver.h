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
#include <Qstring>
#include <iostream>
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
    bool flag = 1; // 連接成功與否
};

#endif // CONNECTTOSERVER_H
