#include "parentform_w.h"
#include "ui_parentform_w.h"
#include <QSqlRecord>
#include <QDebug>
#include <QItemSelectionModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlDatabase>

ParentForm_w::ParentForm_w(QSqlDatabase *DB,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParentForm_w)
{
    ui->setupUi(this);
    this->setWindowTitle("录入父表信息");
    db = DB;
//    //测试
//    QSqlQuery query(*db);

//    if(!query.exec("insert into driver_info values "
//               "('D001','张瑞','66666666666'), "
//               "('D002','徐宏云','23333333333'), "
//               "('D003','吴风江','17777777777');"))
//        QMessageBox::warning(this, "insert failed",db->lastError().text());
        //获取数据库的表名，绑定到comboBox
        QStringList tables = db->tables(QSql::Tables);
        tables.removeAt(0);
        tables.removeAt(2);
        tables.removeAt(2);
        qDebug() << tables;
        ui->comboBox->addItems(tables);

	    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

//        QSqlDatabase info = QSqlDatabase::addDatabase("QMYSQL","info");
//        info.setHostName("127.0.0.1");
//        info.setUserName("root");
//        info.setPassword("xhy971010");
//        info.setDatabaseName("information_schema");
//        if( !info.open() ) //数据库打开失败
//        {
//            QMessageBox::warning(this,"ERRO",info.lastError().text());
//            qDebug() << "错误!";
//            return;
//        }
//        else
//        {
//            QMessageBox::information(this,"SUESS","打开数据库成功");
//            qDebug() <<"suess";


//        }
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ParentForm_w::~ParentForm_w()
{
    delete ui;
}

void ParentForm_w::on_comboBox_currentTextChanged(const QString &arg1)
{
    QString table = ui->comboBox->currentText();//返回comboBox中选中的文本

       //设置模型
       model = new QSqlTableModel(this);
       model->setTable(table);

       //把model放在view
       ui->tableView->setModel(model);
       //显示model里的数据
       model->select();

       //设置model的编辑模式，手动提交修改
       model->setEditStrategy(QSqlTableModel::OnManualSubmit);
       connect(ui->Button_add,&QPushButton::clicked,
               [=]()
               {
           //添加空记录
           QSqlRecord record = model->record();//获取model的空记录
           //获取行号
           int row = model->rowCount();
           model->insertRecord(row,record);

               }
               );
       connect(ui->Button_delete,&QPushButton::clicked,
               [=]()
               {
           //获取选中的模型
           QItemSelectionModel *sModel = ui->tableView->selectionModel();
           //取出选中模型的索引
           QModelIndexList list = sModel->selectedRows();
           //删除所有选中的行
           for(int i=0;i < list.size();i++)
           {
               model->removeRow(list.at(i).row());
           }
               }
               );
       connect(ui->Button_ok,&QPushButton::clicked,
               [=]()
               {
           model->submitAll();//提交动作
               }
               );
       connect(ui->Button_cancel,&QPushButton::clicked,
               [=]()
               {
           model->revertAll();//取消所有动作
           model->submitAll();//提交动作
           model->select();
               }
               );
}

