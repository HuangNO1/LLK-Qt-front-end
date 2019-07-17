#ifndef BLOCKUSERDIALOG_H
#define BLOCKUSERDIALOG_H

#include <QDialog>
#include "mylabel.h"

namespace Ui {
class BlockUserDialog;
}

class BlockUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BlockUserDialog(QWidget *parent = nullptr);
    ~BlockUserDialog();
private slots:
    void button_click(QString);
signals:
    void confirm_BLOCK();
    void Cancel_BLOCK();

private:
    Mylabel *cancel_Block; // 取消鍵
    REDlabel *confirm_Block; // 登出鍵
private:
    Ui::BlockUserDialog *ui;
};

#endif // BLOCKUSERDIALOG_H
