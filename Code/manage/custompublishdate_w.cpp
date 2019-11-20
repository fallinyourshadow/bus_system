#include "custompublishdate_w.h"
#include "ui_custompublishdate_w.h"
#include <QMessageBox>
CustomPublishDate_w::CustomPublishDate_w(QString *publishDate,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomPublishDate_w)
{
    ui->setupUi(this);
    publish_date = publishDate;
    ui->year_e->setFocus();
    ui->year_e->setText("20");
    this->setWindowTitle("自定义发布时间");
}

CustomPublishDate_w::~CustomPublishDate_w()
{
    delete ui;
}
void CustomPublishDate_w::on_year_e_textEdited(const QString &arg1)
{
    if(arg1.size() == 4)
    {
        ui->mon_e->setFocus();
    }
}

void CustomPublishDate_w::on_mon_e_textEdited(const QString &arg1)
{
    if(arg1.size() == 2)
    {
        ui->day_e->setFocus();
    }
}

void CustomPublishDate_w::on_day_e_textEdited(const QString &arg1)
{
    if(arg1.size() == 2)
    {
        ui->ok_b->setFocus();
    }
}

void CustomPublishDate_w::on_ok_b_clicked()
{
    QString pt;
    int year;
    int mon;
    int day;

    year = ui->year_e->text().toInt();
    mon = ui->mon_e->text().toInt();
    day = ui->day_e->text().toInt();
    pt = QString("'%1-%2-%3 00:00'").arg(year).arg(mon).arg(day);
    int rec;
    rec = QMessageBox::question(this,"确认",QString("发布时间为: %1").arg(pt));
    if(rec == QMessageBox::Yes)
    {
        *publish_date = pt;
        this->close();
    }
}

void CustomPublishDate_w::on_pushButton_2_clicked()
{
    this->close();
}


