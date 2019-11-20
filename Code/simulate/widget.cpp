#include "widget.h"
#include "ui_widget.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    cout = 0;
    ui->setupUi(this);
    loginDb_w = new LoginDatabase_w;
    loginDb_w->show();
    loginDb_w->exec();
    db = loginDb_w->getDb();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonbus_clicked()
{

    QSqlQuery query(*db);
    busid = ui->lineEdit->text();
    uint max_spot;
    QString str_max_spot;
    QString str;
    str_max_spot = QString("select * from immediate_bus_location where bus_id ='%1';").arg(busid);
    query.exec(str_max_spot);
    max_spot = query.numRowsAffected();
    cout++;
    if(cout>max_spot)
    {
        ui->text_display->clear();
        ui->text_display->append("到达终点");
        //qDebug() << "到达终点";
        str = QString ("update immediate_bus_location set is_arrive = 0 where bus_id = '%1';").arg(busid);
        query.exec(str);
        cout = 0;
    }
    else
    {
        str = QString ("update immediate_bus_location set is_arrive = 0 where bus_id = '%1';").arg(busid);
        query.exec(str);
        str = QString("update immediate_bus_location set is_arrive = 1 where bus_id = '%1' and sequence_position = '%2';").arg(busid).arg(cout);
        query.exec(str);
        ui->text_display->append("公交前进一站");
    }
}

void Widget::on_buttonok_clicked()
{
    busid = ui->lineEdit->text();
    QSqlQuery query(*db);
    QString str;
    QString str_bid;
    uint len,i;
    QSqlRecord rec;
    bool flag = false;
    i = 0;
    len = 0;
    str = QString("select bus_id from bus_info;");
    query.exec(str);
    rec = query.record();
    len = query.numRowsAffected();
    qDebug() << len;
    while(i<len)
    {
        query.seek(i);
       // str_bid = rec.indexOf("bus_id");
        qDebug() <<query.value("bus_id").toString();
        if(query.value("bus_id").toString() == busid)
        {
            flag = true;
        }

        i++;
    }
    if(!flag)
    {
        ui->lineEdit->clear();
        ui->text_display->clear();
        ui->text_display->append("输入错误");
    }
    if(flag)
    {
        ui->text_display->clear();
        ui->text_display->append("匹配成功");
    }

    cout = 0;
}
