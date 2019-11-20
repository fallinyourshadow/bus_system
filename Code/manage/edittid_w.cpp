#include "edittid_w.h"
#include "ui_edittid_w.h"

EditTid_w::EditTid_w(QStringList * tidList,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTid_w)
{
    tid_list = tidList;
    ui->setupUi(this);
}

EditTid_w::~EditTid_w()
{
    delete ui;
}



void EditTid_w::on_cancel_b_clicked()
{
    this->close();
}

void EditTid_w::on_ok_b_clicked()
{
    QString tids = ui->editTid_e->text();
    QStringList tidList = tids.split(',');

    int len = tidList.size();
    int i =0;
    while(i < len)
    {
        if(!tid_list->contains(tidList.at(i)))
        {
            tid_list->append(tidList.at(i));
            i++;
        }
    }
    this->close();
}
