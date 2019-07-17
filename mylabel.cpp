#include "mylabel.h"
#include <QCoreApplication>
#include <QLabel>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QWidget>
Mylabel::Mylabel(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    this->setText(text);
    //connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}
/*
void Mylabel::slotClicked()
{

}
*/
void Mylabel::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mylabel mousePressEvent";
    setStyleSheet("QLabel {background-color: white;"
                  " color:rgb(102, 184, 255);"
                  " border: 1px solid rgb(102, 184, 255);}");
}

void Mylabel::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "mylabel mouseMoveEvent";
    setStyleSheet("QLabel {background-color: white;"
                  " color:rgb(102, 184, 255);"
                  " border: 1px solid rgb(102, 184, 255);}");
}

void Mylabel::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "mylabel mouseReleaseEvent";
    setStyleSheet("QLabel {background-color:rgb(102, 184, 255); color:white;}");

    // 延遲執行時間，看到按壓效果
    QTime reachTime = QTime::currentTime().addMSecs(200); // 200 毫秒
    while (QTime::currentTime() < reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.2sec
    }

    emit clicked(this->text());
    qDebug() << "emit click";
}
void Mylabel::enterEvent(QEvent *)
{
    setStyleSheet("QLabel {background-color:rgb(120, 199, 255);color:white;}");
    qDebug() << "mylabel enter";
}
void Mylabel::leaveEvent(QEvent *)
{
    setStyleSheet("QLabel {background-color:rgb(102, 184, 255); color:white;}");
    qDebug() << "mylabel leave";
}

Nolabel::Nolabel(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    this->setText(text);
    //connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

void Nolabel::mousePressEvent(QMouseEvent *event)
{
    emit clicked(this->text());
}

whitelabel::whitelabel(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    this->setText(text);
    //connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

void whitelabel::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "whitelabel mousePressEvent";
    setStyleSheet("QLabel {background-color: rgb(230, 230, 230);"
                  " color:black;");
}

void whitelabel::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "whitelabel mouseMoveEvent";
    setStyleSheet("QLabel {background-color: rgb(230, 230, 230);"
                  " color:black;");
}

void whitelabel::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "whitelabel mouseReleaseEvent";
    setStyleSheet("QLabel {background-color:rgb(255, 255, 255); color:black;}");

    // 延遲執行時間，看到按壓效果
    QTime reachTime = QTime::currentTime().addMSecs(200); // 200 毫秒
    while (QTime::currentTime() < reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.2sec
    }

    emit clicked(this->text());
    qDebug() << "emit click";
}
void whitelabel::enterEvent(QEvent *)
{
    setStyleSheet("QLabel {background-color:rgb(236, 236, 236);color:black;}");
    qDebug() << "whitelabel enter";
}
void whitelabel::leaveEvent(QEvent *)
{
    setStyleSheet("QLabel {background-color:white; color:black;}");
    qDebug() << "whitelabel leave";
}

