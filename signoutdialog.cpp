#include "signoutdialog.h"
#include "ui_signoutdialog.h"

SignOutDialog::SignOutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignOutDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    this->setStyleSheet("QWidget { border-top-left-radius:10px;border-top-right-radius:10px;"
                        "border-bottom-right-radius:10px;border-bottom-left-radius:10px;}");
    QFont ft;
    ft.setPointSize(15);
    ft.setFamily("Corbel");

    // 設定控件
    cancel_logout = new Mylabel("Cancel", this);
    cancel_logout->setGeometry(QRect(ui->label_Cancel->x(), ui->label_Cancel->y(),
                                     ui->label_Cancel->width(), ui->label_Cancel->height()));
    cancel_logout->setAlignment(Qt::AlignCenter); // 文字靠左
    cancel_logout->setStyleSheet("QLabel { background-color : rgb(102, 184, 255); color : white;padding:15px;}");
    cancel_logout->setFont(ft);
    connect(cancel_logout, SIGNAL(clicked(QString)), this, SLOT(button_click(QString)));

    confirm_logout = new REDlabel("Log Out", this);
    confirm_logout->setGeometry(QRect(ui->LogOut->x(), ui->LogOut->y(),
                                      ui->LogOut->width(), ui->LogOut->height()));
    confirm_logout->setAlignment(Qt::AlignCenter); // 文字靠左
    confirm_logout->setStyleSheet("QLabel { background-color : red; color : white;padding:15px;}");
    confirm_logout->setFont(ft);
    connect(confirm_logout, SIGNAL(clicked(QString)), this, SLOT(button_click(QString)));
}

SignOutDialog::~SignOutDialog()
{
    delete ui;
}
void SignOutDialog::button_click(QString data)
{
    if (data == QString::fromStdString("Cancel")) // 取消 鈕被按
    {
        this->setVisible(false);
    }
    if(data == QString::fromStdString("Log Out")) // LogOut 鈕被按
    {
        this->close();
        emit LouOut_LLK();
    }

}
