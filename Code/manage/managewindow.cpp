#include "managewindow.h"
#include "ui_managewindow.h"
#include <QSqlDatabase>
#include "logindatabase_w.h"
#include <QDebug>
#include "noticeform_w.h"
#include "busroute_w.h"

ManageWindow::ManageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManageWindow)
{

    ui->setupUi(this);
    //this->setWindowState(Qt::WindowMaximized);
    //登陆
    loginDb_w = new LoginDatabase_w;
    loginDb_w->show();
    loginDb_w->exec();

    //qDebug() << loginDb_w->isConnectDb;
    QSqlDatabase *db =  loginDb_w->getDb();
    noticeForm_w = new NoticeForm_w(db,this);
    busRoute_w = new BusRoute_w(db,this);
    parentForm_w = new ParentForm_w(db,this);
    //noticeForm_w->show();
    //busRoute_w->show();
    //parentForm_w->show();
}
ManageWindow::~ManageWindow(){
    delete ui;
}

void ManageWindow::on_notice_a_triggered()
{
    noticeForm_w->setWindowState(Qt::WindowMaximized);
    noticeForm_w->show();
}

void ManageWindow::on_prentInfo_a_triggered()
{
    parentForm_w->setWindowState(Qt::WindowMaximized);
    parentForm_w->show();
}

void ManageWindow::on_arriveInfo_a_triggered()
{
    busRoute_w->setWindowState(Qt::WindowMaximized);
    busRoute_w->show();
}
