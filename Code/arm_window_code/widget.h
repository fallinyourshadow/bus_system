#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    bool failSignal;
protected:
    void timerEvent(QTimerEvent *event);
private:

    void updateNoticeAndWeather();//更新公告和天气
    void updateCurrentBusLocation();//更新公交信息
    void updateTime();//更新时间
    QString my_id;
    Ui::Widget *ui;
    QSqlDatabase *db;
    int timerId;
    //uint sec;//计时
    QStringList contentList;
};

#endif // WIDGET_H
