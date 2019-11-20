#include "noticeform_w.h"
#include "ui_noticeform_w.h"
#include <QSqlError>
NoticeForm_w::NoticeForm_w(QSqlDatabase *DB,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoticeForm_w)
{

    ui->setupUi(this);
    this->setWindowTitle("公告维护");
    db = DB;
    //model = new QSqlTableModel(this);
    //model->setTable("main_notice");
    //model = new QSqlRelationalTableModel(this);
    model = new QSqlTableModel(this);
    //model->setTable("main_notice");
    //设置外键关系
    //classify_by_id();

    //fRKey = QSqlRelation("spot_info","terminal_id","spot_name");

    ui->select_fliter->setEnabled(false);
    ui->delete_b->setEnabled(false);
    //ui->sname_e->setEnabled(false);
    ui->notice_e->setEnabled(false);
    ui->wather->setEnabled(false);
    ui->publish_delay_b->setEnabled(false);
    ui->publish_b->setEnabled(false);
    //ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    //ui->tableView->setModel(model);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->hide();
    //model->setFilter("main_notice.terminal_id = spot_info.terminal_id");
    //noticeClasses = new Notice;
//    connect(model,QTableView::,[=](){
//        qDebug() << "clicked";
//    });
           // strs = "选中的行:";
    isEditNew = false;
    row_count = 0;
    class_count = 0;
    pselect_Row = -1;
    currentWeather = "none";
    publish_date = "default";
    ui->select_b->click();
}

NoticeForm_w::~NoticeForm_w()
{
    delete ui;
}

void NoticeForm_w::on_select_b_clicked()
{
    tid = ui->tid_e->text();
    sName = ui->sname_e->text();
    model->clear();
   // model->setTable("main_notice");
    //lastSelect = QString("spot_name like '\%%1\%' and main_notice.terminal_id like '\%%2\%';").arg(sName).arg(tid);
    //model->setFilter(lastSelect);
//    model->relationModel(1)
    //model->select();
    //ui->tableView->setModel(model);

    model->setTable("main_notice");
//    model->setSelectionBehavior(QAbstractItemView::SelectRows);
    //model->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    model->setSelectionMode(QTableView::SingleSelection);
    model->setFilter(QString("terminal_id like '\%%1\%';").arg(tid));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit/*手动提交*/);//编辑策略

    QStringList header;
    header << "站台名"
           << "终端id"
           << "插入时间"
           << "内容"
           << "发布时间"
           << "天气"
           << "地图"
           << "结束";
    int i = 0;
    while(model->setHeaderData(i,Qt::Horizontal,header.at(i)))
        i++;
    i=0;
    model->select();

//        model->insertColumn(2);//添加一个空列
//        model->setHeaderData(2,Qt::Horizontal,"spot_name");
    //ui->tableView->horizontalHeader()->setSectionHidden(4,true);//隐藏内容字段
    ui->tableView->horizontalHeader()->setSectionHidden(6,true);//隐藏地图字段
    row_count = model->rowCount();
    //selectedRowNidList = new int[row_count];
        qDebug() <<"总记录数:" << row_count;//测试
    if(row_count == 0)
    {
        QMessageBox::information(ui->tableView,"信息","没有任何记录");
    }
    else
    {
        showAll();
        ui->select_fliter->setCurrentText("全部");
    //    model->setRelation(1,fRKey);//设置外键
    //    model->select();

        tids.clear();//使用前清空
        //int i = 0;
        while(i < model->rowCount())//获取tid
        {
           tids.append(model->index(i,1,QModelIndex()).data().toString());
           //qDebug() << tids.at(i);
                       i++;
        }
        i = 0;
    //    while (i < row_count) {//将tid加入空列
    //        model->index(i,2,QModelIndex()).data().setValue(tid.at(i));
    //        i++;
    //    }
           if(row_count != 0)
           {
               ui->select_fliter->setEnabled(true);
           }
           else
           {
               ui->select_fliter->setEnabled(false);
           }
           //ui->delete_b->setEnabled(true);
          //delete noticeClasses;
          tidList.clear();//使用前清空

          classify_by_id();
          identifyNotice();
//delete noticeClasses;
    }
    this->installEventFilter(this);
    clearSelectList();
}
Notice::Notice(){
    this->next = NULL;
    this->map = NULL;
}
Notice::Notice(Notice * n){
    this->next = NULL;
    this->map = n;
    setMember(n->id,n->row_num,n->publish_time,n->spot_name);
    deltaDate = n->deltaDate;
    notice_id = n->notice_id;
    classmate_count = n->classmate_count;
}
Notice::~Notice()
{
    //delete this;
}
void Notice::setMember(QString tid,int row,uint time,QString spot){//设置部分成员
    id = tid;
    row_num = row;
    publish_time = time;
    spot_name = spot;
    beUsing = false;
    Using = false;
    is_old = false;
}
uint Notice::now_date(){//获得当前的uint时间
    QDateTime time = QDateTime::currentDateTime();
    return time.toTime_t();
}

