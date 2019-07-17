#include "blockuserdialog.h"
#include "ui_blockuserdialog.h"

BlockUserDialog::BlockUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlockUserDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    this->setStyleSheet("QWidget { border-top-left-radius:10px;border-top-right-radius:10px;"
                        "border-bottom-right-radius:10px;border-bottom-left-radius:10px;}");
    QFont ft;
    ft.setPointSize(15);
    ft.setFamily("Corbel");

    // 設定控件
    cancel_Block = new Mylabel("Cancel", this);
    cancel_Block->setGeometry(QRect(ui->label_Cancel->x(), ui->label_Cancel->y(),
                                     ui->label_Cancel->width(), ui->label_Cancel->height()));
    cancel_Block->setAlignment(Qt::AlignCenter); // 文字靠左
    cancel_Block->setStyleSheet("QLabel { background-color : rgb(102, 184, 255); color : white;padding:15px;}");
    cancel_Block->setFont(ft);
    connect(cancel_Block, SIGNAL(clicked(QString)), this, SLOT(button_click(QString)));

    confirm_Block = new REDlabel("Block", this);
    confirm_Block->setGeometry(QRect(ui->Block->x(), ui->Block->y(),
                                      ui->Block->width(), ui->Block->height()));
    confirm_Block->setAlignment(Qt::AlignCenter); // 文字靠左
    confirm_Block->setStyleSheet("QLabel { background-color : red; color : white;padding:15px;}");
    confirm_Block->setFont(ft);
    connect(confirm_Block, SIGNAL(clicked(QString)), this, SLOT(button_click(QString)));
}

BlockUserDialog::~BlockUserDialog()
{
    delete ui;
}
void BlockUserDialog::button_click(QString data)
{
    if (data == QString::fromStdString("Cancel")) // 取消 鈕被按
    {
        this->setVisible(false);
        emit confirm_BLOCK();
    }
    if(data == QString::fromStdString("Block")) // LogOut 鈕被按
    {
        this->setVisible(false);
        emit Cancel_BLOCK();
    }

}
