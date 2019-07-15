LLK-Qt-front-end
===

此為通訊軟件用 Qt 製作的前端

## 已完成功能

- 開始介面
- 登入介面
- 註冊介面
- 按鈕美觀與介面設計
- 連接服務介面
- 聊天視窗的聊天列表（此用 QlistView + QPaint 實現)
- 聊天視窗的訊息呈現（此用 QlistWidget + QPaint 實現)
  
> 聊天室視窗的呈現方法為另建一個 QMainWindow UI 工程，並添加 widget 排版 QlistWidget 與 textEdit（輸入區），最後在主視窗實例化此類對象並 Show 出來。

- 無窗口下自定義窗口，並添加縮放最大最小關閉功能。
- 視窗最大最小關閉的 ToolTip （滑鼠接近會提示）
- 聊天視窗按下關閉鍵縮小至托盤，左點擊（單擊或雙擊）托盤可以視窗恢復原狀，右點擊可選擇關閉結束此程序與恢復原狀
- 聊天視窗縮放時視窗內控件的比例

## 未完成部分

- 判斷是否連網
- 判斷輸入 Username 與 Password 的格式，並呈現判斷結果在視窗上
- 判斷註冊是否成功
- 聊天視窗的狀態欄，頭像，對話框，列表之間的綁定連動
- 上傳文件功能（可有可無）
- 聊天視窗 Setting 按鈕與按下按鈕後彈出的視窗
- Setting 裡的功能（Sign Out, New group, Night Mode）
- 點擊 Setting 裡的自己的頭像會彈出一視窗邊擊自己的資料
- 聊天對象的管理（e.g. Block User, View Profile ）
- 托盤點擊提示的美觀
- 好友搜尋
- 第二次登入自動登入與自動連網
- 聊天室斷網處理
- 頭像更換功能 （可有可無）

## 文件說明

### mylabel.h、mylabel.cpp

自定義的 label，具點擊事件，裡面定義了兩個類
- Mylabel - 具有點擊效果、滑鼠事件效果，適用於僅具文字的按鈕
- Nolabel - 無特效功能，適用於點擊頭像開啟文件更換頭像或是點擊任何帶有圖標的按鈕
> 註：該類發射信號帶有 QString 參數，發射內容為 `label->text()`，也就是按鈕上的文字，可作為接收信號時的按鈕類型作判斷，並給予執行相對應的程序

### register.h、register.cpp

兩文件為製作註冊頁面的參考設計，只有用到該 UI 介面的設計，可以考慮刪除這兩文件以及其 UI 文件 register.ui

### logindialog.h、logindialog.cpp、logindialog.ui

從程序開始到進入聊天介面之前的所有程序都在這裡定義

登入介面帳號密碼的程序輸入處應設於 logindialog.cpp 中第 311 行至 332 行內，添加輸入判斷，並阻止輸入格式錯誤登入成功

```C++
    if (data == QString::fromStdString("Login")) // 登入鈕被按
    {
        Server->close();               // 關掉 Server
        Server->hide();
        if (Server->getFlag() == true) // 連網成功
        {
            QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
            animation->setDuration(700);
            animation->setStartValue(1);
            animation->setEndValue(0);
            animation->start();
            // 延遲執行時間，看到變化效果
            QTime reachTime = QTime::currentTime().addMSecs(700); // 700 毫秒
            while (QTime::currentTime() < reachTime)
            {
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.7sec
            }
            Server->close();
            Server->hide();
            accept(); // 登入成功
        }
    }
```
> 註：目前有可能出現的錯誤是登入之後連接服務介面沒被關閉，所以添加了`hide()`動作

註冊介面的帳號密碼程序輸入處應設於 logindialog.cpp 中第 333 行至 387 行內，添加輸入判斷，並阻止輸入格式錯誤註冊成功

```C++
if (data == QString::fromStdString("Register")) // 註冊被按
{
    Server->close(); // 關掉 Server
    Server->hide();
    if (Server->getFlag() == true)
    {
        QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
        animation->setDuration(700);
        animation->setStartValue(1);
        animation->setEndValue(0);
        animation->start();
        QTime reachTime = QTime::currentTime().addMSecs(700); // 700 毫秒
        while (QTime::currentTime() < reachTime)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100); // 延遲 0.7sec
        }
        // 消除原視窗

```

### connecttoserver.h、connecttoserver.cpp、connecttoserver.ui

連接服務介面，目前還沒引入聊天視窗的頭文件
修改處 為 connecttoserver.h 的第 52 行

```
bool flag = 1; // 連接成功與否
```
與 connecttoserver.cpp 的 `connectSuccess()` 函數，添加連網判斷

### chatmainwindow.h、chatmainwindow.cpp

為聊天視窗裡的聊天訊息區，使用到 chatmessage.h 與 chatmessage.cpp 定義的 item
需要修改的部分為 chatmessage.cpp 裡 `keyPressEvent()`函數，添加訊息數據的加載，其中 `dealMessage()`與`dealMessageTime`分別為處理輸出訊息的函式

第 147 行到第 192 行為臨時測試編寫的選擇判斷，需修改內容，使其變成可以載入數據庫的通訊數據與新輸入的數據

處理我方輸入
```C++
if (ui->listWidget->count() % 2)
{
    if (isSending)
    {
        dealMessageTime(time);

        QNChatMessage *messageW = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
    }
    else
    {
        bool isOver = true;
        // 處理輸入文字
        for (int i = ui->listWidget->count() - 1; i > 0; i--)
        {
            QNChatMessage *messageW = (QNChatMessage *)ui->listWidget->itemWidget(ui->listWidget->item(i));
            if (messageW->text() == msg)
            {
                isOver = false;
                messageW->setTextSuccess();
            }
        }
        // 處理時間文字
        if (isOver)
        {
            dealMessageTime(time);

            QNChatMessage *messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
            messageW->setTextSuccess();
        }
    }
}
```
處理對方輸入
```C++
else
{
    if (msg != "")
    {
        dealMessageTime(time);

        QNChatMessage *messageW = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        dealMessage(messageW, item, msg, time, QNChatMessage::User_She);
    }
}
```

### chatmessage.h、chatmessage.cpp

兩文件為 chatmainmindow.h 與 chatmainwindow.cpp 的建構 Item 基礎
> 註：不宜修改該文字的字體、位置或樣式等，因為親測會嚴重影響文字輸出，但我們依然可以改變字體顏色、聊天框顏色

修改文字樣式與聊天框樣式，於 chatmessage.cpp 的 `paintEvent()`修改

### itemdef.h、itemdelegate.h、itemdelegate.cpp

以 QListView 建構列表，itemdef.h 定義 Item 裡的屬性，itemdelegate.h 與 itemdelegate.cpp 定義繪畫 Items 方式（也就是輸出 Items）

需要修改的地方為
- 添加數據於 itemdef.h
- 修改列表的點擊與滑鼠事件樣式於 itemdelegate.cpp 第 59 ~ 140 行
- 改寫 LLK.cpp 的`initData()`函數，此函數為 Items 載入方法，改成讀取數據庫的內容，代碼位於 LLK.cpp 第 456 ~ 495 行

### LLK.h、LLK.cpp、LLK.ui

這三個文件為聊天視窗的主框架