bool Notice::isOld(){//判断是发布过的还是未发布的
    uint nowDate = QDateTime::currentDateTime().toTime_t();
    deltaDate = this->publish_time - nowDate;
    //qDebug() << deltaDate;
    is_old = (deltaDate) > 0? false : true;
    if(is_old)
    {
        deltaDate = -deltaDate;
    }
    return is_old;
}


QSqlQuery * NoticeForm_w::getSpotNames()
{
    QSqlQuery * query = new QSqlQuery(*db);
    QString sql;
    sql = QString("select s.spot_name from spot_info s,main_notice m where m.terminal_id = s.terminal_id and m.terminal_id like '\%%1\%' order by m.notice_id;").arg(tid);//.arg(sName).arg(tid);
    query->exec(sql);
    return query;
}

void NoticeForm_w::classify_by_id()//分组存入链表数组
{
   // model->select();

    //int len = model->rowCount();//获得有多少个对象
    if(row_count == 0)
    {
        ui->select_fliter->setEnabled(false);
    }
    else{
         ui->select_fliter->setEnabled(true);
    }
    //QSqlRecord rec = model->record();
    //int len  = rec.count();
//    qDebug() << len;
    QString tid;
    uint publish_time;
    Notice *head = new Notice;
    head->next = new Notice;
    Notice *v = head->next;//定义一个操作指针
    int i = 0;
    class_count = 0;
//创建链表并初始化
    QSqlQuery * query =  getSpotNames();
    QSqlRecord rec = query->record();
    QVariant spot;
    while (i < row_count) {
        tid = tids.at(i);//tid
        if(!tidList.contains(tid))
        {
            tidList.append(tid);
            //qDebug() << tidList.at(class_count);
            class_count++;
        }
        publish_time = model->index(i,4,QModelIndex()).data().toDateTime().toTime_t();
        //qDebug() << publish_time;
        query->next();
        v->setMember(tid,i,publish_time,query->value(rec.indexOf("s.spot_name")).toString());
        //.data().setValue();
        v->notice_id = model->index(i,0,QModelIndex()).data().toUInt();
        spot.setValue(v->spot_name);
        //bool a = model->setData(model->index(i,0,QModelIndex()),spot);
        model->setData(model->index(i,0,QModelIndex()),spot);
        if(ui->sname_e->text() != "")
        {
            if(!(v->spot_name == ui->sname_e->text()))
                ui->tableView->setRowHidden(v->row_num,true);
        }

        v->isOld();
        v->next = new Notice;
        //qDebug() << "id: " << v->id << "站点名: " <<  spot << a;
        v = v->next;

        i++;
    }
    //model->select();
    v = head->next;//键操作指针置回启点
    delete query;
    //测试
//    while(head->next->next != NULL){
//        qDebug() << head->next->id;
//        head->next = head->next->next;
//    }
    //qDebug() << class_count;

//分类
    noticeClasses = new Notice[class_count];
    i = 0;
    int j = 0;
    Notice *prev = head;//记录前一个对象地址
    Notice *temp = NULL;
    while (i < class_count) {
        noticeClasses[i].id = tidList.at(i);//对象类名
        while(v->next != NULL){
            //qDebug() << v->id;
            if(tidList.at(i) == v->id)
            {
                noticeClasses[i].classmate_count = j++;//同类对象总数加1
                temp = v;//将要移动的对象加入容器
                //qDebug() << v->id;
                v = v->next;//操作指针后移
                prev->next = v;//与要移动的对象断开连接
                temp->next = noticeClasses[i].next;//将要移动的对象与所有同类连接
                noticeClasses[i].next = temp;//连接到同类的head
            }
            else
            {
                prev = prev->next;//上个对象标记指针后移一位
                v = v->next;//操作指针后移一位
            }
        }
        j = 0;
        v = head->next;//从头开始
        prev = head;
        i++;
    }
    v = NULL;
    prev = NULL;
    delete head;
    //测试
//    i = 0;
//    while(i < class_count)
//    {
//        v = noticeClasses[i].next;
//        while(v != NULL)
//        {
//            qDebug() << v->id;
//            v = v->next;
//        }
//        i++;
//    }
}
void NoticeForm_w::identifyNotice()//确定每个对象的具体属性
{
    //测试
    Notice * opsv = NULL;
    int i = 0;
//    while(i < class_count)
//    {
//        opsv = noticeClasses[i].next;
//        qDebug() << "第" << i <<"组";
//        while(opsv != NULL)
//        {
//            //opsv->beUsing = false;
//            qDebug() << opsv->spot_name << opsv->id <<" " << " is_old: "<< opsv->is_old << " Using: " << opsv->Using << " beUsing: " << opsv->beUsing;
//            opsv= opsv->next;
//        }
//        i++;
//    }
//    i = 0;
    Notice * beUsingAlterList = NULL;
    Notice * usingAlterList = NULL;
    Notice * beUsing_obj = NULL;
    Notice * using_obj = NULL;
    while(i < class_count)
    {
        opsv = noticeClasses[i].next;
        beUsingAlterList = new Notice;
        usingAlterList = new Notice;
       // beUsing_obj = NULL;//从头开始添加
        //using_obj = NULL;
        while(opsv != NULL)
        {
            //分别存入两个待比较列表
            //qDebug() << "分别存入两个待比较列表";
            if(opsv->is_old)
            {
                using_obj = new Notice(opsv);
                using_obj->next = usingAlterList->next;
                usingAlterList->next = using_obj;
                using_obj = NULL;
            }
            else
            {
                beUsing_obj = new Notice(opsv);//值拷贝，并且保存地址
                beUsing_obj->next = beUsingAlterList->next;
                beUsingAlterList->next = beUsing_obj;
                beUsing_obj = NULL;

            }
            opsv = opsv->next;
        }
        //选出将要使用的
//        if(beUsingAlterList->next != NULL)//如果有成员
//        {
            opsv = beUsingAlterList->next;
            beUsing_obj = opsv;//从第一个开始
            while(opsv != NULL)
            {
                //qDebug() << "选出将要使用的";
                if(opsv->next != NULL)
                {
                    if(beUsing_obj->deltaDate > opsv->next->deltaDate)
                        beUsing_obj = opsv->next;
                }
                else
                {
                    beUsing_obj->map->beUsing = true;
                }
                opsv= opsv->next;
            }
//        }
        //选出正在使用的
//        if(usingAlterList->next != NULL)
//        {
            opsv = usingAlterList->next;
            using_obj = opsv;//从第一个开始
            while(opsv != NULL)
            {
                //qDebug() << "选出正在使用的";
                if(opsv->next != NULL)
                {
                    if(using_obj->deltaDate > opsv->next->deltaDate)
                        using_obj = opsv->next;
                }
                else
                {
                    using_obj->map->Using = true;

                }
                opsv= opsv->next;
            }

//        }
        beUsing_obj = NULL;
        using_obj = NULL;
        delete beUsingAlterList;
        delete usingAlterList;
        i++;//处理下一组
    }
    opsv = NULL;
//   qDebug() << "\n***";
}
void NoticeForm_w::showAll(){
    int i = 0;
    while(i < row_count)
    {
        ui->tableView->setRowHidden(i,false);
        i++;
    }
}
void NoticeForm_w::on_select_fliter_currentTextChanged(const QString &arg1)
{
    int i = 0;
    Notice *opsv = NULL;
   // QString fliter = ui->select_fliter->currentText();
    //qDebug() << arg1;
    //ui->select_b->click();
    if(arg1 == "历史")
    {
        showAll();
        while(i < class_count)
        {
            opsv = noticeClasses[i].next;
            while(opsv != NULL)
            {
                if(!opsv->is_old)
                {
                    ui->tableView->setRowHidden(opsv->row_num,true);

                }
                if(opsv->Using)
                {
                    ui->tableView->setRowHidden(opsv->row_num,true);
                }
                opsv = opsv->next;
            }
            i++;
        }
    }
    else if(arg1 == "正在使用")
    {
        showAll();
        while(i < class_count)
        {
            opsv = noticeClasses[i].next;
            while(opsv != NULL)
            {
                if(!opsv->Using)
                {
                    ui->tableView->setRowHidden(opsv->row_num,true);
                }
                opsv = opsv->next;
            }
            i++;
        }
    }
    else if(arg1 == "未发布")
    {
        showAll();
        while(i < class_count)
        {
            opsv = noticeClasses[i].next;
            while(opsv != NULL)
            {
                if(opsv->is_old)
                {
                    ui->tableView->setRowHidden(opsv->row_num,true);
                }

                opsv = opsv->next;
            }
            i++;
        }
    }
    else if(arg1 == "即将发布")//即将发布
    {
        showAll();
        while(i < class_count)
        {
            opsv = noticeClasses[i].next;
            while(opsv != NULL)
            {
                if(!opsv->beUsing)
                {
                    ui->tableView->setRowHidden(opsv->row_num,true);
                }
                opsv = opsv->next;
            }
            i++;
        }
    }
    else
    {
        showAll();
    }
    clearSelectList();
    //selectedRowNidList.clear();
}

