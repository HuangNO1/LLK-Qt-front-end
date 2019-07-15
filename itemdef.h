#ifndef ITEMDEF_H
#define ITEMDEF_H

#include <QMetaType>
#include <QString>
#include <QPixmap>
typedef enum{
    S_RED,
    S_BLUE,
    S_YELLOW,
} ItemStatus;

struct ItemData{
    QString name;  // 名字
    QString tel;  // 談話最新內容
    QPixmap avatar; // 頭像
    QString ID;  // email
};

Q_DECLARE_METATYPE(ItemData)

#endif // ITEMDEF_H
