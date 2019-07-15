#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "connecttoserver.h"
#include "mylabel.h"
#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QGraphicsOpacityEffect>
#include <QLCDNumber>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QPoint>
#include <QPushButton>
#include <QSlider>
#include <QString>
#include <QTimer>
#include <QToolButton>
#include <QVBoxLayout>
#include <QtGui>

class scrollLabel : public QLabel
{
    Q_OBJECT
public:
    scrollLabel(const QPixmap *pixmap, QWidget *parent = 0);
    ~scrollLabel() {}

protected:
    void enterEvent(QEvent *event); // 滑鼠移入
    void leaveEvent(QEvent *event); // 滑鼠移出
    void timerEvent(QTimerEvent *event);
    void mousePressEvent(QMouseEvent *event);   // 滑鼠點擊
    void mouseMoveEvent(QMouseEvent *event);    // 滑鼠點擊後移動
    void mouseReleaseEvent(QMouseEvent *event); // 滑鼠釋放

signals:
    void clicked(QString);

private:
    // 紀錄定時器 id
    int m_enterId;
    int m_leaveId;
    //保存label顯示的圖片
    QPixmap m_pixmap;
    //紀錄旋轉角度
    float m_rotateAngle;
    const float FixedAngle = 2.5f;
    const int Time = 10;
};

namespace Ui
{
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();

public:
    QToolButton *minButton;
    QToolButton *closeButton;
    //------------------ start
    Mylabel *my_label;
    //------------------ login
    Mylabel *login_label;
    Mylabel *register_label;
    scrollLabel *setting_label;
    //------------------ register
    Mylabel *confirm_regiter;
    Mylabel *cancel_register;
    QLabel *usrname_r_label;
    QLabel *pwdname_r_label;
    QLabel *con_pwdname_r_label;
    QLabel *emailname_r_label;
    QLabel *invaild_r_label;
    Nolabel *Avatar_label; // 頭像
    QLineEdit *usrname_r_lineedit;
    QLineEdit *pwdname_r_lineedit;
    QLineEdit *con_pwdname_r_lineedit;
    QLineEdit *emailname_r_lineedit;
    QLabel *register_success_icon;
    QLabel *register_success_text;

protected:
    // 拖拽窗口
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::loginDialog *ui;
    ConnectToServer *Server;
    bool isDrag;               // 移動窗口的標記
    QPoint mouseStartPoint;    // 滑鼠初始位置
    QPoint windowTopLeftPoint; // 窗口初始位置
    bool registerSuccess;      // 判斷是否註冊成功

private slots:
    void button_click(QString);
    void windowClose(); // 視窗關閉
};

#endif // LOGINDIALOG_H