void NoticeForm_w::on_delete_b_released()
{
    int rec;
    int i = 0;
    int len;
    rec = QMessageBox::question(this,"确认删除", "删除后不可撤销，正在使用的记录删除后终端将使用前一条记录，是否继续");
    if(rec == QMessageBox::Yes)
    {
        len = selectedRowNidList.size();
        //qDebug() << len;

        QSqlQuery query(*db);
        while(i < len)
        {
           query.exec(QString("delete from main_notice where notice_id = %1").arg(selectedRowNidList.at(i)));
            i++;
        }
        row_count -= len;
        if(row_count == 0)
        {
            ui->delete_b->setEnabled(false);
            ui->select_fliter->setEnabled(false);
        }
        else
        {
            ui->delete_b->setEnabled(true);
        }
        model->submitAll();
        ui->select_b->click();
        //qDebug() << row_count;
    }
    //clearSelectList();
}

void NoticeForm_w::on_tableView_entered(const QModelIndex &index)
{
//    select_model = ui->tableView->selectionModel();
//    select_list = select_model->selectedRows();
    //qDebug() << select_list.size();
    index;
    clearSelectList();
}

void NoticeForm_w::editDisable(){
    ui->notice_e->setEnabled(false);
    ui->wather->setCurrentText("无");
    currentWeather = "none";

    ui->wather->setEnabled(false);
    publish_date = "default";
    ui->publish_delay_b->setCurrentText("发布时间");
    ui->publish_delay_b->setEnabled(false);
    ui->create_b->setText("创建新的");
    ui->publish_b->setEnabled(false);
    ui->tableView->setEnabled(true);
    ui->publish_b->setCurrentIndex(0);
}
void NoticeForm_w::editEnable()
{
    ui->notice_e->setEnabled(true);
    ui->wather->setEnabled(true);
    //ui->publish_delay_b->setEnabled(true);
    ui->tableView->setEnabled(false);
    ui->show_tid_l->setText("终端: *");
     ui->create_b->setText("取消");
    ui->notice_num_l->setText("记录编号: *");
    ui->publish_b->setCurrentIndex(0);
}
void NoticeForm_w::on_tableView_clicked(const QModelIndex &index)
{
    //qDebug() << "clicked" << index.row();
    //    if(pselect_Row != index.row())
    //    {
            int i = 0;
            pselect_Row = index.row();
            ui->tableView->selectRow(pselect_Row);

            //qDebug() << "开始";
            QString status;
            uint Nid;
            Notice *vops = NULL;
            while (i < class_count) {
                vops = noticeClasses[i].next;
                while (vops != NULL) {
                    if(model->index(pselect_Row,1,QModelIndex()).data().toString() == vops->id && model->index(pselect_Row,4,QModelIndex()).data().toDateTime().toTime_t() == vops->publish_time)
                    {
                        Nid = vops->notice_id;
                        i = class_count;
                        break;
                    }
                    vops = vops->next;
                }
                        i++;
            }
            i=0;
            if(!selectedRowNidList.contains(Nid))
            {
                selectedRowNidList.append(Nid);
                //qDebug() << "结束";
                    //qDebug() << selectedRowNidList.at(i++);
                while(i < class_count)
                {
                    vops = noticeClasses[i].next;
                    while (vops != NULL) {
                        if(pselect_Row == vops->row_num)
                        {
                            if(vops->is_old && vops->Using)
                             status = "正在使用";
                            else if(vops->is_old)
                             status = "历史记录";
                            else if(!vops->is_old && vops->beUsing)
                             status = "将被使用";
                            else if(!vops->is_old)
                                 status = "未被使用";
                            else
                                status = "未知";
                            i = class_count;
                           strs.append(status);
                            break;
                        }
                        vops = vops->next;
                    }
                    i++;
                }
            }
            i = 0;
            QString str = "";
            while(i < selectedRowNidList.size())
            {
                     str = QString("%1 /Nid:%2 状态:%3/").arg(str).arg(selectedRowNidList.at(i)).arg(strs.at(i));
                     i++;
            }
            ui->show_selected->setText(QString("选中列表:%1（单机查询清空）").arg(str));
            i = 0;
            while (i < class_count) {
                vops = noticeClasses[i].next;
                while (vops != NULL) {
                    if(model->index( pselect_Row,1,QModelIndex()).data().toString() == vops->id && model->index(pselect_Row,4,QModelIndex()).data().toDateTime().toTime_t() == vops->publish_time)
                    {
                        i = class_count;
                        break;
                    }
                    vops = vops->next;
                }
                        i++;
            }
            ui->notice_num_l->setText(QString("记录编号: %1").arg(vops->notice_id));
            ui->show_tid_l->setText(QString("终端: %1").arg(model->index(pselect_Row,1,QModelIndex()).data().toString()));
            ui->notice_e->setText(model->index(pselect_Row,3,QModelIndex()).data().toString());
            QString wather = model->index(pselect_Row,6,QModelIndex()).data().toString();
            if(wather == "rainy")
                ui->wather->setCurrentText("雨");
            else if(wather == "cloudy")
                ui->wather->setCurrentText("阴");
            else if(wather == "sunny")
                ui->wather->setCurrentText("晴");
            else
                ui->wather->setCurrentText("无");
       // }
        ui->delete_b->setEnabled(true);
}
void NoticeForm_w::clearSelectList()
{
    selectedRowNidList.clear();
    strs.clear();
    ui->show_selected->setText("选中的行:");
}
//bool NoticeForm_w::eventFilter(QObject *w, QEvent *e)
//{
//    if(e->type() == QEvent::MouseButtonPress)
//    {
//        if(w != ui->tableView)
//        {
//            qDebug() << "list clear";
//            clearSelectList();
//        }
//    }
//}
//void NoticeForm_w::on_tableView_pressed(const QModelIndex &index)
//{

