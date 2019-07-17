#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "mylabel.h"
#include "connecttoserver.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();
signals:
    void isCloseSetting(); // 發射視窗是否被關閉


protected:
    void resizeEvent(QResizeEvent *event); // 視窗被改變大小
private slots:
    void button_click(QString);

private:
    Ui::SettingDialog *ui;
    whitelabel *connectNetWork; // 連 server 按鈕
    whiteToRedlabel *SignOut; // 登出按鈕
    ConnectToServer *Server; // 連服務視窗

};

#endif // SETTINGDIALOG_H
