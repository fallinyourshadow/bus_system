#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QPushButton>
#include <QVariantList>
#include <QTableView>
#include <QSqlTableModel>
#include <QStringList>
#include <QSqlRecord>
//#include <QAbstractItemView>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    QPushButton * d = new QPushButton(this);
    QPushButton * d_bus_info = new QPushButton(this);
    connect_db = new QPushButton(this);
    QPushButton * insert_notice_info = new QPushButton(this);
    QPushButton * insert_driver_info = new QPushButton(this);
    QPushButton * insert_bus_info = new QPushButton(this);
    QPushButton * insert_spot_info = new QPushButton(this);
    QPushButton * insert_bus_location = new QPushButton(this);
    QPushButton * d_spot_info = new QPushButton(this);
    QPushButton * d_bus_location = new QPushButton(this);
    QPushButton * d_notice_info = new QPushButton(this);

    //设置按钮名

    connect_db->setText("连接MySQL数据库");
    d_notice_info->setText("清空mian_notice表");
    d->setText("清空driver表");
    d_bus_info->setText("清空bus_info表");
    d_spot_info->setText("清空spot_info表");
    d_bus_location->setText("清空immediate_bus_location表");
    insert_notice_info->setText("插入测试信息到main_notice表");
    insert_driver_info->setText("插入测试信息到driver表");
    insert_bus_info->setText("插入测试信息到bus_info表");
    insert_spot_info->setText("插入测试信息到spot_info表");
    insert_bus_location->setText("插入测试信息到immediate_bus_location表");
    //设置按钮位置
    d->move(150,0);
    d_bus_info->move(300,0);
    d_spot_info->move(450,0);
    d_bus_location->move(600,0);
    d_notice_info->move(850,0);
    insert_driver_info->move(0,50);
    insert_bus_info->move(0,100);
    insert_spot_info->move(0,150);
    insert_bus_location->move(0,200);
    insert_notice_info->move(0,250);
    //创建数据库对象
    db = QSqlDatabase::addDatabase("QMYSQL");
    //是否连接，默认否
    isConnectMySQL = false;
    //设置鼠标点击槽函数
    connect(connect_db,&QPushButton::pressed,[=](){
        //连接数据库
        db.setHostName("127.0.0.1");//数据库服务器IP
        db.setUserName("mikasa");//数据库用户名
        db.setPassword("123456");//密码
        db.setDatabaseName("intelligent_bus_spot");//数据库名
        //打开数据库
        isConnectMySQL = db.open();
        isConnectMySQL?
        QMessageBox::information(this,"success","连接成功")
        :
        QMessageBox::warning(this, "open failed",db.lastError().text());
        //SQL
    });
    connect(insert_notice_info,&QPushButton::pressed,[=](){
        if(isConnectMySQL)
        {
            QSqlQuery query(db);
            if(!query.exec("insert into main_notice(terminal_id,notice_content,publish_date,weather) values"
                           "('T001','暂无','2019-10-24 6:00','cloudy'),"
                           "('T002','暂无','2019-10-24 6:00','cloudy'),"
                           "('T003','暂无',default,'cloudy');"))
                QMessageBox::warning(this, "delete failed",db.lastError().text());
        }
        else
        {
            QMessageBox::warning(this, "open failed","数据库尚未连接");
        }
    });
    connect(d_notice_info,&QPushButton::pressed,[=](){
        if(isConnectMySQL)
        {
            QSqlQuery query(db);
            if(!query.exec("delete from  main_notice "
                       "where terminal_id like 'T%';"))
                QMessageBox::warning(this, "delete failed",db.lastError().text());
        }
        else
        {
            QMessageBox::warning(this, "open failed","数据库尚未连接");
        }
    });
    connect(insert_bus_location,&QPushButton::pressed,[=](){
        if(isConnectMySQL)
        {
            QSqlQuery query(db);
            if(!query.exec("insert into immediate_bus_location(bus_id,terminal_id,sequence_position) values"
                       "('B001','T003',1),('B001','T002',2),('B001','T001',3),"
                       "('B002','T003',2),('B002','T002',3),('B002','T001',1),"
                       "('B003','T003',2),('B003','T002',1);"))
                QMessageBox::warning(this, "delete failed",db.lastError().text());
        }
        else
        {
            QMessageBox::warning(this, "open failed","数据库尚未连接");
        }
    });
    connect(d_bus_location,&QPushButton::pressed,[=](){
        if(isConnectMySQL)
        {
            QSqlQuery query(db);
            if(!query.exec("delete from immediate_bus_location "
                       "where terminal_id like 'T%';"))
                QMessageBox::warning(this, "delete failed",db.lastError().text());
        }
        else
        {
            QMessageBox::warning(this, "open failed","数据库尚未连接");
        }
    });
    connect(d_bus_info,&QPushButton::pressed,[=](){
        if(isConnectMySQL)
        {
            QSqlQuery query(db);
            if(!query.exec("delete from spot_info "
                       "where terminal_id like 'T%';"))
                QMessageBox::warning(this, "delete failed",db.lastError().text());
        }
        else
        {
            QMessageBox::warning(this, "open failed","数据库尚未连接");
        }
    });
    connect(d_bus_info,&QPushButton::pressed,[=](){
        if(isConnectMySQL)
        {
            QSqlQuery query(db);
            if(!query.exec("delete from bus_info "
                       "where bus_id like 'B%';"))
                QMessageBox::warning(this, "delete failed",db.lastError().text());
        }
        else
        {
            QMessageBox::warning(this, "open failed","数据库尚未连接");
        }
    });
    connect(d,&QPushButton::pressed,[=](){
        if(isConnectMySQL)
        {
            QSqlQuery query(db);
            if(!query.exec("delete from driver_info "
                       "where driver_id like 'D%';"))
                QMessageBox::warning(this, "delete failed",db.lastError().text());
        }
        else
        {
            QMessageBox::warning(this, "open failed","数据库尚未连接");
        }
    });
    connect(insert_driver_info,&QPushButton::pressed,[=](){
        if(isConnectMySQL)
        {
            QSqlQuery query(db);
            if(!query.exec("insert into driver_info values "
                       "('D001','张瑞','66666666666'), "
                       "('D002','徐宏云','23333333333'), "
                       "('D003','吴风江','17777777777');"))
                QMessageBox::warning(this, "insert failed",db.lastError().text());
        }
        else
        {
            QMessageBox::warning(this, "open failed","数据库尚未连接");
        }
    });
    connect(insert_spot_info,&QPushButton::pressed,[=](){
        if(isConnectMySQL)
        {
            QSqlQuery query(db);
            //oracle风格
            //占位符 + 自定义名称
            query.prepare("insert into spot_info values(:terminal_id, :spot_name);");
            //设置字段内容
            QVariantList terminal_id;
            QVariantList spot_name;
            terminal_id << "T001" << "T002" << "T003";
            spot_name << "春熙路" << "天府广场" << "盐市口";
            //字段绑定
            query.bindValue(":terminal_id",terminal_id);
            query.bindValue(":spot_name",spot_name);
            //执行预处理
            if(!query.execBatch())
                QMessageBox::warning(this, "insert failed",db.lastError().text());
        }
        else
        {
            QMessageBox::warning(this, "open failed","数据库尚未连接");
        }
    });
    connect(insert_bus_info,&QPushButton::pressed,[=](){
        if(isConnectMySQL)
        {
            QSqlQuery query(db);
            //按顺序绑定windows风格
            QVariantList bus_id_list;
            bus_id_list << "B001" << "B002" << "B003";
            QVariantList driver_id_list;
            driver_id_list << "D003" << "D002" << "D001";
            QVariantList bus_num_list;
            bus_num_list << "104" << "252" << "372";
            query.prepare("insert into bus_info values(?, ?, ?)");
            query.addBindValue(bus_id_list);
            query.addBindValue(bus_num_list);
            query.addBindValue(driver_id_list);
            //执行预处理语句
            if(!query.execBatch())
                QMessageBox::warning(this, "insert failed",db.lastError().text());
        }
        else
        {
            QMessageBox::warning(this, "open failed","数据库尚未连接");
        }
    });
    QStringList tables;
    tables.append("无");
    tables.append("司机信息表");
    tables.append("公交信息表");
    tables.append("站点信息表");
    tables.append("到站表");
    tables.append("公告表");
    ui->setupUi(this);
    //tables.clear();
    //ui->comboBox->clear();
    ui->comboBox->addItems(tables);
    ui->comboBox->setCurrentText("无");

    model = new QSqlTableModel(this);//新建模型
    //model->setEditStrategy(QSqlTableModel::OnManualSubmit);

