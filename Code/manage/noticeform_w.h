#ifndef NOTICEFORM_W_H
#define NOTICEFORM_W_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
//#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QItemSelectionModel>
#include <QDebug>
#include <QVariant>
#include <QDateTime>
#include <QVector>
#include <QSqlRecord>
//#include <QList>
#include <QSqlQuery>
#include <QMessageBox>
#include <QItemSelectionModel>
#include <QModelIndexList>
#include <QEvent>
#include "custompublishdate_w.h"
#include "edittid_w.h"
namespace Ui {
class NoticeForm_w;
}

class Notice{
public:
    Notice();
    Notice(Notice *);
    ~Notice();
    uint notice_id;
    int classmate_count;//保存以tid为一类的对象个数，链表头使用
    QString id;
    int row_num;//行号
    uint publish_time;//发布时间
    QString spot_name;//站点名
    int deltaDate;//距现在的时间
    bool is_old;//新的还是旧的
    bool Using;//是否正在使用,一个类中仅有一个为true,即is_old为true时,距离现在时间最近的那个对象
    bool beUsing;//是否将要使用,一个类中仅有一个为true,即is_old为false时,距离现在时间最近的那个对象
    Notice * next;//连接成员
    Notice * map;//连接自己
    uint now_date();//返回当前时间
    bool isOld();//判断自己是否为旧的
    void setMember(QString,int,uint,QString);//设置部分成员
    void showSpotName();

private:

};

class NoticeForm_w : public QDialog
{
    Q_OBJECT

public:
    explicit NoticeForm_w(QSqlDatabase *DB,QWidget *parent = 0);
    ~NoticeForm_w();
protected:
    //bool eventFilter(QObject *, QEvent *);
private slots:
    void on_select_b_clicked();

    void on_select_fliter_currentTextChanged(const QString &arg1);

    void on_delete_b_released();


    void on_tableView_entered(const QModelIndex &index);


    void on_tableView_clicked(const QModelIndex &index);

//    void on_tableView_pressed(const QModelIndex &index);


    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_create_b_clicked();

    void on_wather_currentTextChanged(const QString &arg1);

    void on_publish_delay_b_currentTextChanged(const QString &arg1);

    void on_notice_e_textChanged();

    void on_publish_b_currentTextChanged(const QString &arg1);

private:
    Ui::NoticeForm_w *ui;
    QSqlDatabase *db;
    //QSqlTableModel *model;
    //QSqlRelationalTableModel *model;
     QSqlTableModel * model;
     //QItemSelectionModel * select_model;
     //QModelIndexList select_list;
    QSqlRelation fRKey;

    QString tid;
    QString sName;
    QString lastSelect;
    QStringList strs;
    QVector<uint> selectedRowNidList;
    //QModelIndex in_dateTime;
    //QModelIndex in_id;
    //QVector<Notice> noticeList;

    Notice * noticeClasses;
    QStringList tids;
    QStringList tidList;
    int row_count;
    int class_count;

    bool isEditNew;
    int pselect_Row;
    QString currentWeather;
    QString publish_date;

    void classify_by_id();
    void identifyNotice();
    void showAll();
    void editDisable();
    void editEnable();
    QSqlQuery * getSpotNames();
    void clearSelectList();
    bool isSameDate(QString);
    bool insertOrUpdate(QString id);
};

#endif // NOTICEFORM_W_H
