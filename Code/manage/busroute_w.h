#ifndef BUSROUTE_W_H
#define BUSROUTE_W_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QStringListModel>

namespace Ui {
class BusRoute_w;
}
class Route
{
public:
    Route(){
        next = NULL;
        route_num = '0';
        tid = '0';
        bid = '0';
        spot_count = 0;
        spot_name = '0';
        sequence = 0;
    }

    ~Route(){};
    QString route_num;
    QString tid;
    QString spot_name;
    QString bid;
    uint spot_count;
    uint sequence;
    Route *next;
};

class BusRoute_w : public QDialog
{
    Q_OBJECT

public:
    explicit BusRoute_w(QSqlDatabase *DB,QWidget *parent = 0);
    ~BusRoute_w();

private slots:
    void on_buttonadd_clicked();

    void on_pushButton_clicked();

    void on_buttonconcel_clicked();

    void on_buttondel_clicked();

    //void on_buttonroute_clicked();

private:
    Ui::BusRoute_w *ui;
    QSqlDatabase *db;
    QSqlTableModel *model;
    QStringListModel *modellist;
    Route *route_list;
    bool addflag;
    int class_count;
    void update_rlist();
};

#endif // BUSROUTE_W_H