//    mode->setTable("driver_info");//选择表
//    ui->tableView->setModel(mode);//加入ui
//    mode->select();//显
//    this->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    //QSqlDatabase::database();//获得数据库指针
    //或者直接访问私有成员db
    if(isConnectMySQL)
    {
        int i = 0;
        int len;
        QStringList sqlList;
        sqlList.append("DROP TABLE ad_source;");
        sqlList.append("DROP TABLE main_notice;");
        sqlList.append("DROP TABLE immediate_bus_location;");
        sqlList.append("DROP TABLE bus_info;");
        sqlList.append("DROP TABLE driver_info;");
        sqlList.append("DROP TABLE spot_info;");
        len = sqlList.size();
        //db.transaction();
        QSqlQuery query;

//        query.exec("DROP TABLE ad_source;"
//                   "DROP TABLE main_notice;"
//                   "DROP TABLE immediate_bus_location;"
//                   "DROP TABLE bus_info;"
//                   "DROP TABLE driver_info;"
//                   "DROP TABLE spot_info;");
//        DROP TABLE ad_source;
//        DROP TABLE main_notice;
//       DROP TABLE immediate_bus_location;
//        DROP TABLE bus_info;
//        DROP TABLE driver_info;
//        DROP TABLE spot_info;
        if(QMessageBox::Yes == QMessageBox::question(this, "确认", "删除后不可撤回，是否继续？"))
        {//db.commit(); //无效
            bool isSuccess = true;
             while (i < len) {
               isSuccess =  query.exec(sqlList.at(i++)) && isSuccess;
            }
             isSuccess ? QMessageBox::information(this,"信息","全部操作完成")
                       : QMessageBox::information(this,"信息","部分操作完成");
        }
        else{
            //db.rollback(); //无效
        }
    }
    else
    {
        QMessageBox::warning(this, "open failed","数据库尚未连接");
    }
}

