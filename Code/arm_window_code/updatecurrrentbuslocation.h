#ifndef UPDATECURRRENTBUSLOCATION_H
#define UPDATECURRRENTBUSLOCATION_H
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QStringListModel>
#include <QSqlQuery>
#include <QSqlRecord>
class Bus
{
public:
    Bus(){
        bnum = '0';
        current_se = 0;
        spot_se = 0;
        spot_count = -1;
        Bus *next = NULL;
    }
    ~Bus(){};
    QString bnum;
    uint current_se;
    uint spot_se;
    int spot_count;
    Bus *next;
};


#endif // UPDATECURRRENTBUSLOCATION_H