//}



void NoticeForm_w::on_tableView_doubleClicked(const QModelIndex &index)
{
    ui->tableView->selectRow(index.row());
    ui->tid_e->setText(model->index(index.row(),1,QModelIndex()).data().toString());
    Notice *vops = NULL;
    int i = 0;
    while (i < class_count) {
        vops = noticeClasses[i].next;
        while (vops != NULL) {
            if(ui->tid_e->text() == vops->id)
            {

                i = class_count;
                break;
            }
            vops = vops->next;
        }
                i++;
    }
    ui->sname_e->setText(vops->spot_name);
    ui->select_b->click();
    //ui->delete_b->setEnabled(false);
}

void NoticeForm_w::on_create_b_clicked()//编辑允许
{
//    "insert into main_notice(terminal_id,notice_content,publish_date,weather) values"
//                               "('T001','暂无','2019-10-24 6:00','cloudy'),"
//                               "('T002','暂无','2019-10-24 6:00','cloudy'),"
//                               "('T003','暂无',default,'cloudy');"))
    if(ui->create_b->text() == "创建新的")
        {
        editEnable();
        ui->create_b->setText("取消");
        isEditNew = true;
    }
    else if(ui->create_b->text() == "取消")
    {
        editDisable();
        ui->create_b->setText("创建新的");
        ui->tableView->setEnabled(true);
        isEditNew = false;
    }
}