void Widget::on_pushButton_2_clicked()
{
    if(isConnectMySQL)
    {
        QSqlQuery query(db);
//        query.exec("source C:/Users/ASUS/Desktop/综合实训/数据库设计/sql脚本/创建表/create_table.sql");
        query.exec("create table spot_info("
                   "terminal_id char(10) primary key,"
                   "spot_name char(100) not null"
                   ")engine=InnoDB default charset=gbk;");
       query.exec("create table driver_info("
           "driver_id char(10) primary key,"
           "driver_name char(20) not null,"
           "driver_contaction char(20) not null"
       ")engine=InnoDB default charset=gbk;");
        query.exec("create table bus_info("
           "bus_id char(10) primary key,"
           "bus_num char(10) not null,"
           "driver_id char(10) not null,"
           "constraint bus_driver_fk foreign key(driver_id) references driver_info(driver_id)"
       ")engine=InnoDB default charset=gbk;");
       query.exec("create table immediate_bus_location("
       "relationship_id int unsigned auto_increment primary key,"
           "bus_id  char(10) not null,"
           "terminal_id char(10) not null,"
           "sequence_position int unsigned not null,"
           "is_arrive bit default 0 not null,"
           "constraint bus_location_fk foreign key(bus_id) references bus_info(bus_id),"
           "constraint terminal_location_fk foreign key(terminal_id) references spot_info(terminal_id)"
       ")engine=InnoDB default charset=gbk;");
       query.exec("create table main_notice("
           "notice_id int unsigned auto_increment primary key,"
           "terminal_id char(10) not null,"
           "insert_date datetime default now() not null,"
          "notice_content text not null,"
           "publish_date datetime default now() not null,"
           "weather enum('cloudy','sunny','rainy','none') default 'none',"
           "map_source mediumblob,"
           "constraint terminal_notice_fk foreign key(terminal_id) references spot_info(terminal_id)"
       ")engine=InnoDB default charset=gbk;");
       query.exec("create table ad_source("
           "ad_id char(10) primary key,"
           "ad_company char(48),"
           "contact_person_name char(32) not null,"
           "contaction_num char(20) not null,"
           "publish_date datetime,"
           "expiration_date datetime,"
           "terminal_id char(10),"
           "constraint ad_terminal_fk foreign key(terminal_id) references spot_info(terminal_id)"
       ")engine=InnoDB default charset=gbk;");
       QMessageBox::information(this,"信息","全部操作完成");
    }
    else{
        QMessageBox::warning(this, "open failed","数据库尚未连接");
    }
}

