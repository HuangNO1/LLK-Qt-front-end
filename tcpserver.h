#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDialog>

namespace Ui {
class TcpServer;
}

class TcpServer : public QDialog
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = nullptr);
    ~TcpServer();

private:
    Ui::TcpServer *ui;
};

#endif // TCPSERVER_H
