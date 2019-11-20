#include "logindatabase_w.h"
#include "ui_logindatabase_w.h"
#include <QRegExp>
#include <QDebug>
LoginDatabase_w::LoginDatabase_w(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDatabase_w)
{
    isConnectDb = false;
    ui->setupUi(this);
    ui->ip1_e->setFocus();
    QRegExp regExp("[0-9]{1,3}");
    ui->ip1_e->setValidator(new QRegExpValidator(regExp,this));
    ui->ip2_e->setValidator(new QRegExpValidator(regExp,this));
    ui->ip3_e->setValidator(new QRegExpValidator(regExp,this));
    ui->ip4_e->setValidator(new QRegExpValidator(regExp,this));
    ui->ip1_e->setText("127");
    ui->ip2_e->setText("0");
    ui->ip3_e->setText("0");
    ui->ip4_e->setText("1");
    ui->user_name_e->setText("mikasa");
    ui->passwd_e->setText("123456");
    QWidget::setTabOrder(ui->ip1_e,ui->ip2_e);
    QWidget::setTabOrder(ui->ip2_e,ui->ip3_e);
    QWidget::setTabOrder(ui->ip3_e,ui->ip4_e);
    QWidget::setTabOrder(ui->ip4_e,ui->user_name_e);
    QWidget::setTabOrder(ui->user_name_e,ui->passwd_e);
    ui->ok_b->setEnabled(true);
    this->setWindowTitle("连接数据库");
//    connect(ui->cancel_b,&QPushButton::clicked,this,&LoginDatabase_w::sendSignal);
    //this->installEventFilter(this);
    //isConnectDb = false;
}

LoginDatabase_w::~LoginDatabase_w()
{
    delete ui;
}



void LoginDatabase_w::on_ip1_e_textEdited(const QString &arg1)
{
    if(arg1.size() == 3){
        ui->ip2_e->setFocus();
    }
    okEnable();
}

void LoginDatabase_w::on_ip2_e_textEdited(const QString &arg1)
{
    if(arg1.size() == 3){
        ui->ip3_e->setFocus();
    }
    okEnable();
}

void LoginDatabase_w::on_ip3_e_textEdited(const QString &arg1)
{
    if(arg1.size() == 3){
        ui->ip4_e->setFocus();
    }
    okEnable();
}

void LoginDatabase_w::on_ip4_e_textEdited(const QString &arg1)
{
    if(arg1.size() == 3){
        ui->user_name_e->setFocus();
    }
    okEnable();
}
void LoginDatabase_w::okEnable(){
    if(ui->ip1_e->text() != ""&&
    ui->ip2_e->text() != ""&&
    ui->ip3_e->text() != ""&&
    ui->ip4_e->text() != ""&&
    ui->user_name_e->text() != ""&&
    ui->passwd_e->text() != "")
        ui->ok_b->setEnabled(true);
    else {
        ui->ok_b->setEnabled(false);
    }
}



void LoginDatabase_w::on_user_name_e_textEdited(const QString &)
{
    okEnable();
}

void LoginDatabase_w::on_passwd_e_textEdited(const QString &)
{
    okEnable();
}



void LoginDatabase_w::on_ok_b_released()
{

    QString userName = ui->user_name_e->text();
    QString passwd = ui->passwd_e->text();
    QString ip;

    ip = QString("%1.%2.%3.%4")
            .arg(ui->ip1_e->text())
            .arg(ui->ip2_e->text())
            .arg(ui->ip3_e->text())
            .arg(ui->ip4_e->text());
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(ip);//数据库服务器IP
    db.setUserName(userName);//数据库用户名
    db.setPassword(passwd);//密码
    db.setDatabaseName("intelligent_bus_spot");//数据库名
    //打开数据库
    qDebug() << userName << passwd << ip;
    isConnectDb = db.open();
    if(isConnectDb)
    {
        this->hide();
        this->close();
    }
    else
    {
        QMessageBox::warning(this,"警告","连接失败");
        ui->ip1_e->setText("");
        ui->ip2_e->setText("");
        ui->ip3_e->setText("");
        ui->ip4_e->setText("");
        ui->user_name_e->setText("");
        ui->passwd_e->setText("");
    }
}

void LoginDatabase_w::on_cancel_b_released()
{

    this->close();
}
//void LoginDatabase_w::sendSignal(){
//    emit exitM();
//}
QSqlDatabase * LoginDatabase_w::getDb()
{
    return &db;
}