void NoticeForm_w::on_wather_currentTextChanged(const QString &arg1)
{
    if(arg1 == "无")
    {
        currentWeather = "none";
    }
    else if(arg1 == "晴")
    {
        currentWeather = "sunny";
    }
    else if(arg1 == "雨")
    {
        currentWeather = "rainy";
    }
    else if(arg1 == "阴")
        {
        currentWeather = "cloudy";
    }
}

void NoticeForm_w::on_publish_delay_b_currentTextChanged(const QString &arg1)
{
    if(arg1 != "发布时间" && ui->notice_e->toPlainText() != "" &&isEditNew)
    {
        ui->publish_b->setEnabled(true);
        if(arg1 == "现在")
        {
            publish_date = "default";
        }
        else if(arg1 == "自定义")
        {
            //CustomPublishDate_w * custom_date = new CustomPublishDate_w(&publish_date,this);
            CustomPublishDate_w custom_date(&publish_date,this);
            //qDebug() << "custom";
            custom_date.show();
            custom_date.exec();
            if(publish_date != "default")
            {
                //qDebug() << "发布时间为" <<publish_date;
            }
            else {
                publish_date = "default";
                ui->publish_delay_b->setCurrentText("发布时间");
            }
        }
    }
    else
    {
        ui->publish_b->setEnabled(false);
       //ui->publish_delay_b->setEnabled(false);
    }
}

