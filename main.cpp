#include "llk.h"
#include "logindialog.h"
#include "mylabel.h"
#include "register.h"
#include <QApplication>
#include <QtGui>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LLK w;
    loginDialog dlg;
    if (dlg.exec() == QDialog::Accepted)
    {
        w.show();
        a.installNativeEventFilter(&w);
        return a.exec();
    }
    else
    {
        return 0;
    }
}
