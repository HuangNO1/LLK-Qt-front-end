#ifndef SIGNOUTDIALOG_H
#define SIGNOUTDIALOG_H

#include <QDialog>
#include "mylabel.h"

namespace Ui {
class SignOutDialog;
}

class SignOutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignOutDialog(QWidget *parent = nullptr);
    ~SignOutDialog();

private slots:
    void button_click(QString);
signals:
    void LouOut_LLK();
    void Cancel_LLK();

private:
    Ui::SignOutDialog *ui;
    Mylabel *cancel_logout; // 取消鍵
    REDlabel *confirm_logout; // 登出鍵

};

#endif // SIGNOUTDIALOG_H