void NoticeForm_w::on_notice_e_textChanged()
{
    if(ui->notice_e->toPlainText() != "" && isEditNew)
    {
        //ui->publish_b->setEnabled(true);
        ui->publish_delay_b->setEnabled(true);

    }
    else
    {
        ui->publish_b->setEnabled(false);
        ui->publish_delay_b->setEnabled(false);
    }
}
bool NoticeForm_w::insertOrUpdate(QString id)
{
    QSqlQuery query(*db);
    Notice *vops = NULL;
    int i = 0;
    //int j = 0;
    QDateTime datetime;
    bool isSameDayNotice = false;
    QString time;
    QString str = "insert into main_notice(terminal_id,notice_content,publish_date,weather) values('%1','%2',%3,'%4');";
    QString sqlUpdate = "update main_notice set notice_content = '%1',weather = '%2' where terminal_id = '%3' and publish_date = %4;";
    QString content = ui->notice_e->toPlainText();
    //qDebug() << "公告内容" << content;
    QString publishDate = publish_date;
    QString weather = currentWeather;
     bool isSuccess = true;
    while (i < class_count)//判断是更新还是加入
    {
        vops = noticeClasses[i].next;

        while (vops != NULL)
        {
            time = datetime.fromTime_t(vops->publish_time).toString("yyyy-MM-dd hh:mm");
            time = QString("%1%2%3").arg('\'').arg(time).arg('\'');
            //bool a = publishDate == time;
            //qDebug() << publishDate << "==" <<  time << a;
            if(id == vops->id && publishDate == time)
            {
                isSameDayNotice = true;
                i = class_count;
                break;
            }
            vops = vops->next;
        }
        i++;
    }
    if(!isSameDayNotice)
    {
        isSuccess = isSuccess && query.exec(QString(str.arg(id).arg(content).arg(publishDate).arg(weather)));
        isSameDayNotice = false;
        //qDebug() << QString(str.arg(id).arg(content).arg(publishDate).arg(weather));
    }
    else
    {
        isSuccess = isSuccess && query.exec(QString(sqlUpdate.arg(content).arg(weather).arg(id).arg(publishDate)));
       // qDebug() << QString(sqlUpdate.arg(content).arg(weather).arg(id).arg(publishDate));
    }
    return isSuccess;
}

