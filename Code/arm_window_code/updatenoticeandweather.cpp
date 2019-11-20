#include "widget.h"
#include "ui_widget.h"
#include <QSqlQuery>
#include "updatenoticeandweather.h"
#include <QDateTime>
#include <QSqlRecord>
#include <QDebug>
Notice::Notice()
{
    content = " ";
    ptime = 0;
    weather = " ";
    delta_time = -1;
}

void Notice::set_members(uint ptime_1,QString weather_1,QString content_1)
{
    ptime = ptime_1;
    weather = weather_1;
    content = content_1;
}
int Notice::calculate_deltatime()
{
    QDateTime nowtime = QDateTime::currentDateTime();
    uint time = nowtime.toTime_t();
    delta_time = time - ptime;
    return delta_time;
}

void Widget::updateNoticeAndWeather()
{



    QDateTime time;
    QString weather;
    QString content;
    QSqlQuery query(*db);
    QString rec_str;
    QSqlRecord rec;
    int i = 0;
    int row;
    query.exec(QString("select weather,notice_content,publish_date from main_notice where terminal_id = '%1';").arg(my_id));

    rec = query.record();
    row = query.numRowsAffected();
    qDebug() << "查询结果行数:" << row;

    Notice notice[row];

    while(query.next())
    {


        QDateTime nowtime_1 = QDateTime::currentDateTime();
        weather = query.value(0).toString();
        qDebug() << weather;

        content = query.value(1).toString();
        qDebug() << content;
        time = query.value(2).toDateTime();

        int delta = nowtime_1.toTime_t() - time.toTime_t();

       qDebug() << "delta=" << delta;

        //qDebug() << time.toTime_t();
//        contentList.append(weather);
//        contentList.append(content);
        //qDebug() << contentList;

        if(delta>0 || delta == 0)
        {
        notice[i].set_members(time.toTime_t(),weather,content);

        notice[i].calculate_deltatime();

        //qDebug() << notice[i].weather <<  notice[i].delta_time;
        i++;
        }
        //contentList.clear();
    }
    row = i;
    i=0;
    Notice min;
    min = notice[0];
    while(i<row-1)
    {
       if(min.delta_time>notice[i+1].delta_time)
       {
           min = notice[i+1];
       }
       i++;
    }
    if(min.weather == "sunny")
    {
        ui->l_show_weather->setText("晴");
    }
    else if(min.weather == "cloudy" )
    {
       ui->l_show_weather->setText("多云");
    }
    else if(min.weather == "rainy")
    {
        ui->l_show_weather->setText("雨");
    }
    else
    {
        ui->l_show_weather->setText("未知");
    }
    qDebug() << "min.content.length()=" << min.content.length();

//    QString arry[ min.content.length()] = min.content;

//    qDebug() << arry[2];

    std::string str = min.content.toStdString();
    const char* ch = str.c_str();
    qDebug() << "内容：" << ch;

    int position = 0;

    do
    {
        if(min.content.length()>30)
        {
            QString Temp_str = min.content.left(30);
            contentList.append(QString("    %1").arg(Temp_str));
            min.content = min.content.remove(position,30);
            //position += 20;
           // qDebug() << "大于50";

        }
//        else
//        {
//            contentList.append(min.content);
//            qDebug() << "2";
//        }

    }while(min.content.length()>30);

    contentList.append(QString("    %1").arg(min.content));
   // qDebug() << "2";

    qDebug() <<"contenlist.size=" << contentList.size();
}
