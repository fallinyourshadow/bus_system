#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //连接数据库
    db = new QSqlDatabase();
    *db = QSqlDatabase::addDatabase("QMYSQL");
    db->setHostName("127.0.0.1");
    db->setUserName("root");
    db->setPassword("xhy971010");
    db->setDatabaseName("intelligent_bus_spot");//数据库名
    //db->open()?QMessageBox::information(this,"信息","成功"):QMessageBox::warning(this,"警告","连接失败");
    failSignal = !db->open();
    if(failSignal)
    {
        qDebug() << "open database failed";
    }
    my_id = "T20308";
    ui->setupUi(this);
    timerId = startTimer(1000);
}
void Widget::updateTime()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss");
    ui->l_show_time->setText(str);
}
void Widget::timerEvent(QTimerEvent *event)
{
    static uint sec = 0;
    uint len;
    static uint i = 0;
    len = contentList.size();
    if(sec%10 == 0)
    {
        contentList.clear();
        updateNoticeAndWeather();
        len = contentList.size();
    }
    if(sec%2 == 0)
    {
        updateCurrentBusLocation();
    }
    if(sec%2 == 0)//更新公告内容
    {
        //qDebug() << "sec=" << sec;
        //qDebug() << "len=" << len;
        if( len == 0)
        {
             ui->text_notice_content->setText("暂无");
        }
        else
        {
             ui->text_notice_content->setText(contentList.at(i%len));
             i++;
             if(i == len)
             {
                 i = 0;
             }
        }
    }
    updateTime();
    sec ++;
   // qDebug() << sec;
    if(sec%1800 == 0)//watch dog
    {
        sec = 0;//防止溢出
        i = 0;//更新后从新开始显示
    }
}
Widget::~Widget()
{
    delete ui;
}