void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
//    if(arg1 != "无")
//    {
        if(isConnectMySQL)
        {
            if(arg1 == "无")
            {
                model->clear();
            }
            else if(arg1 == "司机信息表")
            {
                model->setTable("driver_info");//选择表
                QStringList header;
                header << "司机id"
                       << "姓名"
                       << "联系电话"
                       << "结束";
                int i = 0;
                while(model->setHeaderData(i,Qt::Horizontal,header.at(i)))
                    i++;
                model->setEditStrategy(QSqlTableModel::OnManualSubmit/*手动提交*/);//编辑策略
//                ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置只读
                ui->tableView->setModel(model);//加入ui
                model->select();//查询所有记录
                //qDebug() << arg1;
            }
            else if(arg1 == "公交信息表")
            {
                model->setTable("bus_info");//选择表
                QStringList header;
                header << "公交id"
                       << "公交号码"
                       << "司机id"
                       << "结束";
                int i = 0;
                while(model->setHeaderData(i,Qt::Horizontal,header.at(i)))
                    i++;
                model->setEditStrategy(QSqlTableModel::OnManualSubmit/*手动提交*/);//编辑策略
//                ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置只读
                ui->tableView->setModel(model);//加入ui
                model->select();//查询所有记录
                //qDebug() << arg1;
            }
            else if(arg1 == "到站表")
            {
                model->setTable("immediate_bus_location");//选择表
                QStringList header;
                header << "关系id"
                       << "公交id"
                       << "终端id"
                       << "到站顺位"
                       << "到站标记"
                       << "结束";
                int i = 0;
                while(model->setHeaderData(i,Qt::Horizontal,header.at(i)))
                    i++;
                model->setEditStrategy(QSqlTableModel::OnManualSubmit);//编辑策略
    //                ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置只读
                ui->tableView->setModel(model);//加入ui
                //model->setFilter(QString("%1_id like '%2'").arg(str1).arg(str2));
                model->select();//查询所有记录
                //qDebug() << arg1;
            }
            else if(arg1 == "公告表")
            {
                model->setTable("main_notice");//选择表
                QStringList header;
                header << "公告id"
                       << "终端id"
                       << "编写时间"
                       << "公告内容"
                       << "发布时间"
                       << "天气"
                       << "地图"
                       << "结束";
                int i = 0;
                while(model->setHeaderData(i,Qt::Horizontal,header.at(i)))
                    i++;
                model->setEditStrategy(QSqlTableModel::OnManualSubmit);//编辑策略
    //                ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置只读
                ui->tableView->setModel(model);//加入ui
                //model->setFilter(QString("%1_id like '%2'").arg(str1).arg(str2));
                model->select();//查询所有记录
                //qDebug() << arg1;
            }
            else
            {
                model->setTable("spot_info");//选择表
                QStringList header;
                header << "终端id"
                       << "站点名称"
                       << "结束";
                int i = 0;
                while(model->setHeaderData(i,Qt::Horizontal,header.at(i)))
                    i++;

                model->setEditStrategy(QSqlTableModel::OnManualSubmit/*手动提交*/);//编辑策略
                //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置只读
                ui->tableView->setModel(model);//加入ui
                model->select();//查询所有记录
                //qDebug() << arg1;
            }
        }
        else{
            QMessageBox::information(this,"信息","请连接数据库");
            ui->comboBox->setCurrentText("无");
        }
   // }
}

void Widget::on_pushButton_7_clicked()
{
    QString table_name = ui->comboBox->currentText();
    QString str1;
    //qDebug() << table_name;
    if(table_name != "无")
    {
        if(table_name == "司机信息表")
        {
            str1 = "driver";
        }
        else if(table_name == "站点信息表"){
            str1 = "terminal";
        }
        else if(table_name == "公交信息表"){
            str1 = "bus";
        }
        else if(table_name == "到站表"){
            str1 = "bus";
        }
        else if(table_name == "公告表")
        {
            str1 = "terminal";
        }
        QString str2;
        str2 = QString("\%%1\%").arg(ui->lineEdit->text());
        //qDebug() << str2;
        model->setFilter(QString("%1_id like '%2'").arg(str1).arg(str2));
        model->select();
    }
    else{
        QMessageBox::information(this,"信息","请选择表");
    }
}

//增加
void Widget::on_pushButton_3_clicked()
{
    //创建一个空记录
    QSqlRecord emptyRecord =  model->record();
    int row = model->rowCount();
    model->insertRecord(row, emptyRecord);
}
//选中删除
void Widget::on_pushButton_4_clicked()
{
    //获取选区的模块
    QItemSelectionModel * sModel = ui->tableView->selectionModel();
    //获取选取的索引
    QModelIndexList sList = sModel->selectedRows();
    int len = sList.size();
    int i = 0;
    while (i < len) {
        model->removeRow(sList.at(i++).row());
    }
}

//取消修改
void Widget::on_pushButton_6_clicked()
{
    model->revertAll();
    model->submitAll();
}

//提交所有修改
void Widget::on_pushButton_5_clicked()
{
    model->submitAll();
}
// bool Widget::eventFilter(QObject *watched, QEvent *event)
// {
//     if(watched == connect_db)
//     {
//         if(!isConnectMySQL)
//         {
//             return false;
//         }
//         else{
//             return true;
//         }
//     }
//     return false;
// }