void NoticeForm_w::on_publish_b_currentTextChanged(const QString &arg1)
{
//    QSqlQuery query(*db);
    QString id;

//    QString content = ui->notice_e->toPlainText();
//    //qDebug() << "公告内容" << content;
//    QString publishDate = publish_date;
//    bool isSameDayNotice = false;
//    QString weather = currentWeather;

//    QString str = "insert into main_notice(terminal_id,notice_content,publish_date,weather) values('%1','%2',%3,'%4');";

//    QString sqlUpdate = "update main_notice set notice_content = '%1',weather = '%2' where terminal_id = '%3' and publish_date = %4;";

    bool isSuccess = false;
    Notice *vops = NULL;
    int i = 0;
    int j = 0;
    int len;
    QStringList tid_list;
//    QDateTime datetime;
//    QString time;

    if(arg1 == "所有已存在记录的终端")
    {
        if(class_count == 0)
        {
            QMessageBox::information(this,"信息","什么都没有发生");
        }
        else
        {

            while(i < class_count)
            {
                j = 0;
                id = noticeClasses[i].id;
                isSuccess = insertOrUpdate(id);
//                while (j < class_count)//判断是更新还是加入
//                {
//                    vops = noticeClasses[i].next;

//                    while (vops != NULL)
//                    {
//                        time = datetime.fromTime_t(vops->publish_time).toString("yyyy-MM-dd hh:mm");
//                        time = QString("%1%2%3").arg('\'').arg(time).arg('\'');
//                        bool a = publishDate == time;
//                        qDebug() << publishDate << "==" <<  time << a;
//                        if(id == vops->id && publishDate == time)
//                        {
//                            isSameDayNotice = true;
//                            j = class_count;
//                            break;
//                        }
//                        vops = vops->next;
//                    }
//                    j++;
//                }
//                if(!isSameDayNotice)
//                {
//                    isSuccess = isSuccess && query.exec(QString(str.arg(id).arg(content).arg(publishDate).arg(weather)));
//                    isSameDayNotice = false;
//                    qDebug() << QString(str.arg(id).arg(content).arg(publishDate).arg(weather));
//                }
//                else
//                {
//                    isSuccess = isSuccess && query.exec(QString(sqlUpdate.arg(content).arg(weather).arg(id).arg(publishDate)));
//                    qDebug() << QString(sqlUpdate.arg(content).arg(weather).arg(id).arg(publishDate));
//                }
                i++;
            }
            isSuccess ? QMessageBox::information(this,"信息","全部成功") : QMessageBox::warning(this,"可能失败了",db->lastError().text());
            editDisable();
        }
    }
    else if(arg1 == "选中列表中的终端")
    {
        len = selectedRowNidList.size();
        //qDebug() << len;
        if(len == 0)
        {
            QMessageBox::information(this,"信息","什么都没有发生");
        }
        else
        {
            while(j < len)
            {
                i = 0;
                while (i < class_count)
                {
                    vops = noticeClasses[i].next;
                    while (vops != NULL)
                    {
                        if(selectedRowNidList.at(j) == vops->notice_id)
                        {
                            id = vops->id;
                            if(!tid_list.contains(id))
                            {
                                tid_list.append(id);
                                isSuccess = insertOrUpdate(id);
                                //isSuccess = isSuccess && query.exec(QString(str.arg(id).arg(content).arg(publishDate).arg(weather)));
                                 //qDebug() << QString(str.arg(id).arg(content).arg(publishDate).arg(weather));
                            }
                            i = class_count;
                            break;
                        }
                        vops = vops->next;
                    }
                    i++;
                }
                j++;
            }
            isSuccess ? QMessageBox::information(this,"信息","全部成功") : QMessageBox::warning(this,"可能失败了",db->lastError().text());
            editDisable();
        }
    }
    else if(arg1 == "输入终端id")
    {
        EditTid_w edit_tid_w(&tid_list,this);
        //EditTid_w edit_tid_w = new EditTid_w(&tid_list,this);
        edit_tid_w.show();
        edit_tid_w.exec();
        if(!tid_list.isEmpty())
        {
            len = tid_list.size();
            while(i < len)
            {
                id = tid_list.at(i);
                isSuccess = insertOrUpdate(id);
                //isSuccess = isSuccess && query.exec(QString(str.arg(id).arg(content).arg(publishDate).arg(weather)));
                 //qDebug() << QString(str.arg(id).arg(content).arg(publishDate).arg(weather));
                i++;
            }
            isSuccess ? QMessageBox::information(this,"信息","全部成功") : QMessageBox::warning(this,"可能失败了",db->lastError().text());
            editDisable();
        }
        else
        {
            QMessageBox::information(this,"信息","什么都没有发生");
        }
    }
    ui->select_b->click();
}
