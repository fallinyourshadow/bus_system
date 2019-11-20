#ifndef MANAGEWINDOW_H
#define MANAGEWINDOW_H

#include <QMainWindow>
#include "logindatabase_w.h"
#include "noticeform_w.h"
#include "busroute_w.h"
#include "parentform_w.h"

namespace Ui {
class ManageWindow;
}

class ManageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManageWindow(QWidget *parent = 0);
    ~ManageWindow();
    LoginDatabase_w * loginDb_w;
private slots:

    void on_notice_a_triggered();

    void on_prentInfo_a_triggered();

    void on_arriveInfo_a_triggered();

private:
    Ui::ManageWindow *ui;
    NoticeForm_w * noticeForm_w;
    BusRoute_w * busRoute_w;
    ParentForm_w * parentForm_w;
    //MainWindow a;
};

#endif // MANAGEWINDOW_H
