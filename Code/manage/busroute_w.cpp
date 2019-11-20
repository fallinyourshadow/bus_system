#include "busroute_w.h"
#include "ui_busroute_w.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QDebug>

BusRoute_w::BusRoute_w(QSqlDatabase *DB,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BusRoute_w)
{
    ui->setupUi(this);
    this->setWindowTitle("录入路线");
    db = DB;

    model = new QSqlTableModel(this);
    model->setTable("immediate_bus_location");

    ui->tableView->setModel(model);

    model->select();
    model->setHeaderData(0,Qt::Horizontal,"序号");
    model->setHeaderData(1,Qt::Horizontal,"车牌号");
    model->setHeaderData(2,Qt::Horizontal,"站牌号");
    model->setHeaderData(3,Qt::Horizontal,"到站顺序");
    model->setHeaderData(4,Qt::Horizontal,"是否到站");

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    addflag = false;
    ui->texterror->append("你好");
    ui->texterror->isReadOnly();
    update_rlist();
}

BusRoute_w::~BusRoute_w()
{
    delete ui;
}

void BusRoute_w::on_buttonadd_clicked()
{
    QSqlRecord record = model->record();
    int row = model->rowCount();
    model->insertRecord(row,record);
    addflag = true;
}

void BusRoute_w::on_pushButton_clicked()
{
    model->submitAll();
    if(addflag)
    {
        QSqlQuery query;
        int row;
        int se3;
        int tid2;
        QString value_bus_id;
        int value_se;
        int value_se_last;
        QString value_ter_id;
        QString value_ter_id_last;
        QSqlRecord rec1;
        query.exec("select * from immediate_bus_location;");
        QSqlRecord rec = query.record();
        if(query.last())
        {
            rec = query.record();
            int se = rec.indexOf("sequence_position");
            value_se_last = query.value(se).toInt();
            int se2 = rec.indexOf("bus_id");
            value_bus_id = query.value(se2).toString();
            int tid = rec.indexOf("terminal_id");
            value_ter_id_last = query.value(tid).toString();
            int reid = rec.indexOf("relationship_id");
            row = query.value(reid).toInt();
        }
        query.clear();
        QString str = QString("select * from immediate_bus_location where bus_id = '%1';").arg(value_bus_id);
        query.exec(str);
        int size = query.size();
        rec1 = query.record();
        for(int i=0;i<size-1;i++)
        {
            query.seek(i);
            se3 = rec1.indexOf("sequence_position");
            value_se = query.value(se3).toInt();
            tid2 = rec.indexOf("terminal_id");
            value_ter_id = query.value(tid2).toString();
            if((value_se == value_se_last) || (value_ter_id == value_ter_id_last) )
            {
                query.clear();
                QString str1 = QString("delete from immediate_bus_location where relationship_id = %1").arg(row);
                query.exec(str1);
                ui->texterror->clear();
                ui->texterror->append("数据输入错误，重新输入");
                model->submitAll();
                addflag = false;
                return;
            }

        }
    }
    ui->texterror->clear();
    ui->texterror->append("数据输入正确");
    update_rlist();
}

void BusRoute_w::on_buttonconcel_clicked()
{
    model->revertAll();
    addflag = false;
    model->submitAll();
    ui->texterror->clear();
    update_rlist();
}

void BusRoute_w::on_buttondel_clicked()
{
    QItemSelectionModel *smodel = ui->tableView->selectionModel();
    QModelIndexList list = smodel->selectedRows();
    for(int i=0;i<list.size();i++)
    {
        model->removeRow(list.at(i).row());
    }

    update_rlist();
}

void BusRoute_w::update_rlist()
{
    Route *route_head = new Route;
    int len = model->rowCount();
    Route *temp = NULL;
    Route *opsv = NULL;
    Route *pro = NULL;
    Route *rank_head = new Route;
    Route *p1 = NULL;
    Route *prep1 = NULL;
    Route *p2 = NULL;
    Route *prep2 = NULL;
    int i=0;
    bool flag = true;
    QString strroute = "";
    QSqlQuery query(*db);
    QString strsql = "select b.bus_num from bus_info b,immediate_bus_location ibl where b.bus_id = ibl.bus_id and b.bus_id = '%1'";
    QString strsql2 = "select s.spot_name from spot_info s,immediate_bus_location ibl where s.terminal_id = ibl.terminal_id and s.terminal_id = '%1' order by spot_name";
    QSqlRecord rec;
    int se;
    QStringList route_class;
    QStringList bus_sample;
    while(i<len)
    {
        temp = new Route;
        temp->tid = model->index(i,2).data().toString();
        temp->sequence = model->index(i,3).data().toUInt();
        temp->bid = model->index(i,1).data().toString();
        query.exec(QString(strsql).arg(temp->bid));
        rec = query.record();
        se = rec.indexOf("bus_num");
        query.next();
        temp->route_num = query.value(se).toString();
        if(!route_class.contains(temp->route_num))
        {
            route_class.append(temp->route_num);
        }

        query.exec(QString(strsql2).arg(temp->tid));
        rec = query.record();
        se = rec.indexOf("spot_name");
        query.next();
        temp->spot_name = query.value(se).toString();
       // qDebug() << query.value(se).toString();
        temp->next = route_head->next;
        route_head->next = temp;
       //  qDebug() << temp->bid; //<<opsv->tid<<opsv->sequence;
        i++;
    }
    i=0;
    class_count = route_class.size();

    while (i<class_count)
    {
        opsv = route_head->next;
        while(opsv!=NULL)
        {
            if(!bus_sample.contains(opsv->bid) && opsv->route_num == route_class.at(i))
            {
               bus_sample.append(opsv->bid);
               //qDebug() <<bus_sample.at(i);
            }

            opsv = opsv->next;
        }
        i++;
    }
    route_list = new Route[class_count];


    i = 0;
    while(i<class_count)
    {
        opsv = route_head->next;
        pro = route_head;

        while (opsv!=NULL)
        {
            if(opsv->bid == bus_sample.at(i))
            {
                route_list[i].spot_count++;
                temp = opsv;
                opsv = opsv->next;
                pro->next = opsv;
                temp->next = route_list[i].next;
                route_list[i].next = temp;

            }
            else
            {
                pro = pro->next;
                 opsv = opsv->next;
            }
        }
        i++;
    }
    delete route_head;

    i=0;
    while (i<class_count)
    {
        rank_head->next = route_list[i].next;
        prep1 = rank_head->next;
        p1 = prep1->next;
        while(p1 != NULL)
        {
            flag = true;
            temp = p1;
            for(prep2=rank_head,p2=prep2->next;p2!=p1;prep2=prep2->next,p2=p2->next)
            {
                if(p2->sequence>p1->sequence)
                {
                    p1 = p1->next;
                    prep1->next = p1;
                    prep2->next = temp;
                    temp->next = p2;
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                prep1 = prep1->next;
                p1 = p1->next;
            }
        }
        route_list[i].next = rank_head->next;
        i++;
    }  
    ui->textroute->clear();
    i = 0;
    while(i<class_count)
    {
        opsv = route_list[i].next;
        strroute = QString("route: %1").arg(route_class[i]);
        while (opsv != NULL)
        {
            strroute = QString(" %1  %2" ).arg(strroute).arg(opsv->spot_name);
            opsv = opsv->next;
        }
        ui->textroute->append(strroute);
        i++;
    }

}
